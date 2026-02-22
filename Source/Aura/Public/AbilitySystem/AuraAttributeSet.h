// No Copyright

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AttributeSet.h"
#include "AuraAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

USTRUCT(BlueprintType)
struct FEffectProperties
{
	GENERATED_BODY()
	
	FEffectProperties() {}
	
	FGameplayEffectContextHandle EffectContextHandle;
	
	UPROPERTY(BlueprintReadOnly)
	UAbilitySystemComponent* SourceAbilitySystemComponent = nullptr;
	
	UPROPERTY(BlueprintReadOnly)
	AActor* SourceAvatarActor = nullptr;
	
	UPROPERTY(BlueprintReadOnly)
	AController* SourceController = nullptr;
	
	UPROPERTY(BlueprintReadOnly)
	ACharacter* SourceCharacter = nullptr;
	
	UPROPERTY(BlueprintReadOnly)
	UAbilitySystemComponent* TargetAbilitySystemComponent = nullptr;
	
	UPROPERTY(BlueprintReadOnly)
	AActor* TargetAvatarActor = nullptr;
	
	UPROPERTY(BlueprintReadOnly)
	AController* TargetController = nullptr;
	
	UPROPERTY(BlueprintReadOnly)
	ACharacter* TargetCharacter = nullptr;
};

/**
 * 
 */
UCLASS()
class AURA_API UAuraAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UAuraAttributeSet();
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;
	
	/** ============================================================
	 *                    PRIMARY ATTRIBUTES
	*  Player-invested stats (level ups, gear, etc.)
	*  These DO NOT directly affect gameplay.
	*  They are used to DERIVE secondary attributes.
	*  ============================================================ */

	/** Strength
	* Increases physical damage output.
	* Used to scale melee and physical abilities.
	*/
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Strength, Category = "PrimaryAttributes")
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Strength);

	/** Intelligence
	* Increases magical damage output.
	* Used for spell scaling and mana-related stats.
	*/
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Intelligence, Category = "PrimaryAttributes")
	FGameplayAttributeData Intelligence;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Intelligence);

	/** Resilience
	* Defensive primary stat.
	* Increases Armor and Armor Penetration.
	*/
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Resilience, Category = "PrimaryAttributes")
	FGameplayAttributeData Resilience;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Resilience);

	/** Vigor
	* Health-focused primary stat.
	* Increases Max Health.
	*/
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Vigor, Category = "PrimaryAttributes")
	FGameplayAttributeData Vigor;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Vigor);

	UFUNCTION() void OnRep_Strength(const FGameplayAttributeData& OldStrength) const;
	UFUNCTION() void OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const;
	UFUNCTION() void OnRep_Resilience(const FGameplayAttributeData& OldResilience) const;
	UFUNCTION() void OnRep_Vigor(const FGameplayAttributeData& OldVigor) const;


	/** ============================================================
	*                  SECONDARY ATTRIBUTES
	*  Derived from Primary Attributes via MMC or calculations.
	*  These directly affect combat outcomes.
	*  ============================================================ */

	/** Armor
	* Reduces incoming damage and improves Block Chance.
	* Derived from Resilience.
	*/
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Armor, Category = "SecondaryAttributes")
	FGameplayAttributeData Armor;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Armor);

	/** Armor Penetration
	* Ignores a percentage of enemy Armor when dealing damage.
	* Also increases Critical Hit Chance.
	* Derived from Resilience.
	*/
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ArmorPenetration, Category = "SecondaryAttributes")
	FGameplayAttributeData ArmorPenetration;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, ArmorPenetration);

	/** Block Chance
	* Chance to cut incoming damage in half.
	* Derived from Armor.
	*/
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_BlockChance, Category = "SecondaryAttributes")
	FGameplayAttributeData BlockChance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, BlockChance);

	/** Critical Hit Chance
	* Chance to deal a critical hit (double damage plus bonus).
	* Derived from Armor Penetration.
	*/
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalHitChance, Category = "SecondaryAttributes")
	FGameplayAttributeData CriticalHitChance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, CriticalHitChance);

	/** Critical Hit Damage
	* Bonus damage added when a critical hit is scored.
	*/
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalHitDamage, Category = "SecondaryAttributes")
	FGameplayAttributeData CriticalHitDamage;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, CriticalHitDamage);

	/** Critical Hit Resistance
	* Reduces the critical hit chance of attacking enemies.
	*/
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalHitResistance, Category = "SecondaryAttributes")
	FGameplayAttributeData CriticalHitResistance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, CriticalHitResistance);

	/** Health Regeneration
	* Amount of Health regenerated every second.
	* Derived from Vigor.
	*/
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_HealthRegeneration, Category = "SecondaryAttributes")
	FGameplayAttributeData HealthRegeneration;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, HealthRegeneration);

	/** Mana Regeneration
	* Amount of Mana regenerated every second.
	* Derived from Intelligence.
	*/
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ManaRegeneration, Category = "SecondaryAttributes")
	FGameplayAttributeData ManaRegeneration;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, ManaRegeneration);

	/** Max Health
	* Maximum amount of Health obtainable.
	* Derived from Vigor.
	*/
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "CoreAttributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxHealth);

	/** Max Mana
	* Maximum amount of Mana obtainable.
	* Derived from Intelligence.
	*/
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxMana, Category = "CoreAttributes")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxMana);

	UFUNCTION() void OnRep_Armor(const FGameplayAttributeData& OldArmor) const;
	UFUNCTION() void OnRep_ArmorPenetration(const FGameplayAttributeData& OldArmorPenetration) const;
	UFUNCTION() void OnRep_BlockChance(const FGameplayAttributeData& OldBlockChance) const;
	UFUNCTION() void OnRep_CriticalHitChance(const FGameplayAttributeData& OldCriticalHitChance) const;
	UFUNCTION() void OnRep_CriticalHitDamage(const FGameplayAttributeData& OldCriticalHitDamage) const;
	UFUNCTION() void OnRep_CriticalHitResistance(const FGameplayAttributeData& OldCriticalHitResistance) const;
	UFUNCTION() void OnRep_HealthRegeneration(const FGameplayAttributeData& OldHealthRegeneration) const;
	UFUNCTION() void OnRep_ManaRegeneration(const FGameplayAttributeData& OldManaRegeneration) const;
	UFUNCTION() void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;
	UFUNCTION() void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const;


	/** ============================================================
	*                      CORE ATTRIBUTES
	*  These are the actual runtime gameplay resources.
	*  UI, abilities, and gameplay logic use these directly.
	*  ============================================================ */

	/** Health
	* Current health value.
	* Modified by damage, healing, and regeneration.
	*/
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "CoreAttributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Health);

	/** Mana
	* Current mana value used to cast abilities.
	*/
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Mana, Category = "CoreAttributes")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Mana);

	UFUNCTION() void OnRep_Health(const FGameplayAttributeData& OldHealth) const;
	UFUNCTION() void OnRep_Mana(const FGameplayAttributeData& OldMana) const;
	
private:
	void SetEffectProperties(const struct FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const;
};
