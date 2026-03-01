// No Copyright

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AuraAbilitySystemFunctionLibrary.generated.h"

struct FWidgetControllerParams;
class UOverlayWidgetController;

/**
 * 
 */
UCLASS()
class AURA_API UAuraAbilitySystemFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, Category = "AuraAbilitySystemFunctionLibrary|WidgetController")
	static UOverlayWidgetController* BP_GetOverlayWidgetController(const UObject* WorldContextObject);
};
