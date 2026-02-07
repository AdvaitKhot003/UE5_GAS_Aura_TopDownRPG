// No Copyright


#include "UI/HUD/AuraHUD.h"
#include "UI/Widget/AuraUserWidget.h"
#include "UI/Controller/OverlayWidgetController.h"

UOverlayWidgetController* AAuraHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	if (OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(WCParams);
	}
	return OverlayWidgetController;
}

void AAuraHUD::InitOverlayWidget(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	checkf(OverlayWidgetClass, TEXT("OverlayWidgetClass is null in InitOverlay: %s"), *GetActorNameOrLabel());
	checkf(OverlayWidgetControllerClass, TEXT("OverlayWidgetControllerClass is null in InitOverlay: %s"), *GetActorNameOrLabel());
	
	OverlayWidget = CreateWidget<UAuraUserWidget>(GetWorld(), OverlayWidgetClass);
	if (OverlayWidget)
	{
		const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
		UOverlayWidgetController* OWC = GetOverlayWidgetController(WidgetControllerParams);
		OverlayWidget->SetWidgetController(OWC);
		OWC->BroadcastInitialValues();
		OverlayWidget->AddToViewport();
	}
}
