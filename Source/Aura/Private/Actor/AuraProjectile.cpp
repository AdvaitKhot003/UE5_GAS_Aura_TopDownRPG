// No Copyright


#include "Actor/AuraProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/AudioComponent.h"

AAuraProjectile::AAuraProjectile()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	SetRootComponent(SphereComponent);
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::Type::QueryOnly);
	SphereComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	//SphereComponent->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	SphereComponent->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Overlap);
	SphereComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->SetUpdatedComponent(SphereComponent);
	ProjectileMovementComponent->InitialSpeed = 500.f;
	ProjectileMovementComponent->MaxSpeed = 500.f;
	ProjectileMovementComponent->ProjectileGravityScale = 0.f;
}

void AAuraProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AAuraProjectile::OnSphereComponentBeginOverlap);
	
	SetLifeSpan(ProjectileLifeSpan);
	
	checkf(ProjectileLoopingSound, TEXT("ProjectileLoopingSound is not set in %s"), *GetActorNameOrLabel());
	
	ProjectileLoopingAudioComponent = UGameplayStatics::SpawnSoundAttached(
		ProjectileLoopingSound,
		GetRootComponent(),
		NAME_None,
		FVector::ZeroVector,
		EAttachLocation::KeepRelativeOffset,
		true);
}

void AAuraProjectile::Destroyed()
{
	if (!bHasCollided)
	{
		bHasCollided = true;
		PlayImpactFX();
	}

	Super::Destroyed();
}

void AAuraProjectile::OnSphereComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (bHasCollided) return;

	bHasCollided = true;
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SphereComponent->OnComponentBeginOverlap.RemoveAll(this);

	PlayImpactFX();

	if (HasAuthority())
	{
		Destroy();
	}
}

void AAuraProjectile::PlayImpactFX() const
{
	checkf(ProjectileHitSound, TEXT("ProjectileHitSound is not set in %s"), *GetActorNameOrLabel());
	checkf(ProjectileHitEffect, TEXT("ProjectileHitEffect is not set in %s"), *GetActorNameOrLabel());
	
	UGameplayStatics::PlaySoundAtLocation(this, ProjectileHitSound, GetActorLocation());
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ProjectileHitEffect, GetActorLocation());
	
	if (ProjectileLoopingAudioComponent && ProjectileLoopingAudioComponent->IsPlaying())
	{
		//ProjectileLoopingAudioComponent->Stop();
		ProjectileLoopingAudioComponent->FadeOut(0.1f, 0.f);
	}
}
