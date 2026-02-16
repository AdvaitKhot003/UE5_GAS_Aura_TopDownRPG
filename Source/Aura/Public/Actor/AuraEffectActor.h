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

USTRUCT(BlueprintType)
struct FEffectApplicationConfig
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> GameplayEffectClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bOverrideEffectLevel = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "bOverrideEffectLevel", EditConditionHides))
	float EffectLevel = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EEffectApplicationPolicy ApplicationPolicy = EEffectApplicationPolicy::DontApply;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EEffectRemovalPolicy RemovalPolicy = EEffectRemovalPolicy::DontRemove;
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
	TArray<FEffectApplicationConfig> EffectApplicationConfigs;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AppliedEffects")
	bool bDestroyOnEffectRemoval = false;
	
	UFUNCTION(BlueprintCallable)
	void ApplyGameplayEffectToTargetActor(AActor* TargetActor, const FEffectApplicationConfig& Config);
	
	UFUNCTION(BlueprintCallable)
	void RemoveInfiniteEffectsFromTargetActor(AActor* TargetActor);
	
	TMultiMap<UAbilitySystemComponent*, FActiveGameplayEffectHandle> ActiveEffectHandles;
};
