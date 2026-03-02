// No Copyright

#pragma once

#include "CoreMinimal.h"
#include "UI/Controller/AuraWidgetController.h"
#include "AttributeMenuWidgetController.generated.h"

class UDataAsset_AuraAttributeInfo;
struct FAuraAttributeInfo;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAuraAttributeInfoSignature, const FAuraAttributeInfo&, AttributeInfo);

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class AURA_API UAttributeMenuWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()
	
public:
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;
	
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FAuraAttributeInfoSignature OnAttributeInfoChanged;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WidgetData")
	TObjectPtr<UDataAsset_AuraAttributeInfo> AttributeInfoDataAsset;
};
