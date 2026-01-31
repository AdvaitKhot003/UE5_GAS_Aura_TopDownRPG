// No Copyright


#include "Controllers/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	check(AuraMappingContext);

	if (!IsLocalController()) return;

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(AuraMappingContext, 0);
	}
	
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Hand;
	
	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	
	EnhancedInputComponent->BindAction(MoveInputAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D MovementVector = InputActionValue.Get<FVector2D>();
	const FRotator MovementRotation(0.f, GetControlRotation().Yaw, 0.f);
	
	const FVector ForwardDirection = MovementRotation.RotateVector(FVector::ForwardVector);
	const FVector RightDirection = MovementRotation.RotateVector(FVector::RightVector);
	
	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		if (MovementVector.Y != 0.f)
		{
			ControlledPawn->AddMovementInput(ForwardDirection, MovementVector.Y, false);
		}
		
		if (MovementVector.X != 0.f)
		{
			ControlledPawn->AddMovementInput(RightDirection, MovementVector.X, false);
		}
	}
}
