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
	for (const FEffectApplicationConfig& Config : EffectApplicationConfigs)
	{
		if (Config.ApplicationPolicy == EEffectApplicationPolicy::ApplyOnBeginOverlap)
		{
			ApplyGameplayEffectToTargetActor(TargetActor, Config);
		}
	}
}

void AAuraEffectActor::OnEndOverlap(AActor* TargetActor)
{
	bool bShouldRemove = false;

	for (const FEffectApplicationConfig& Config : EffectApplicationConfigs)
	{
		if (Config.ApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
		{
			ApplyGameplayEffectToTargetActor(TargetActor, Config);
		}

		if (Config.RemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
		{
			bShouldRemove = true;
		}
	}

	if (bShouldRemove)
	{
		RemoveInfiniteEffectsFromTargetActor(TargetActor);
	}
}

void AAuraEffectActor::ApplyGameplayEffectToTargetActor(AActor* TargetActor, const FEffectApplicationConfig& Config)
{
	if (!HasAuthority()) return;
	if (!Config.GameplayEffectClass) return;

	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (!TargetASC) return;

	FGameplayEffectContextHandle EffectContextHandle = TargetASC->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);

	const FGameplayEffectSpecHandle EffectSpecHandle =
		TargetASC->MakeOutgoingSpec(Config.GameplayEffectClass, Config.EffectLevel, EffectContextHandle);

	if (!EffectSpecHandle.IsValid()) return;
	
	const FGameplayEffectSpec& EffectSpec = *EffectSpecHandle.Data.Get();
	const FActiveGameplayEffectHandle ActiveEffectHandle = TargetASC->ApplyGameplayEffectSpecToSelf(EffectSpec);

	const UGameplayEffect* GameplayEffect = EffectSpec.Def.Get();
	const bool bIsInfinite = GameplayEffect && GameplayEffect->DurationPolicy == EGameplayEffectDurationType::Infinite;

	if (bIsInfinite && Config.RemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		ActiveEffectHandles.Add(TargetASC, ActiveEffectHandle);
	}
}

void AAuraEffectActor::RemoveInfiniteEffectsFromTargetActor(AActor* TargetActor)
{
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (!TargetASC) return;

	TArray<FActiveGameplayEffectHandle> TempActiveEffectHandles;
	ActiveEffectHandles.MultiFind(TargetASC, TempActiveEffectHandles);

	TArray<FActiveGameplayEffectHandle> EffectHandlesToRemove;

	for (const FActiveGameplayEffectHandle& TempEffectHandle : TempActiveEffectHandles)
	{
		int32 StacksRemoved = TargetASC->RemoveActiveGameplayEffect(TempEffectHandle, 1);

		if (StacksRemoved > 0 && TargetASC->GetActiveGameplayEffect(TempEffectHandle) == nullptr)
		{
			EffectHandlesToRemove.Add(TempEffectHandle);
		}
	}

	for (const FActiveGameplayEffectHandle& EffectHandle : EffectHandlesToRemove)
	{
		ActiveEffectHandles.RemoveSingle(TargetASC, EffectHandle);
	}
}
