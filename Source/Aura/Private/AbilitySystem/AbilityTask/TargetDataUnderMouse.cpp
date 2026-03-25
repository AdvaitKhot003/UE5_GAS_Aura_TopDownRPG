// No Copyright


#include "AbilitySystem/AbilityTask/TargetDataUnderMouse.h"
#include "AbilitySystemComponent.h"

UTargetDataUnderMouse* UTargetDataUnderMouse::CreateTargetDataUnderMouse(UGameplayAbility* OwningGameplayAbility)
{
	UTargetDataUnderMouse* MyObject = NewAbilityTask<UTargetDataUnderMouse>(OwningGameplayAbility);
	return MyObject;
}

void UTargetDataUnderMouse::Activate()
{
	Super::Activate();
	
	const bool bIsLocallyControlled = Ability->GetCurrentActorInfo()->IsLocallyControlled();
	
	if (bIsLocallyControlled) SendTargetDataUnderMouse();
	else
	{
		// Server Implementation (Listening For Target Data)
	}
}

void UTargetDataUnderMouse::SendTargetDataUnderMouse()
{
	APlayerController* PC = Ability->GetCurrentActorInfo()->PlayerController.Get();
	if (!PC) return;

	FHitResult HitResult;
	PC->GetHitResultUnderCursor(ECC_Visibility, false, HitResult);

	FGameplayAbilityTargetData_SingleTargetHit* Data = new FGameplayAbilityTargetData_SingleTargetHit();
	Data->HitResult = HitResult;

	FGameplayAbilityTargetDataHandle Handle;
	Handle.Add(Data);

	UAbilitySystemComponent* ASC = AbilitySystemComponent.Get();
	if (!ASC) return;

	if (Ability->GetCurrentActorInfo()->IsLocallyControlled())
	{
		FScopedPredictionWindow ScopedPrediction(ASC);

		ASC->ServerSetReplicatedTargetData(
			GetAbilitySpecHandle(),
			GetActivationPredictionKey(),
			Handle,
			FGameplayTag(),
			ASC->ScopedPredictionKey
		);
	}

	if (ShouldBroadcastAbilityTaskDelegates())
	{
		ValidTargetData.Broadcast(Handle);
	}

	EndTask();
}
