// Paradise_NiseMono all rights reserved


#include "DataAssets/StartUpData/DataAsset_EnemyStartUpData.h"

#include "AbilitySystem/KlotoAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/KlotoEnemyGameplayAbility.h"

void UDataAsset_EnemyStartUpData::GiveToAbilitySystemComponent(UKlotoAbilitySystemComponent* InAscToGive,
                                                               int32 ApplyLevel)
{
	Super::GiveToAbilitySystemComponent(InAscToGive, ApplyLevel);

	if (!EnemyStartUpAbilitySets.IsEmpty())
	{
		for (const TSubclassOf<UKlotoEnemyGameplayAbility>& AbilityClass : EnemyStartUpAbilitySets)
		{
			if (!AbilityClass) continue;

			FGameplayAbilitySpec AbilitySpec(AbilityClass);
			AbilitySpec.Level = ApplyLevel;
			AbilitySpec.SourceObject = InAscToGive->GetAvatarActor();

			InAscToGive->GiveAbility(AbilitySpec);
		}
	}
}
