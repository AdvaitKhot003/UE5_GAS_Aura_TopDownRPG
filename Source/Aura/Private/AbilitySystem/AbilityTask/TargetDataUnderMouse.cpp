// No Copyright


#include "AbilitySystem/AbilityTask/TargetDataUnderMouse.h"

UTargetDataUnderMouse* UTargetDataUnderMouse::CreateTargetDataUnderMouse(UGameplayAbility* OwningGameplayAbility)
{
	UTargetDataUnderMouse* MyObject = NewAbilityTask<UTargetDataUnderMouse>(OwningGameplayAbility);
	return MyObject;
}

void UTargetDataUnderMouse::Activate()
{
	Super::Activate();
	
	APlayerController* PC = Ability->GetCurrentActorInfo()->PlayerController.Get();
	FHitResult HitResult;
	PC->GetHitResultUnderCursor(ECC_Visibility, false, HitResult);
	ValidTargetData.Broadcast(HitResult.Location);
}
