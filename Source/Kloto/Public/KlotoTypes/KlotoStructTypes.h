// Paradise_NiseMono all rights reserved

#pragma once

#include "KlotoStructTypes.generated.h"

class UKlotoRobotLinkedAnimLayer;

USTRUCT(BlueprintType)
struct FKlotoRobotWeaponData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UKlotoRobotLinkedAnimLayer> WeaponAnimLayerToLink; 
};