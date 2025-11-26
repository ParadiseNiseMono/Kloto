// Paradise_NiseMono all rights reserved


#include "DataAssets/StartUpData/DataAsset_StartUpDataBase.h"

#include "AbilitySystem/KlotoAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/KlotoGameplayAbility.h"

void UDataAsset_StartUpDataBase::GiveToAbilitySystemComponent(UKlotoAbilitySystemComponent* InKlotoAscToGive,
                                                            int32 ApplyLevel)
{
	check(InKlotoAscToGive);

	GrantAbilities(ActivateOnGivenAbilities, InKlotoAscToGive, ApplyLevel);
	GrantAbilities(ReactiveAbilities, InKlotoAscToGive, ApplyLevel);
}

void UDataAsset_StartUpDataBase::GrantAbilities(const TArray<TSubclassOf<UKlotoGameplayAbility>>& InAbilitiesToGive,
	UKlotoAbilitySystemComponent* InKlotoAscToGive, int32 ApplyLevel)
{
	if (InAbilitiesToGive.IsEmpty()) return;

	for (const TSubclassOf<UKlotoGameplayAbility>& Ability : InAbilitiesToGive)
	{
		if (!Ability) return;

		FGameplayAbilitySpec AbilitySpec(Ability);
		AbilitySpec.SourceObject = InKlotoAscToGive->GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
		InKlotoAscToGive->GiveAbility(AbilitySpec);
	}
}
