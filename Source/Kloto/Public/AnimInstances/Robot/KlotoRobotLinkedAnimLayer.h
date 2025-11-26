// Paradise_NiseMono all rights reserved

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/KlotoBaseAnimInstance.h"
#include "KlotoRobotLinkedAnimLayer.generated.h"

class UKlotoRobotAnimInstance;
/**
 * 
 */
UCLASS()
class KLOTO_API UKlotoRobotLinkedAnimLayer : public UKlotoBaseAnimInstance
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, meta=(BlueprintThreadSafe))
	UKlotoRobotAnimInstance* GetRobotAnimInstance() const;
};
