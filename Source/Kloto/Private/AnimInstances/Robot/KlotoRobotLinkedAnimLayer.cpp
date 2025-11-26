// Paradise_NiseMono all rights reserved


#include "AnimInstances/Robot/KlotoRobotLinkedAnimLayer.h"

#include "AnimInstances/Robot/KlotoRobotAnimInstance.h"

UKlotoRobotAnimInstance* UKlotoRobotLinkedAnimLayer::GetRobotAnimInstance() const
{
	return Cast<UKlotoRobotAnimInstance>(GetOwningComponent()->GetAnimInstance());
}
