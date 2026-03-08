// No Copyright

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AuraAbilitySystemComponent.generated.h"

class UGameplayAbility;
DECLARE_MULTICAST_DELEGATE_OneParam(FEffectAssetTagsDelegate, const FGameplayTagContainer&)

/**
 * 
 */
UCLASS()
class AURA_API UAuraAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
public:
	void CharacterAbilityActorInfoSet();
	void GiveStartUpAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartUpAbilities);
	
	void OnInputAbilityPressed(const FGameplayTag& InputTag);
	void OnInputAbilityReleased(const FGameplayTag& InputTag);
	void OnInputAbilityHeld(const FGameplayTag& InputTag);
	
	FEffectAssetTagsDelegate EffectAssetTags;
	
protected:
	UFUNCTION(Client, Reliable)
	void ClientEffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec,
		FActiveGameplayEffectHandle ActiveEffectHandle);
};
