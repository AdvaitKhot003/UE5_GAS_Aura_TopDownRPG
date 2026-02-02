// No Copyright


#include "Character/AuraPlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AAuraPlayer::AAuraPlayer()
{
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->SetRelativeRotation(FRotator(-45.f, 0.f, 0.f));
	CameraBoom->TargetArmLength = 600.f;
	CameraBoom->bUsePawnControlRotation = false;
	
	CameraBoom->bEnableCameraLag = true;
	CameraBoom->CameraLagSpeed = 10.0f;
	CameraBoom->CameraLagMaxDistance = 50.0f;
	CameraBoom->bEnableCameraRotationLag = false;
	CameraBoom->bUseCameraLagSubstepping = true;
	CameraBoom->CameraLagMaxTimeStep = 0.016f; // 60 FPS
	
	CameraBoom->bInheritPitch = false;
	CameraBoom->bInheritYaw = false;
	CameraBoom->bInheritRoll = false;
	
	FollowCamera = CreateDefaultSubobject<UCameraComponent>("FollowCamera");
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
	
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 540.f, 0.f);
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->GroundFriction = 10.f;
}
