// No Copyright

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AuraHUD.generated.h"

class UAuraUserWidget;

/**
 * 
 */
UCLASS()
class AURA_API AAuraHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	TObjectPtr<UAuraUserWidget> OverlayWidget;
	
protected:
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "HUD", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UAuraUserWidget> OverlayWidgetClass;
};
