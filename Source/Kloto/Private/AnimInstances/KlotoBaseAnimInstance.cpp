// Paradise_NiseMono all rights reserved


#include "AnimInstances/KlotoBaseAnimInstance.h"

#include "KlotoFunctionLibrary.h"

bool UKlotoBaseAnimInstance::DoesOwnerHasTag(FGameplayTag TagToCheck) const
{
	if (APawn* OwningPawn = TryGetPawnOwner())
	{
		return UKlotoFunctionLibrary::NativeDoesActorHasTag(OwningPawn, TagToCheck);
	}
	return false;
}
