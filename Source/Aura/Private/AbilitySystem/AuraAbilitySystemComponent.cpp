// No Copyright


#include "AbilitySystem/AuraAbilitySystemComponent.h"

void UAuraAbilitySystemComponent::CharacterAbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UAuraAbilitySystemComponent::EffectApplied);
}

void UAuraAbilitySystemComponent::GiveStartUpAbilitiesAndActivateOnce(const TArray<TSubclassOf<UGameplayAbility>>& StartUpAbilities)
{
	for (const TSubclassOf<UGameplayAbility>& AbilityClass : StartUpAbilities)
	{
		if (!AbilityClass) continue;
		
		FGameplayAbilitySpec AbilitySpec(AbilityClass);
		AbilitySpec.SourceObject = GetAvatarActor();
		AbilitySpec.Level = 1;
		
		//GiveAbility(AbilitySpec);
		GiveAbilityAndActivateOnce(AbilitySpec);
	}
}

void UAuraAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec,
	FActiveGameplayEffectHandle ActiveEffectHandle)
{
	FGameplayTagContainer AssetTags;
	EffectSpec.GetAllAssetTags(AssetTags);
	
	EffectAssetTags.Broadcast(AssetTags);
}
