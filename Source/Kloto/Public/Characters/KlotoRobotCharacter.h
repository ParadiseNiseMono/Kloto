// Paradise_NiseMono all rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Characters/KlotoBaseCharacter.h"
#include "KlotoRobotCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
/**
 * 
 */
UCLASS()
class KLOTO_API AKlotoRobotCharacter : public AKlotoBaseCharacter
{
	GENERATED_BODY()

public:
	AKlotoRobotCharacter();
protected:
	virtual void BeginPlay() override;

private:
	
#pragma region Components
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
#pragma endregion	
};
