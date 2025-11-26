// Paradise_NiseMono all rights reserved


#include "Components/Combat/RobotCombatComponent.h"

#include "Items/Weapons/KlotoRobotWeapon.h"

AKlotoRobotWeapon* URobotCombatComponent::GetRobotCarriedWeaponByTag(FGameplayTag InWeaponTag) const
{
	return Cast<AKlotoRobotWeapon>(GetCharacterCarriedWeaponByTag(InWeaponTag));
}
