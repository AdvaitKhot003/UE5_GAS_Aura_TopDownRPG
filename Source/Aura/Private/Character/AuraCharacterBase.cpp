// No Copyright


#include "Character/AuraCharacterBase.h"
#include "Components/CapsuleComponent.h"
#include "AbilitySystemComponent.h"

AAuraCharacterBase::AAuraCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;
	
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);
	
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	WeaponMesh->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
}

UAbilitySystemComponent* AAuraCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AAuraCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAuraCharacterBase::InitCharacterAbilityActorInfo()
{
	
}

void AAuraCharacterBase::InitializePrimaryAttributes()
{
	if (!HasAuthority()) return;
	
	checkf(DefaultPrimaryAttributes,
		TEXT("DefaultPrimaryAttributes is null in InitializePrimaryAttributes: %s"), *GetActorNameOrLabel());
	
	UAbilitySystemComponent* SourceASC = GetAbilitySystemComponent();
	
	if (!SourceASC) return;
	
	FGameplayEffectContextHandle EffectContextHandle = SourceASC->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);
	
	const FGameplayEffectSpecHandle EffectSpecHandle =
		SourceASC->MakeOutgoingSpec(DefaultPrimaryAttributes, 1.f, EffectContextHandle);
	
	if (!EffectSpecHandle.IsValid()) return;
	
	const FGameplayEffectSpec& EffectSpec = *EffectSpecHandle.Data.Get();
	SourceASC->ApplyGameplayEffectSpecToTarget(EffectSpec, SourceASC);
}
