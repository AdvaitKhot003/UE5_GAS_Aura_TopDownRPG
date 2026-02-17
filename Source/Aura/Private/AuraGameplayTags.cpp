// No Copyright


#include "AuraGameplayTags.h"

namespace AuraGameplayTags
{
	/** Input Tags **/
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Move, "InputTag.Move");
	
	/** Attribute Tags **/
	UE_DEFINE_GAMEPLAY_TAG(AttributeTag_Vital_Health, "AttributeTag.Vital.Health");
	UE_DEFINE_GAMEPLAY_TAG(AttributeTag_Vital_Mana, "AttributeTag.Vital.Mana");
	UE_DEFINE_GAMEPLAY_TAG(AttributeTag_Vital_MaxHealth, "AttributeTag.Vital.MaxHealth");
	UE_DEFINE_GAMEPLAY_TAG(AttributeTag_Vital_MaxMana, "AttributeTag.Vital.MaxMana");
	UE_DEFINE_GAMEPLAY_TAG(AttributeTag_Primary_Strength, "AttributeTag.Primary.Strength");
	UE_DEFINE_GAMEPLAY_TAG(AttributeTag_Primary_Intelligence, "AttributeTag.Primary.Intelligence");
	UE_DEFINE_GAMEPLAY_TAG(AttributeTag_Primary_Resilience, "AttributeTag.Primary.Resilience");
	UE_DEFINE_GAMEPLAY_TAG(AttributeTag_Primary_Vigor, "AttributeTag.Primary.Vigor");
	
	/** Message Tags **/
	UE_DEFINE_GAMEPLAY_TAG(MessageTag_HealthPotion, "MessageTag.HealthPotion");
	UE_DEFINE_GAMEPLAY_TAG(MessageTag_ManaPotion, "MessageTag.ManaPotion");
	UE_DEFINE_GAMEPLAY_TAG(MessageTag_HealthCrystal, "MessageTag.HealthCrystal");
	UE_DEFINE_GAMEPLAY_TAG(MessageTag_ManaCrystal, "MessageTag.ManaCrystal");
}
