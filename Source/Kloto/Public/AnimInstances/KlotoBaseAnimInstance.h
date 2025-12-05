// Paradise_NiseMono all rights reserved

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Animation/AnimInstance.h"
#include "KlotoBaseAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class KLOTO_API UKlotoBaseAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintPure, meta=( BlueprintThreadSafe))
	bool DoesOwnerHasTag(FGameplayTag TagToCheck) const;
};
