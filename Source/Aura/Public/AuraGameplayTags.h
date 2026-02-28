// No Copyright

#pragma once

#include "NativeGameplayTags.h"

namespace AuraGameplayTags
{
	/** Input Tags **/
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Move);
	
	/** Vital Attribute Tags **/
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(AttributeTag_Vital_Health);
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(AttributeTag_Vital_Mana);
	
	/** Primary Attribute Tags **/
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(AttributeTag_Primary_Strength);
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(AttributeTag_Primary_Intelligence);
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(AttributeTag_Primary_Resilience);
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(AttributeTag_Primary_Vigor);
	
	/** Secondary Attribute Tags **/
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(AttributeTag_Secondary_Armor);
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(AttributeTag_Secondary_ArmorPenetration);
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(AttributeTag_Secondary_BlockChance);
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(AttributeTag_Secondary_CriticalHitChance);
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(AttributeTag_Secondary_CriticalHitDamage);
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(AttributeTag_Secondary_CriticalHitResistance);
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(AttributeTag_Secondary_HealthRegeneration);
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(AttributeTag_Secondary_ManaRegeneration);
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(AttributeTag_Secondary_MaxHealth);
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(AttributeTag_Secondary_MaxMana);
	
	/** Message Tags **/
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(MessageTag_HealthPotion);
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(MessageTag_ManaPotion);
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(MessageTag_HealthCrystal);
	AURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(MessageTag_ManaCrystal);
}
