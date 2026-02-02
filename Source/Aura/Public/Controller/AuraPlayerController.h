// No Copyright

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AuraPlayerController.generated.h"

class UDataAsset_AuraInputConfig;
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
	
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|DataAsset", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UDataAsset_AuraInputConfig> AuraInputConfig;
	
	void Input_Move(const FInputActionValue& InputActionValue);
};
