// Paradise_NiseMono all rights reserved


#include "KlotoTypes/KlotoStructTypes.h"

#include "AbilitySystem/Abilities/KlotoRobotGameplayAbility.h"

bool FKlotoRobotAbilitySet::IsValid() const
{
	return InputTag.IsValid() && AbilityToGrant;
}
