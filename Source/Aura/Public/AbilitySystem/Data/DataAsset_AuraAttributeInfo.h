// No Copyright

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "DataAsset_AuraAttributeInfo.generated.h"

USTRUCT(BlueprintType)
struct FAuraAttributeInfo
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "AttributeTag"))
	FGameplayTag AttributeTag = FGameplayTag();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText AttributeName = FText();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText AttributeDescription = FText();
	
	UPROPERTY(BlueprintReadOnly)
	float AttributeValue = 0.f;
	
	bool IsValid() const
	{
		return AttributeTag.IsValid() && !AttributeName.IsEmpty() && !AttributeDescription.IsEmpty();
	}
};

/**
 * 
 */
UCLASS()
class AURA_API UDataAsset_AuraAttributeInfo : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (TitleProperty = "AttributeTag"))
	TArray<FAuraAttributeInfo> AttributeInfos;

	FAuraAttributeInfo FindAttributeInfoByTag(const FGameplayTag& InAttributeTag, bool bAttributeInfoNotFound = false) const;
};
