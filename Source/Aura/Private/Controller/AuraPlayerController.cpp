// No Copyright


#include "Controller/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInput/DataAsset_AuraInputConfig.h"
#include "EnhancedInput/AuraEnhancedInputComponent.h"
#include "AuraGameplayTags.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	checkf(AuraInputConfig,
		TEXT("Warning: UDataAsset_AuraInputConfig* AuraInputConfig is nullptr in BeginPlay in AuraPlayerController."));
	
	if (!IsLocalController()) return;

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (!Subsystem) return;
	Subsystem->AddMappingContext(AuraInputConfig->InputMappingContext, 0);
	
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	
	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	UAuraEnhancedInputComponent* AuraEnhancedInputComponent = CastChecked<UAuraEnhancedInputComponent>(InputComponent);
	
	AuraEnhancedInputComponent->BindNativeInputAction(AuraInputConfig, AuraGameplayTags::InputTag_Move,
		ETriggerEvent::Triggered, this, &AAuraPlayerController::Input_Move);
}

void AAuraPlayerController::Input_Move(const FInputActionValue& InputActionValue)
{
	const FVector2D MovementAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator MovementRotation(0.f, GetControlRotation().Yaw, 0.f);
	
	const FVector ForwardDirection = MovementRotation.RotateVector(FVector::ForwardVector);
	const FVector RightDirection = MovementRotation.RotateVector(FVector::RightVector);
	
	APawn* OwningPawn = GetPawn();
	if (!OwningPawn) return;
	
	if (MovementAxisVector.Y != 0.f)
	{
		OwningPawn->AddMovementInput(ForwardDirection, MovementAxisVector.Y);
	}
	
	if (MovementAxisVector.X != 0.f)
	{
		OwningPawn->AddMovementInput(RightDirection, MovementAxisVector.X);
	}
}
