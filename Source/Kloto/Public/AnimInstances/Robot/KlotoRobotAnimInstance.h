// Paradise_NiseMono all rights reserved

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/KlotoCharacterAnimInstance.h"
#include "KlotoRobotAnimInstance.generated.h"

class AKlotoRobotCharacter;
/**
 * 
 */
UCLASS()
class KLOTO_API UKlotoRobotAnimInstance : public UKlotoCharacterAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimData|References")
	AKlotoRobotCharacter* OwingRobotCharacter;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	bool bShouldEnterRelaxState;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	float EnterRelaxStateThreshold = 5.f;

	float IdleElpasedTime;
};
