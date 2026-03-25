// No Copyright


#include "AbilitySystem/Abilities/AuraProjectileSpellAbility.h"
#include "Actor/AuraProjectile.h"
#include "Interaction/CombatInterface.h"

void UAuraProjectileSpellAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UAuraProjectileSpellAbility::SpawnProjectile()
{
	if (!GetAvatarActorFromActorInfo()->HasAuthority()) return;

	if (ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo()))
	{
		const FVector SocketLocation = CombatInterface->GetCombatSocketLocation();
		const FTransform SpawnTransform(SocketLocation);
		APawn* AvatarInstigatorPawn = Cast<APawn>(GetAvatarActorFromActorInfo());

		AAuraProjectile* Projectile = GetWorld()->SpawnActorDeferred<AAuraProjectile>(
			AuraProjectileClass,
			SpawnTransform,
			GetAvatarActorFromActorInfo(),
			AvatarInstigatorPawn,
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn
		);

		Projectile->FinishSpawning(SpawnTransform);
	}
}
