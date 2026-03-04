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
	void GiveStartUpAbilitiesAndActivateOnce(const TArray<TSubclassOf<UGameplayAbility>>& StartUpAbilities);
	
	FEffectAssetTagsDelegate EffectAssetTags;
	
protected:
	void EffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec,
		FActiveGameplayEffectHandle ActiveEffectHandle);
};
