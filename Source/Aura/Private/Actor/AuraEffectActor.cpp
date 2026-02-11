// No Copyright


#include "Actor/AuraEffectActor.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"

AAuraEffectActor::AAuraEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;
	
	EffectActorRoot = CreateDefaultSubobject<USceneComponent>("EffectActorRoot");
	SetRootComponent(EffectActorRoot);
}

void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();
}

void AAuraEffectActor::OnBeginOverlap(AActor* TargetActor)
{
	if (InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnBeginOverlap)
	{
		ApplyGameplayEffectToTargetActor(TargetActor, InstantGameplayEffectClass);
	}
	
	if (DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnBeginOverlap)
	{
		ApplyGameplayEffectToTargetActor(TargetActor, DurationGameplayEffectClass);
	}
	
	if (InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnBeginOverlap)
	{
		ApplyGameplayEffectToTargetActor(TargetActor, InfiniteGameplayEffectClass);
	}
}

void AAuraEffectActor::OnEndOverlap(AActor* TargetActor)
{
	if (InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyGameplayEffectToTargetActor(TargetActor, InstantGameplayEffectClass);
	}
	
	if (DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyGameplayEffectToTargetActor(TargetActor, DurationGameplayEffectClass);
	}
	
	if (InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyGameplayEffectToTargetActor(TargetActor, InfiniteGameplayEffectClass);
	}
	
	if (InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
		if (!TargetASC) return;
		
		TArray<FActiveGameplayEffectHandle> ActiveEffectHandlesToRemove;
		
		for (const auto& [ActiveEffectHandle, ASC] : ActiveEffectHandles)
		{
			if (ASC == TargetASC)
			{
				TargetASC->RemoveActiveGameplayEffect(ActiveEffectHandle, 1);
				ActiveEffectHandlesToRemove.Add(ActiveEffectHandle);
			}
		}
		
		for (const auto& ActiveEffectHandle : ActiveEffectHandlesToRemove)
		{
			ActiveEffectHandles.FindAndRemoveChecked(ActiveEffectHandle);
		}
	}
}

void AAuraEffectActor::ApplyGameplayEffectToTargetActor(AActor* TargetActor, const TSubclassOf<UGameplayEffect>& GameplayEffectClass)
{
	if (!HasAuthority()) return;
	
	checkf(GameplayEffectClass, TEXT("GameplayEffectClass is null in ApplyGameplayEffectToTargetActor: %s"), *GetActorNameOrLabel());

	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (!TargetASC) return;

	FGameplayEffectContextHandle EffectContextHandle = TargetASC->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);

	const FGameplayEffectSpecHandle EffectSpecHandle =
		TargetASC->MakeOutgoingSpec(GameplayEffectClass, EffectActorLevel, EffectContextHandle);

	if (EffectSpecHandle.IsValid())
	{
		const FGameplayEffectSpec& EffectSpec = *EffectSpecHandle.Data.Get();
		const FActiveGameplayEffectHandle ActiveEffectHandle = TargetASC->ApplyGameplayEffectSpecToSelf(EffectSpec);
		
		const UGameplayEffect* GameplayEffect = EffectSpec.Def.Get();
		const bool bIsInfinite = GameplayEffect && GameplayEffect->DurationPolicy == EGameplayEffectDurationType::Infinite;

		if (bIsInfinite && InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
		{
			ActiveEffectHandles.Add(ActiveEffectHandle, TargetASC);
		}
	}
}
