// No Copyright

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/PlayerController.h"
#include "AuraPlayerController.generated.h"

class UDataAsset_AuraInputConfig;
class IEnemyInterface;
struct FInputActionValue;

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
};
