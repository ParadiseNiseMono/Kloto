// Paradise_NiseMono all rights reserved


#include "Components/Combat/RobotCombatComponent.h"

#include "KlotoDebugHelper.h"
#include "Items/Weapons/KlotoRobotWeapon.h"

AKlotoRobotWeapon* URobotCombatComponent::GetRobotCarriedWeaponByTag(FGameplayTag InWeaponTag) const
{
	return Cast<AKlotoRobotWeapon>(GetCharacterCarriedWeaponByTag(InWeaponTag));
}

void URobotCombatComponent::OnHitTargetActor(AActor* HitActor)
{
	Debug::Print(GetOwningPawn()->GetActorNameOrLabel() + TEXT("Hit") + HitActor->GetActorNameOrLabel());
}

void URobotCombatComponent::OnWeaponPulledFromTargetActor(AActor* InteractedActor)
{
	Debug::Print(GetOwningPawn()->GetActorNameOrLabel() + TEXT("Pulled") + InteractedActor->GetActorNameOrLabel());
}
