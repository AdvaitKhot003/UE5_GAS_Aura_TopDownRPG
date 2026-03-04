// No Copyright


#include "UI/Controller/AttributeMenuWidgetController.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/DataAsset_AuraAttributeInfo.h"

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);
	
	checkf(AttributeInfoDataAsset, TEXT("AttributeInfoDataAsset is null in BindCallbacksToDependencies: %s"), *GetNameSafe(this));
	
	for (auto& Pair : AuraAttributeSet->TagsToAttributesMap)
	{
		BroadcastAttributeInfo(Pair.Key, Pair.Value());
	}
}

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);
	UAuraAbilitySystemComponent* AuraAbilitySystemComponent = CastChecked<UAuraAbilitySystemComponent>(AbilitySystemComponent);
	
	checkf(AttributeInfoDataAsset, TEXT("AttributeInfoDataAsset is null in BindCallbacksToDependencies: %s"), *GetNameSafe(this));
	
	for (auto& Pair : AuraAttributeSet->TagsToAttributesMap)
	{
		AuraAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Value()).AddLambda(
		[this, Pair](const FOnAttributeChangeData& Data)
		{
			BroadcastAttributeInfo(Pair.Key, Pair.Value());
		});
	}
}

void UAttributeMenuWidgetController::BroadcastAttributeInfo(const FGameplayTag& AttributeTag, const FGameplayAttribute& Attribute) const
{
	const UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);
	FAuraAttributeInfo AttributeInfoFound = AttributeInfoDataAsset->FindAttributeInfoForTag(AttributeTag);
	AttributeInfoFound.AttributeValue = Attribute.GetNumericValue(AuraAttributeSet);
	OnAttributeInfoChanged.Broadcast(AttributeInfoFound);
}
