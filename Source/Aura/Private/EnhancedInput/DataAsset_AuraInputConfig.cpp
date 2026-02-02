// No Copyright


#include "EnhancedInput/DataAsset_AuraInputConfig.h"

TObjectPtr<UInputAction> UDataAsset_AuraInputConfig::FindNativeInputActionByTag(const FGameplayTag& InInputTag) const
{
	for (const FAuraInputActionConfig& NativeInputActionConfig : NativeInputActions)
	{
		if (NativeInputActionConfig.IsValid() && NativeInputActionConfig.InputTag == InInputTag)
		{
			return NativeInputActionConfig.InputAction;
		}
	}
	return nullptr;
}
