// No Copyright


#include "Controller/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInput/DataAsset_AuraInputConfig.h"
#include "EnhancedInput/AuraEnhancedInputComponent.h"
#include "AuraGameplayTags.h"
#include "Interaction/EnemyInterface.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "NavigationPath.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Components/SplineComponent.h"
#include "NavigationSystem.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
	
	SplineComponent = CreateDefaultSubobject<USplineComponent>("SplineComponent");
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	if (!IsLocalController()) return;
	TraceUnderCursor();
	ClickToAutoRun();
}

UAuraAbilitySystemComponent* AAuraPlayerController::GetAuraAbilitySystemComponent()
{
	if (AuraAbilitySystemComponent == nullptr)
	{
		AuraAbilitySystemComponent = Cast<UAuraAbilitySystemComponent>(
			UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
	}
	return AuraAbilitySystemComponent;
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

void AAuraPlayerController::ClickToAutoRun()
{
	if (!bAutoRunning) return;

	APawn* OwningPawn = GetPawn();
	if (!OwningPawn) return;

	const float ClosestKey = SplineComponent->FindInputKeyClosestToWorldLocation(OwningPawn->GetActorLocation());

	const FVector Direction = SplineComponent->GetDirectionAtSplineInputKey(ClosestKey, ESplineCoordinateSpace::World);

	OwningPawn->AddMovementInput(Direction);

	const FVector LocationOnSpline = SplineComponent->GetLocationAtSplineInputKey(ClosestKey, ESplineCoordinateSpace::World);
	const float DistanceToDestination = FVector::Dist(LocationOnSpline, CachedDestination);

	if (DistanceToDestination < AutoRunAcceptanceRadius)
	{
		bAutoRunning = false;
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
	if (GetAuraAbilitySystemComponent() == nullptr) return;
	GetAuraAbilitySystemComponent()->OnInputAbilityPressed(InputTag);
	
	if (InputTag.MatchesTagExact(AuraGameplayTags::InputTag_LMB))
	{
		bTargeting = CurrentHitResultActor? true : false;
		bAutoRunning = false;
	}
}

void AAuraPlayerController::Input_AbilityHeld(FGameplayTag InputTag)
{
	if (!InputTag.MatchesTagExact(AuraGameplayTags::InputTag_LMB))
	{
		if (GetAuraAbilitySystemComponent())
		{
			GetAuraAbilitySystemComponent()->OnInputAbilityHeld(InputTag);
		}
		return;
	}

	if (bTargeting)
	{
		if (GetAuraAbilitySystemComponent())
		{
			GetAuraAbilitySystemComponent()->OnInputAbilityHeld(InputTag);
		}
	}
	else
	{
		FollowTime += GetWorld()->GetDeltaSeconds();
		FHitResult HitResult;
		
		if (GetHitResultUnderCursor(ECC_Visibility, false, HitResult))
		{
			CachedDestination = HitResult.ImpactPoint;
		}
		
		APawn* OwningPawn = GetPawn();
		if (!OwningPawn) return;
		
		const FVector WorldDirection = (CachedDestination - OwningPawn->GetActorLocation()).GetSafeNormal();
		OwningPawn->AddMovementInput(WorldDirection);
	}
}

void AAuraPlayerController::Input_AbilityReleased(FGameplayTag InputTag)
{
	if (!InputTag.MatchesTagExact(AuraGameplayTags::InputTag_LMB))
	{
		if (GetAuraAbilitySystemComponent())
		{
			GetAuraAbilitySystemComponent()->OnInputAbilityReleased(InputTag);
		}
		return;
	}
	
	if (bTargeting)
	{
		if (GetAuraAbilitySystemComponent())
		{
			GetAuraAbilitySystemComponent()->OnInputAbilityReleased(InputTag);
		}
	}
	else
	{
		const APawn* OwningPawn = GetPawn();
		if (!OwningPawn) return;
		
		if (FollowTime <= ShortPressThreshold && CachedDestination != OwningPawn->GetActorLocation())
		{
			const UNavigationPath* NavigationPath = UNavigationSystemV1::FindPathToLocationSynchronously(
				this, OwningPawn->GetActorLocation(), CachedDestination);
			
			if (!NavigationPath || NavigationPath->PathPoints.Num() == 0) return;
			
			SplineComponent->ClearSplinePoints();
			for (const FVector& PathPointLocation : NavigationPath->PathPoints)
			{
				SplineComponent->AddSplinePoint(PathPointLocation, ESplineCoordinateSpace::World);
				DrawDebugSphere(GetWorld(), PathPointLocation, 10.f, 10, FColor::Red, false, 5.f);
			}
			SplineComponent->UpdateSpline();
			CachedDestination = NavigationPath->PathPoints.Last();
			bAutoRunning = true;
		}
		
		FollowTime = 0.f;
		bTargeting = false;
	}
}
