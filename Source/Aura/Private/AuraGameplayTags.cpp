// No Copyright


#include "AuraGameplayTags.h"

namespace AuraGameplayTags
{
	/** Input Tags **/
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(InputTag_Move, "InputTag.Move",
		"Input tag for character movement input");
	
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(InputTag_Shift, "InputTag.Shift",
		"Input tag for Shift Key Input");
	
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(InputTag_LMB, "InputTag.LMB",
		"Input tag for left mouse button");
	
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(InputTag_RMB, "InputTag.RMB",
		"Input tag for right mouse button");
	
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(InputTag_1, "InputTag.1",
		"Input tag for 1 key on keyboard");
	
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(InputTag_2, "InputTag.2",
		"Input tag for 2 key on keyboard");
	
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(InputTag_3, "InputTag.3",
		"Input tag for 3 key on keyboard");
	
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(InputTag_4, "InputTag.4",
		"Input tag for 4 key on keyboard");
	
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
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(AttributeTag_Secondary_Armor, "AttributeTag.Secondary.Armor",
		"Reduces incoming damage and increases Block Chance; derived from Resilience");

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(AttributeTag_Secondary_ArmorPenetration, "AttributeTag.Secondary.ArmorPenetration",
		"Ignores a percentage of enemy Armor and increases Critical Hit Chance");

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(AttributeTag_Secondary_BlockChance, "AttributeTag.Secondary.BlockChance",
		"Chance to block incoming attacks and reduce their damage");

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(AttributeTag_Secondary_CriticalHitChance, "AttributeTag.Secondary.CriticalHitChance",
		"Chance to deal a critical hit for increased damage");

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(AttributeTag_Secondary_CriticalHitDamage, "AttributeTag.Secondary.CriticalHitDamage",
		"Bonus damage applied when a critical hit occurs");

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(AttributeTag_Secondary_CriticalHitResistance, "AttributeTag.Secondary.CriticalHitResistance",
		"Reduces incoming enemy critical hit chance");

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(AttributeTag_Secondary_HealthRegeneration, "AttributeTag.Secondary.HealthRegeneration",
		"Amount of health regenerated per second; derived from Vigor");

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(AttributeTag_Secondary_ManaRegeneration, "AttributeTag.Secondary.ManaRegeneration",
		"Amount of mana regenerated per second; derived from Intelligence");
	
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(AttributeTag_Secondary_MaxHealth, "AttributeTag.Secondary.MaxHealth",
		"Maximum health capacity derived from Vigor");

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(AttributeTag_Secondary_MaxMana, "AttributeTag.Secondary.MaxMana",
		"Maximum mana capacity derived from Intelligence");
	
	/** Event Tags **/
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(EventTag_Montage_FireBolt, "EventTag.Montage.FireBolt", 
		"Fired during FireBolt montage to trigger gameplay events.");
	
	/** Message Tags **/
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(MessageTag_HealthPotion, "MessageTag.HealthPotion",
		"Triggered when player picks up a health potion to restore health and update UI");

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(MessageTag_ManaPotion, "MessageTag.ManaPotion",
		"Triggered when player picks up a mana potion to restore mana and update UI");

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(MessageTag_HealthCrystal, "MessageTag.HealthCrystal",
		"Triggered when player collects a health crystal for instant or bonus healing");

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(MessageTag_ManaCrystal, "MessageTag.ManaCrystal",
		"Triggered when player collects a mana crystal for instant or bonus mana");
}
