// No Copyright

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "AuraPlayer.generated.h"

class USpringArmComponent;
class UCameraComponent;

/**
 * 
 */
UCLASS()
class AURA_API AAuraPlayer : public AAuraCharacterBase
{
	GENERATED_BODY()
	
public:
	AAuraPlayer();
	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> FollowCamera;
};
