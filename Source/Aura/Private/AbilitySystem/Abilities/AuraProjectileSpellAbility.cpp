// No Copyright


#include "AbilitySystem/Abilities/AuraProjectileSpellAbility.h"
#include "Actor/AuraProjectile.h"
#include "Interaction/CombatInterface.h"

void UAuraProjectileSpellAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UAuraProjectileSpellAbility::SpawnProjectile(const FVector& ProjectileTargetLocation)
{
	const bool bHasAuthority = GetAvatarActorFromActorInfo()->HasAuthority();
	UE_LOG(LogTemp, Warning, TEXT("SpawnProjectile Authority: %d"), bHasAuthority);

	if (!bHasAuthority) return;

	if (ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo()))
	{
		const FVector SocketLocation = CombatInterface->GetCombatSocketLocation();
		FRotator ProjectileRotation = (ProjectileTargetLocation - SocketLocation).Rotation();
		ProjectileRotation.Pitch = 0.f;
		
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(SocketLocation);
		SpawnTransform.SetRotation(ProjectileRotation.Quaternion());
		
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
