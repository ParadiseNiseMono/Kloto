// Paradise_NiseMono all rights reserved


#include "AbilitySystem/KlotoAbilitySystemComponent.h"

void UKlotoAbilitySystemComponent::OnAbilityInputPressed(const FGameplayTag& InInputTag)
{
	if (!InInputTag.IsValid()) return;

	for (const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (!AbilitySpec.GetDynamicSpecSourceTags().HasTagExact(InInputTag)) continue;
		
		TryActivateAbility(AbilitySpec.Handle);
	}
}

void UKlotoAbilitySystemComponent::OnAbilityInputReleased(const FGameplayTag& InInputTag)
{
	
}
