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
}

void AAuraEffectActor::ApplyGameplayEffectToTargetActor(AActor* TargetActor, const TSubclassOf<UGameplayEffect>& GameplayEffectClass)
{
	if (!HasAuthority()) return;
	
	checkf(GameplayEffectClass, TEXT("GameplayEffectClass is null in ApplyGameplayEffectToTargetActor: %s"), *GetActorNameOrLabel());

	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	checkf(TargetASC, TEXT("TargetASC is null in ApplyGameplayEffectToTargetActor: %s"), *GetActorNameOrLabel());

	FGameplayEffectContextHandle EffectContextHandle = TargetASC->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);

	const FGameplayEffectSpecHandle EffectSpecHandle =
		TargetASC->MakeOutgoingSpec(GameplayEffectClass, 1.f, EffectContextHandle);

	if (EffectSpecHandle.IsValid())
	{
		TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
	}
}
