// No Copyright


#include "EnhancedInput/DataAsset_AuraInputConfig.h"

TObjectPtr<UInputAction> UDataAsset_AuraInputConfig::FindNativeInputActionByTag(const FGameplayTag& InInputTag, bool bInputActionNotFound) const
{
	for (const FAuraInputActionConfig& NativeInputActionConfig : NativeInputActions)
	{
		if (NativeInputActionConfig.IsValid() && NativeInputActionConfig.InputTag == InInputTag)
		{
			return NativeInputActionConfig.InputAction;
		}
	}
	
	if (bInputActionNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("InputAction not found for tag: %s in InputConfig: %s"), *InInputTag.ToString(), *GetNameSafe(this));
	}
	return nullptr;
}
