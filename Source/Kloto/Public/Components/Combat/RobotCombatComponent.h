// Paradise_NiseMono all rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/Combat/PawnCombatComponent.h"
#include "RobotCombatComponent.generated.h"

class AKlotoRobotWeapon;
/**
 * 
 */
UCLASS()
class KLOTO_API URobotCombatComponent : public UPawnCombatComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Kloto|Combat")
	AKlotoRobotWeapon* GetRobotCarriedWeaponByTag(FGameplayTag InWeaponTag) const;
};
