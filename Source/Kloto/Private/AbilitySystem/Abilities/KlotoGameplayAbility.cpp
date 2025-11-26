// Paradise_NiseMono all rights reserved


#include "AbilitySystem/Abilities/KlotoGameplayAbility.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/KlotoAbilitySystemComponent.h"
#include "Components/Combat/PawnCombatComponent.h"

void UKlotoGameplayAbility::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);

	if (ActivationPolicy == EKlotoAbilityActivationPolicy::OnGiven)
	{
		if (ActorInfo && !Spec.IsActive())
		{
			ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle);
		}
	}
}

void UKlotoGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	if (ActivationPolicy == EKlotoAbilityActivationPolicy::OnGiven)
	{
		if (ActorInfo)
		{
			ActorInfo->AbilitySystemComponent->ClearAbility(Handle);
		}
	}
}

UPawnCombatComponent* UKlotoGameplayAbility::GetPawnCombatComponentFromActorInfo() const
{
	return GetAvatarActorFromActorInfo()->FindComponentByClass<UPawnCombatComponent>();
}

UKlotoAbilitySystemComponent* UKlotoGameplayAbility::GetKlotoAbilitySystemComponentFromActorInfo() const
{
	return Cast<UKlotoAbilitySystemComponent>(CurrentActorInfo->AbilitySystemComponent);
}
