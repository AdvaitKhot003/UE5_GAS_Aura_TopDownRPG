// No Copyright


#include "Character/AuraEnemy.h"
#include "Components/CapsuleComponent.h"
#include "Aura/Aura.h"

AAuraEnemy::AAuraEnemy()
{
	UCapsuleComponent* Capsule = GetCapsuleComponent();

	Capsule->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Capsule->SetCollisionObjectType(ECC_Pawn);

	// Start clean
	Capsule->SetCollisionResponseToAllChannels(ECR_Ignore);

	// Required collisions
	Capsule->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block); // ground
	Capsule->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block); // Movable Objects
	Capsule->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block); // other characters

	// Cursor hover
	Capsule->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	// Optional
	Capsule->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);

	// Mesh = visuals only
	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));
}

void AAuraEnemy::HighlightActor()
{
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	WeaponMesh->SetRenderCustomDepth(true);
	WeaponMesh->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
}

void AAuraEnemy::UnhighlightActor()
{
	GetMesh()->SetRenderCustomDepth(false);
	WeaponMesh->SetRenderCustomDepth(false);
}
