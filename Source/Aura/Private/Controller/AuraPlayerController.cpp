// No Copyright


#include "Controller/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInput/DataAsset_AuraInputConfig.h"
#include "EnhancedInput/AuraEnhancedInputComponent.h"
#include "AuraGameplayTags.h"
#include "Interaction/EnemyInterface.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	if (IsLocalController())
	{
		TraceUnderCursor();
	}
}

void AAuraPlayerController::TraceUnderCursor()
{
	FHitResult CursorHitResult;
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHitResult);

	LastHitResultActor = CurrentHitResultActor;
	CurrentHitResultActor = nullptr;

	if (CursorHitResult.IsValidBlockingHit())
	{
		AActor* HitResultActor = CursorHitResult.GetActor();

		if (HitResultActor && HitResultActor->Implements<UEnemyInterface>())
		{
			CurrentHitResultActor.SetObject(HitResultActor);
			CurrentHitResultActor.SetInterface(Cast<IEnemyInterface>(HitResultActor));
		}
	}
	
	if (LastHitResultActor == CurrentHitResultActor) return;

	if (LastHitResultActor)
	{
		LastHitResultActor->UnhighlightActor();
	}

	if (CurrentHitResultActor)
	{
		CurrentHitResultActor->HighlightActor();
	}
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();

	checkf(AuraInputConfig, TEXT("AuraInputConfig is null in BeginPlay: %s"), *GetActorNameOrLabel());

	if (!IsLocalController()) return;

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	checkf(Subsystem, TEXT("Subsystem is null in BeginPlay: %s"), *GetActorNameOrLabel());
	Subsystem->AddMappingContext(AuraInputConfig->InputMappingContext, 0);

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputMode.SetHideCursorDuringCapture(false);
	SetInputMode(InputMode);
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UAuraEnhancedInputComponent* AuraEnhancedInputComponent = CastChecked<UAuraEnhancedInputComponent>(InputComponent);

	AuraEnhancedInputComponent->BindNativeInputAction(AuraInputConfig, AuraGameplayTags::InputTag_Move,
		ETriggerEvent::Triggered, this, &AAuraPlayerController::Input_Move);
	
	AuraEnhancedInputComponent->BindAbilityInputAction(AuraInputConfig, this, &ThisClass::Input_AbilityPressed,
		&ThisClass::Input_AbilityReleased, &ThisClass::Input_AbilityHeld);
}

void AAuraPlayerController::Input_Move(const FInputActionValue& InputActionValue)
{
	const FVector2D MovementAxisVector = InputActionValue.Get<FVector2D>();
	
	const FRotator MovementRotation(0.f, GetControlRotation().Yaw, 0.f);

	const FVector ForwardDirection = MovementRotation.RotateVector(FVector::ForwardVector);
	const FVector RightDirection = MovementRotation.RotateVector(FVector::RightVector);

	APawn* OwningPawn = GetPawn();
	if (!OwningPawn) return;

	if (!FMath::IsNearlyZero(MovementAxisVector.Y))
	{
		OwningPawn->AddMovementInput(ForwardDirection, MovementAxisVector.Y);
	}

	if (!FMath::IsNearlyZero(MovementAxisVector.X))
	{
		OwningPawn->AddMovementInput(RightDirection, MovementAxisVector.X);
	}
}

void AAuraPlayerController::Input_AbilityPressed(FGameplayTag InputTag)
{
	GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Red,
		FString::Printf(TEXT("Ability Input Pressed: %s"), *InputTag.ToString()));
}

void AAuraPlayerController::Input_AbilityReleased(FGameplayTag InputTag)
{
	GEngine->AddOnScreenDebugMessage(2, 5.f, FColor::Green,
		FString::Printf(TEXT("Ability Input Released: %s"), *InputTag.ToString()));
}

void AAuraPlayerController::Input_AbilityHeld(FGameplayTag InputTag)
{
	GEngine->AddOnScreenDebugMessage(3, 5.f, FColor::Blue,
		FString::Printf(TEXT("Ability Input Held: %s"), *InputTag.ToString()));
}
