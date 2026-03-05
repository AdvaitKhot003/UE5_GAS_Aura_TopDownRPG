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
	
	template<class UserObject, typename CallbackFunction>
	void BindAbilityInputAction(const UDataAsset_AuraInputConfig* InInputConfig, UserObject* ContextObject,
		CallbackFunction InputPressedFunction, CallbackFunction InputReleasedFunction, CallbackFunction InputHeldFunction);
};

template <class UserObject, typename CallbackFunction>
void UAuraEnhancedInputComponent::BindNativeInputAction(const UDataAsset_AuraInputConfig* InInputConfig,
	const FGameplayTag& InInputTag, ETriggerEvent TriggerEvent, UserObject* ContextObject, CallbackFunction Function)
{
	checkf(InInputConfig,
		TEXT("Warning: UDataAsset_AuraInputConfig* InInputConfig is nullptr in BindNativeInputAction."));

	if (UInputAction* FoundInputAction = InInputConfig->FindNativeInputActionByTag(InInputTag))
	{
		BindAction(FoundInputAction, TriggerEvent, ContextObject, Function);
	}
}

template <class UserObject, typename CallbackFunction>
void UAuraEnhancedInputComponent::BindAbilityInputAction(const UDataAsset_AuraInputConfig* InInputConfig, UserObject* ContextObject,
	CallbackFunction InputPressedFunction, CallbackFunction InputReleasedFunction, CallbackFunction InputHeldFunction)
{
	checkf(InInputConfig,
		TEXT("Warning: UDataAsset_AuraInputConfig* InInputConfig is nullptr in BindAbilityInputAction."));

	for (const FAuraInputActionConfig& AbilityInputActionConfig : InInputConfig->AbilityInputActions)
	{
		if (!AbilityInputActionConfig.IsValid()) continue;

		if (InputPressedFunction)
		{
			BindAction(AbilityInputActionConfig.InputAction, ETriggerEvent::Started, ContextObject, InputPressedFunction,
				AbilityInputActionConfig.InputTag);
		}

		if (InputReleasedFunction)
		{
			BindAction(AbilityInputActionConfig.InputAction, ETriggerEvent::Completed, ContextObject, InputReleasedFunction,
				AbilityInputActionConfig.InputTag);
		}
		
		if (InputHeldFunction)
		{
			BindAction(AbilityInputActionConfig.InputAction, ETriggerEvent::Triggered, ContextObject, InputHeldFunction,
				AbilityInputActionConfig.InputTag);
		}
	}
}
