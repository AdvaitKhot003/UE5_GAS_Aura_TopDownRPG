// No Copyright


#include "AbilitySystem/Data/DataAsset_AuraAttributeInfo.h"

FAuraAttributeInfo UDataAsset_AuraAttributeInfo::FindAttributeInfoByTag(const FGameplayTag& InAttributeTag, bool bAttributeInfoNotFound) const
{
	for (const FAuraAttributeInfo& AttributeInfo : AttributeInfos)
	{
		if (AttributeInfo.IsValid() && AttributeInfo.AttributeTag == InAttributeTag)
		{
			return AttributeInfo;
		}
	}
	
	if (bAttributeInfoNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("AttributeInfo not found for tag: %s in AttributeInfo: %s"), *InAttributeTag.ToString(), *GetNameSafe(this));
	}
	return FAuraAttributeInfo();
}
