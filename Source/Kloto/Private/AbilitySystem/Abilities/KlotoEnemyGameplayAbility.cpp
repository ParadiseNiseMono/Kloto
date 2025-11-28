// Paradise_NiseMono all rights reserved


#include "AbilitySystem/Abilities/KlotoEnemyGameplayAbility.h"

#include "Characters/KlotoEnemyCharacter.h"

AKlotoEnemyCharacter* UKlotoEnemyGameplayAbility::GetKlotoEnemyCharacterFromActorInfo()
{
	if (!CachedKlotoEnemyCharacter.IsValid())
	{
		CachedKlotoEnemyCharacter = Cast<AKlotoEnemyCharacter>(CurrentActorInfo->AvatarActor);
	}
	return CachedKlotoEnemyCharacter.IsValid() ? CachedKlotoEnemyCharacter.Get() : nullptr;
}

UEnemyCombatComponent* UKlotoEnemyGameplayAbility::GetEnemyCombatComponentFormActorInfo()
{
	return GetKlotoEnemyCharacterFromActorInfo()->GetEnemyCombatComponent();
}
