// Paradise_NiseMono all rights reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GenericTeamAgentInterface.h"
#include "KlotoRobotController.generated.h"

/**
 * 
 */
UCLASS()
class KLOTO_API AKlotoRobotController : public APlayerController, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	AKlotoRobotController();

	//~ Begin IGenericTeamAgentInterface Interface
	virtual FGenericTeamId GetGenericTeamId() const override;
	//~ End IGenericTeamAgentInterface Interface

private:
	FGenericTeamId RobotTeamID;
};
