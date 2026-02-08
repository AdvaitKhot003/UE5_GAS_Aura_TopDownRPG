// No Copyright

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AuraEffectActor.generated.h"

class UGameplayEffect;

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
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AppliedEffects")
	TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;
	
	UFUNCTION(BlueprintCallable)
	void ApplyGameplayEffectToTargetActor(AActor* TargetActor, const TSubclassOf<UGameplayEffect>& GameplayEffectClass);
};
