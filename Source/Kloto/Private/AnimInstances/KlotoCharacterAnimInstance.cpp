// Paradise_NiseMono all rights reserved


#include "AnimInstances/KlotoCharacterAnimInstance.h"

#include "Characters/KlotoBaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UKlotoCharacterAnimInstance::NativeInitializeAnimation()
{
	OwingCharacter = Cast<AKlotoBaseCharacter>(TryGetPawnOwner());

	if (OwingCharacter)
	{
		OwingMovementComponent = OwingCharacter->GetCharacterMovement();
	}
}

void UKlotoCharacterAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	if (!OwingCharacter || !OwingMovementComponent) return;

	GroundSpeed = OwingCharacter->GetVelocity().Size2D();

	bHasAcceleration = OwingMovementComponent->GetCurrentAcceleration().SizeSquared2D() > 0.f;
}
