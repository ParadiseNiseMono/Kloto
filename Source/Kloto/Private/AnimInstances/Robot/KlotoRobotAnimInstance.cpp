// Paradise_NiseMono all rights reserved


#include "AnimInstances/Robot/KlotoRobotAnimInstance.h"

#include "Characters/KlotoRobotCharacter.h"

void UKlotoRobotAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	if (OwingCharacter)
	{
		OwingRobotCharacter = Cast<AKlotoRobotCharacter>(OwingCharacter);
	}
}

void UKlotoRobotAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);

	if (bHasAcceleration)
	{
		IdleElpasedTime = 0.f;
		bShouldEnterRelaxState = false;
	}
	else
	{
		IdleElpasedTime += DeltaSeconds;
		bShouldEnterRelaxState = (IdleElpasedTime >= EnterRelaxStateThreshold);
	}
}
