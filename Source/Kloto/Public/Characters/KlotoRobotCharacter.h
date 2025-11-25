// Paradise_NiseMono all rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Characters/KlotoBaseCharacter.h"
#include "KlotoRobotCharacter.generated.h"

/**
 * 
 */
UCLASS()
class KLOTO_API AKlotoRobotCharacter : public AKlotoBaseCharacter
{
	GENERATED_BODY()

public:

protected:
	virtual void BeginPlay() override;
};
