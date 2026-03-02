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
		FAuraAttributeInfo AttributeInfoFound = AttributeInfoDataAsset->FindAttributeInfoForTag(Pair.Key);
		AttributeInfoFound.AttributeValue = Pair.Value().GetNumericValue(AuraAttributeSet);
		OnAttributeInfoChanged.Broadcast(AttributeInfoFound);
	}
}

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	
}
