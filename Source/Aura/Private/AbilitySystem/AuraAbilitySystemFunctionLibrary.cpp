// No Copyright


#include "AbilitySystem/AuraAbilitySystemFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "UI/HUD/AuraHUD.h"
#include "Controller/AuraPlayerState.h"
#include "UI/Controller/AuraWidgetController.h"

UOverlayWidgetController* UAuraAbilitySystemFunctionLibrary::BP_GetOverlayWidgetController(const UObject* WorldContextObject)
{
	if (!WorldContextObject) return nullptr;

	APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0);
	if (!PC) return nullptr;

	AAuraHUD* AuraHUD = Cast<AAuraHUD>(PC->GetHUD());
	if (!AuraHUD) return nullptr;

	AAuraPlayerState* PS = PC->GetPlayerState<AAuraPlayerState>();
	if (!PS) return nullptr;

	UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
	UAttributeSet* AS = PS->GetAttributeSet();

	if (!ASC || !AS) return nullptr;

	const FWidgetControllerParams Params(PC, PS, ASC, AS);
	return AuraHUD->GetOverlayWidgetController(Params);
}

UAttributeMenuWidgetController* UAuraAbilitySystemFunctionLibrary::BP_GetAttributeMenuWidgetController(const UObject* WorldContextObject)
{
	if (!WorldContextObject) return nullptr;

	APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0);
	if (!PC) return nullptr;

	AAuraHUD* AuraHUD = Cast<AAuraHUD>(PC->GetHUD());
	if (!AuraHUD) return nullptr;

	AAuraPlayerState* PS = PC->GetPlayerState<AAuraPlayerState>();
	if (!PS) return nullptr;

	UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
	UAttributeSet* AS = PS->GetAttributeSet();

	if (!ASC || !AS) return nullptr;

	const FWidgetControllerParams Params(PC, PS, ASC, AS);
	return AuraHUD->GetAttributeMenuWidgetController(Params);
}
