// No Copyright

#pragma once

#include "CoreMinimal.h"
#include "DataAsset_AuraInputConfig.h"
#include "EnhancedInputComponent.h"
#include "AuraEnhancedInputComponent.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraEnhancedInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()
	
public:
	template<class UserObject, typename CallbackFunction>
	void BindNativeInputAction(const UDataAsset_AuraInputConfig* InInputConfig, const FGameplayTag& InInputTag,
		ETriggerEvent TriggerEvent, UserObject* ContextObject, CallbackFunction Function);
};

template <class UserObject, typename CallbackFunction>
void UAuraEnhancedInputComponent::BindNativeInputAction(const UDataAsset_AuraInputConfig* InInputConfig,
	const FGameplayTag& InInputTag, ETriggerEvent TriggerEvent, UserObject* ContextObject, CallbackFunction Function)
{
	checkf(InInputConfig,
		TEXT("Warning: UDataAsset_InputConfig* InInputConfig is nullptr in BindNativeInputAction."));

	if (UInputAction* FoundInputAction = InInputConfig->FindNativeInputActionByTag(InInputTag))
	{
		BindAction(FoundInputAction, TriggerEvent, ContextObject, Function);
	}
}
