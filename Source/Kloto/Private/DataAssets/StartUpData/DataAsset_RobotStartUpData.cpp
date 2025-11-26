// Paradise_NiseMono all rights reserved


#include "DataAssets/StartUpData/DataAsset_RobotStartUpData.h"
#include "AbilitySystem/KlotoAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/KlotoGameplayAbility.h"

bool FKlotoRobotAbilitySet::IsValid() const
{
	return InputTag.IsValid() && AbilityToGrant;
}

void UDataAsset_RobotStartUpData::GiveToAbilitySystemComponent(UKlotoAbilitySystemComponent* InAscToGive,
	int32 ApplyLevel)
{
	Super::GiveToAbilitySystemComponent(InAscToGive, ApplyLevel);

	for (const FKlotoRobotAbilitySet& AbilitySet : RobotStartupAbilitySets)
	{
		if (!AbilitySet.IsValid()) continue;

		FGameplayAbilitySpec AbilitySpec(AbilitySet.AbilityToGrant);
		AbilitySpec.SourceObject = InAscToGive->GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
		AbilitySpec.GetDynamicSpecSourceTags().AddTag(AbilitySet.InputTag);
		InAscToGive->GiveAbility(AbilitySpec);
	}
}
