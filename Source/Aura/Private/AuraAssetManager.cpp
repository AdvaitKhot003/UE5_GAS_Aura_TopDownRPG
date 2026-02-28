// No Copyright


#include "AuraAssetManager.h"

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
}
