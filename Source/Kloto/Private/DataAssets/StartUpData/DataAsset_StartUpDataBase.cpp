// Paradise_NiseMono all rights reserved


#include "DataAssets/StartUpData/DataAsset_StartUpDataBase.h"

#include "AbilitySystem/KlotoAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/KlotoGameplayAbility.h"

void UDataAsset_StartUpDataBase::GiveToAbilitySystemComponent(UKlotoAbilitySystemComponent* InAscToGive,
                                                            int32 ApplyLevel)
{
	check(InAscToGive);

	GrantAbilities(ActivateOnGivenAbilities, InAscToGive, ApplyLevel);
	GrantAbilities(ReactiveAbilities, InAscToGive, ApplyLevel);
}

void UDataAsset_StartUpDataBase::GrantAbilities(const TArray<TSubclassOf<UKlotoGameplayAbility>>& InAbilitiesToGive,
	UKlotoAbilitySystemComponent* InAscToGive, int32 ApplyLevel)
{
	if (InAbilitiesToGive.IsEmpty()) return;

	for (const TSubclassOf<UKlotoGameplayAbility>& Ability : InAbilitiesToGive)
	{
		if (!Ability) return;

		FGameplayAbilitySpec AbilitySpec(Ability);
		AbilitySpec.SourceObject = InAscToGive->GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
		InAscToGive->GiveAbility(AbilitySpec);
	}
}
