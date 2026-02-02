// No Copyright

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AuraAnimInstanceBase.generated.h"

class AAuraCharacterBase;
class UCharacterMovementComponent;

/**
 * 
 */
UCLASS()
class AURA_API UAuraAnimInstanceBase : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;
	
protected:
	UPROPERTY()
	TObjectPtr<AAuraCharacterBase> AuraBaseCharacter;

	UPROPERTY()
	TObjectPtr<UCharacterMovementComponent> AuraBaseMovementComponent;

	UPROPERTY(Transient)
	float CachedGroundSpeed = 0.f;

	UPROPERTY(Transient)
	bool CachedHasAcceleration = false;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	float GroundSpeed;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	bool bHasAcceleration;
};
