// No Copyright

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "AuraEnemy.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraEnemy : public AAuraCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()
	
public:
	AAuraEnemy();
	
	virtual void HighlightActor() override;
	virtual void UnhighlightActor() override;
	
	virtual int32 GetCharacterLevel() override;
	
protected:
	virtual void BeginPlay() override;
	virtual void InitCharacterAbilityActorInfo() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GAS|Attributes")
	int32 EnemyLevel = 1;
};
