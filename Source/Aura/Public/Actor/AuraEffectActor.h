// No Copyright

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "GameFramework/Actor.h"
#include "AuraEffectActor.generated.h"

class UAbilitySystemComponent;
class UGameplayEffect;

UENUM(BlueprintType)
enum class EEffectApplicationPolicy : uint8
{
	ApplyOnBeginOverlap,
	ApplyOnEndOverlap,
	DontApply
};

UENUM(BlueprintType)
enum class EEffectRemovalPolicy : uint8
{
	RemoveOnEndOverlap,
	DontRemove
};

UCLASS()
class AURA_API AAuraEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AAuraEffectActor();

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USceneComponent> EffectActorRoot;
	
	UFUNCTION(BlueprintCallable)
	void OnBeginOverlap(AActor* TargetActor);
	
	UFUNCTION(BlueprintCallable)
	void OnEndOverlap(AActor* TargetActor);
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AppliedEffects")
	bool bDestroyOnEffectRemoval = false;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AppliedEffects")
	TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AppliedEffects")
	EEffectApplicationPolicy InstantEffectApplicationPolicy = EEffectApplicationPolicy::DontApply;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AppliedEffects")
	TSubclassOf<UGameplayEffect> DurationGameplayEffectClass;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AppliedEffects")
	EEffectApplicationPolicy DurationEffectApplicationPolicy = EEffectApplicationPolicy::DontApply;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AppliedEffects")
	TSubclassOf<UGameplayEffect> InfiniteGameplayEffectClass;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AppliedEffects")
	EEffectApplicationPolicy InfiniteEffectApplicationPolicy = EEffectApplicationPolicy::DontApply;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AppliedEffects")
	EEffectRemovalPolicy InfiniteEffectRemovalPolicy = EEffectRemovalPolicy::DontRemove;
	
	UFUNCTION(BlueprintCallable)
	void ApplyGameplayEffectToTargetActor(AActor* TargetActor, const TSubclassOf<UGameplayEffect>& GameplayEffectClass);
	
	UPROPERTY(Transient)
	TMap<FActiveGameplayEffectHandle, UAbilitySystemComponent*> ActiveEffectHandles;
};
