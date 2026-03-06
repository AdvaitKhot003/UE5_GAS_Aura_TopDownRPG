// No Copyright

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/PlayerController.h"
#include "AuraPlayerController.generated.h"

class UAuraAbilitySystemComponent;
class UDataAsset_AuraInputConfig;
class IEnemyInterface;
struct FInputActionValue;
class USplineComponent;

/**
 * 
 */
UCLASS()
class AURA_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AAuraPlayerController();
	virtual void PlayerTick(float DeltaTime) override;
	
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|DataAsset", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UDataAsset_AuraInputConfig> AuraInputConfig;
	
	void Input_Move(const FInputActionValue& InputActionValue);
	void Input_AbilityPressed(FGameplayTag InputTag);
	void Input_AbilityReleased(FGameplayTag InputTag);
	void Input_AbilityHeld(FGameplayTag InputTag);
	
	void TraceUnderCursor();
	
	UPROPERTY(Transient)
	TScriptInterface<IEnemyInterface> LastHitResultActor;
	
	UPROPERTY(Transient)
	TScriptInterface<IEnemyInterface> CurrentHitResultActor;
	
	UPROPERTY()
	TObjectPtr<UAuraAbilitySystemComponent> AuraAbilitySystemComponent;
	UAuraAbilitySystemComponent* GetAuraAbilitySystemComponent();
	
	FVector CachedDestination = FVector::ZeroVector;
	float FollowTime = 0.f;
	float ShortPressThreshold = 0.5f;
	bool bAutoRunning = false;
	bool bTargeting = false;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|DataAsset", meta = (AllowPrivateAccess = "true"))
	float AutoRunAcceptanceRadius = 50.f;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Input|DataAsset", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USplineComponent> SplineComponent;
};
