// No Copyright


#include "AuraAssetManager.h"
#include "AbilitySystemGlobals.h"

UAuraAssetManager& UAuraAssetManager::Get()
{
	checkf(GEngine, TEXT("GEngine is null in UAuraAssetManager"));
	UAuraAssetManager* AuraAssetManager = Cast<UAuraAssetManager>(GEngine->AssetManager);
	checkf(AuraAssetManager, TEXT("AuraAssetManager is null in UAuraAssetManager"));
	return *AuraAssetManager;
}

void UAuraAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	
	// This Is Required To Use Target Data
	UAbilitySystemGlobals::Get().InitGlobalData();
}
