// Paradise_NiseMono all rights reserved

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/KlotoBaseAnimInstance.h"
#include "KlotoCharacterAnimInstance.generated.h"

class UCharacterMovementComponent;
class AKlotoBaseCharacter;
/**
 * 
 */
UCLASS()
class KLOTO_API UKlotoCharacterAnimInstance : public UKlotoBaseAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY()
	AKlotoBaseCharacter* OwingCharacter;

	UPROPERTY()
	UCharacterMovementComponent* OwingMovementComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	float GroundSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	bool bHasAcceleration;
};
