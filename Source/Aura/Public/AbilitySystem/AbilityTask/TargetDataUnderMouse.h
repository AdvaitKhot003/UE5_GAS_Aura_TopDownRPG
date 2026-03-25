// No Copyright

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "TargetDataUnderMouse.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTargetDataUnderMouseSignature, const FGameplayAbilityTargetDataHandle&, TargetDataHandle);

/**
 * 
 */
UCLASS()
class AURA_API UTargetDataUnderMouse : public UAbilityTask
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks",
		meta = (
			DisplayName = "TargetDataUnderMouse",
			HidePin = "OwningGameplayAbility",
			DefaultToSelf = "OwningGameplayAbility",
			BlueprintInternalUseOnly = "TRUE"))
	static UTargetDataUnderMouse* CreateTargetDataUnderMouse(UGameplayAbility* OwningGameplayAbility);
	
	UPROPERTY(BlueprintAssignable, Category = "Ability|Tasks")
	FTargetDataUnderMouseSignature ValidTargetData;
	
private:
	virtual void Activate() override;
	virtual void SendTargetDataUnderMouse();
};
