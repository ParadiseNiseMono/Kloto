// Paradise_NiseMono all rights reserved


#include "Components/Combat/RobotCombatComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "KlotoDebugHelper.h"
#include "KlotoGameplayTags.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "Items/Weapons/KlotoRobotWeapon.h"

AKlotoRobotWeapon* URobotCombatComponent::GetRobotCarriedWeaponByTag(FGameplayTag InWeaponTag) const
{
	return Cast<AKlotoRobotWeapon>(GetCharacterCarriedWeaponByTag(InWeaponTag));
}

AKlotoRobotWeapon* URobotCombatComponent::GetRobotCurrentEquippedWeapon() const
{
	return Cast<AKlotoRobotWeapon>(GetCharacterCurrentEquippedWeapon());
}

float URobotCombatComponent::GetRobotCurrentEquippedWeaponDamageAtLevel(int32 InLevel) const
{
	return GetRobotCurrentEquippedWeapon()->RobotWeaponData.WeaponBaseDamage.GetValueAtLevel(InLevel);
}

void URobotCombatComponent::OnHitTargetActor(AActor* HitActor)
{
	if (OverlappedActors.Contains(HitActor)) return;

	OverlappedActors.AddUnique(HitActor);

	FGameplayEventData Data;
	Data.Instigator = GetOwner();
	Data.Target = HitActor;
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwner(), KlotoGameplayTags::Shared_Event_MeleeHit, Data);
}

void URobotCombatComponent::OnWeaponPulledFromTargetActor(AActor* InteractedActor)
{
	
}
