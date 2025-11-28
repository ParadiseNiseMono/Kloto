// Paradise_NiseMono all rights reserved

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/KlotoGameplayAbility.h"
#include "KlotoEnemyGameplayAbility.generated.h"

class UEnemyCombatComponent;
class AKlotoEnemyCharacter;
/**
 * 
 */
UCLASS()
class KLOTO_API UKlotoEnemyGameplayAbility : public UKlotoGameplayAbility
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure)
	AKlotoEnemyCharacter* GetKlotoEnemyCharacterFromActorInfo();

	UFUNCTION(BlueprintPure)
	UEnemyCombatComponent* GetEnemyCombatComponentFormActorInfo();

private:
	TWeakObjectPtr<AKlotoEnemyCharacter> CachedKlotoEnemyCharacter;
};
