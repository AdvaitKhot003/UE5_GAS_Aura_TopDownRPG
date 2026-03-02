// No Copyright

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AuraAbilitySystemFunctionLibrary.generated.h"

class UAttributeMenuWidgetController;
class UOverlayWidgetController;

/**
 * 
 */
UCLASS()
class AURA_API UAuraAbilitySystemFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, Category="Aura|WidgetController", meta = (WorldContext="WorldContextObject"))
	static UOverlayWidgetController* BP_GetOverlayWidgetController(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category="Aura|WidgetController", meta = (WorldContext="WorldContextObject"))
	static UAttributeMenuWidgetController* BP_GetAttributeMenuWidgetController(const UObject* WorldContextObject);
};
