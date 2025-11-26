// Paradise_NiseMono all rights reserved


#include "AbilitySystem/Abilities/KlotoRobotGameplayAbility.h"

#include "Characters/KlotoRobotCharacter.h"
#include "Controllers/KlotoRobotController.h"

AKlotoRobotCharacter* UKlotoRobotGameplayAbility::GetRobotCharacterFromActorInfo()
{
	if (!CachedKlotoRobotCharacter.IsValid())
	{
		CachedKlotoRobotCharacter = Cast<AKlotoRobotCharacter>(CurrentActorInfo->AvatarActor);
	}

	return CachedKlotoRobotCharacter.IsValid() ? CachedKlotoRobotCharacter.Get() : nullptr;
}

AKlotoRobotController* UKlotoRobotGameplayAbility::GetRobotControllerFromActorInfo()
{
	if (!CachedKlotoRobotController.IsValid())
	{
		CachedKlotoRobotController = Cast<AKlotoRobotController>(CurrentActorInfo->PlayerController);
	}

	return CachedKlotoRobotController.IsValid() ? CachedKlotoRobotController.Get() : nullptr;
}

URobotCombatComponent* UKlotoRobotGameplayAbility::GetRobotCombatComponentFromActorInfo()
{
	return GetRobotCharacterFromActorInfo()->GetRobotCombatComponent();
}
