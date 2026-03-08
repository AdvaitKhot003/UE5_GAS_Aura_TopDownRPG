// No Copyright


#include "AbilitySystem/Abilities/AuraProjectileSpellAbility.h"
#include "Kismet/KismetSystemLibrary.h"

void UAuraProjectileSpellAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	UKismetSystemLibrary::PrintString(this, TEXT("Aura Projectile Spell Ability Activated"),
		true, true, FLinearColor::MakeRandomColor(), 10.f);
}
