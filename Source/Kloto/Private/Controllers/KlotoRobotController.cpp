// Paradise_NiseMono all rights reserved


#include "Controllers/KlotoRobotController.h"

AKlotoRobotController::AKlotoRobotController()
{
	RobotTeamID = FGenericTeamId(0);
}

FGenericTeamId AKlotoRobotController::GetGenericTeamId() const
{
	return RobotTeamID;
}
