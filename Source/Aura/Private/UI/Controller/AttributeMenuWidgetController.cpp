// No Copyright


#include "UI/Controller/AttributeMenuWidgetController.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/DataAsset_AuraAttributeInfo.h"
#include "AuraGameplayTags.h"

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);
	
	checkf(AttributeInfoDataAsset, TEXT("AttributeInfoDataAsset is null in BindCallbacksToDependencies: %s"), *GetNameSafe(this));
	FAuraAttributeInfo AttributeInfoFound = AttributeInfoDataAsset->FindAttributeInfoForTag(AuraGameplayTags::AttributeTag_Primary_Strength);
	AttributeInfoFound.AttributeValue = AuraAttributeSet->GetStrength();
	OnAttributeInfoChanged.Broadcast(AttributeInfoFound);
}

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	
}
