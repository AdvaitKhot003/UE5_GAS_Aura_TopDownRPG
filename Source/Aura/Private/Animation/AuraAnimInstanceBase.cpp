// No Copyright


#include "Animation/AuraAnimInstanceBase.h"
#include "Character/AuraCharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"

void UAuraAnimInstanceBase::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	
	AuraBaseCharacter = Cast<AAuraCharacterBase>(TryGetPawnOwner());

	if (AuraBaseCharacter)
	{
		AuraBaseMovementComponent = AuraBaseCharacter->GetCharacterMovement();
	}
}

void UAuraAnimInstanceBase::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	
	if (!AuraBaseCharacter || !AuraBaseMovementComponent)
	{
		return;
	}

	CachedGroundSpeed = AuraBaseCharacter->GetVelocity().Size2D();

	CachedHasAcceleration = AuraBaseMovementComponent->GetCurrentAcceleration().SizeSquared2D() > 0.f;
}

void UAuraAnimInstanceBase::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);
	
	GroundSpeed = CachedGroundSpeed;
	bHasAcceleration = CachedHasAcceleration;
}
