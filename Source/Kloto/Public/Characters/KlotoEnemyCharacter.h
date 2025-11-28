// Paradise_NiseMono all rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Characters/KlotoBaseCharacter.h"
#include "KlotoEnemyCharacter.generated.h"

class UEnemyCombatComponent;
/**
 * 
 */
UCLASS()
class KLOTO_API AKlotoEnemyCharacter : public AKlotoBaseCharacter
{
	GENERATED_BODY()

public:
	AKlotoEnemyCharacter();
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	UEnemyCombatComponent* EnemyCombatComponent;

	//~ Begin APawn	Interface
	virtual void PossessedBy(AController* NewController) override;
	//~ End APawn Interface

private:
	void InitEnemyStartUpData();
public:
	FORCEINLINE UEnemyCombatComponent* GetEnemyCombatComponent() const { return EnemyCombatComponent; }
};
