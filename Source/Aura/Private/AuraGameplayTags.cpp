// No Copyright


#include "AuraGameplayTags.h"

namespace AuraGameplayTags
{
	/** Input Tags **/
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(InputTag_Move, "InputTag.Move",
		"Input tag for character movement input");
	
	/** Vital Attribute Tags **/
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(AttributeTag_Vital_Health, "AttributeTag.Vital.Health",
		"Current health value, modified by damage, healing, and regeneration");

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(AttributeTag_Vital_Mana, "AttributeTag.Vital.Mana",
		"Current mana resource used for casting abilities");
	
	/** Primary Attribute Tags **/
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(AttributeTag_Primary_Strength, "AttributeTag.Primary.Strength",
		"Increases physical damage output and scales melee abilities");

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(AttributeTag_Primary_Intelligence, "AttributeTag.Primary.Intelligence",
		"Increases magical damage output and improves mana-related stats");

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(AttributeTag_Primary_Resilience, "AttributeTag.Primary.Resilience",
		"Defensive stat that increases Armor and Armor Penetration");

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(AttributeTag_Primary_Vigor, "AttributeTag.Primary.Vigor",
		"Increases maximum health and overall survivability");
	
	/** Secondary Attribute Tags **/
	UE_DEFINE_GAMEPLAY_TAG(AttributeTag_Vital_MaxHealth, "AttributeTag.Vital.MaxHealth");
	UE_DEFINE_GAMEPLAY_TAG(AttributeTag_Vital_MaxMana, "AttributeTag.Vital.MaxMana");
	
	/** Message Tags **/
	UE_DEFINE_GAMEPLAY_TAG(MessageTag_HealthPotion, "MessageTag.HealthPotion");
	UE_DEFINE_GAMEPLAY_TAG(MessageTag_ManaPotion, "MessageTag.ManaPotion");
	UE_DEFINE_GAMEPLAY_TAG(MessageTag_HealthCrystal, "MessageTag.HealthCrystal");
	UE_DEFINE_GAMEPLAY_TAG(MessageTag_ManaCrystal, "MessageTag.ManaCrystal");
}
