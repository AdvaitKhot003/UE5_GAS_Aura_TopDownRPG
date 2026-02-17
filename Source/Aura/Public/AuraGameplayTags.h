// No Copyright

#pragma once

#include "NativeGameplayTags.h"

namespace AuraGameplayTags
{
	/** Input Tags **/
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Move);
	
	/** Attribute Tags **/
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(AttributeTag_Vital_Health);
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(AttributeTag_Vital_Mana);
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(AttributeTag_Vital_MaxHealth);
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(AttributeTag_Vital_MaxMana);
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(AttributeTag_Primary_Strength);
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(AttributeTag_Primary_Intelligence);
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(AttributeTag_Primary_Resilience);
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(AttributeTag_Primary_Vigor);
	
	/** Message Tags **/
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(MessageTag_HealthPotion);
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(MessageTag_ManaPotion);
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(MessageTag_HealthCrystal);
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(MessageTag_ManaCrystal);
}
