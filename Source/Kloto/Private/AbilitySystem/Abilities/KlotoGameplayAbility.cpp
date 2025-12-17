// Paradise_NiseMono all rights reserved


#include "AbilitySystem/Abilities/KlotoGameplayAbility.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "KlotoFunctionLibrary.h"
#include "KlotoGameplayTags.h"
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

FActiveGameplayEffectHandle UKlotoGameplayAbility::NativeApplyGameplayEffectSpecHandleToTarget(AActor* TargetActor,
	const FGameplayEffectSpecHandle& InSpecHandle)
{
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);

	check(TargetASC && InSpecHandle.IsValid());

	return GetKlotoAbilitySystemComponentFromActorInfo()->ApplyGameplayEffectSpecToTarget(*InSpecHandle.Data, TargetASC);
}

FActiveGameplayEffectHandle UKlotoGameplayAbility::BP_ApplyGameplayEffectSpecHandleToTarget(AActor* TargetActor,
	const FGameplayEffectSpecHandle& InSpecHandle, EKlotoSuccessType& OutSuccessType)
{
	FActiveGameplayEffectHandle ActiveGameplayEffectHandle = NativeApplyGameplayEffectSpecHandleToTarget(TargetActor, InSpecHandle);

	OutSuccessType = ActiveGameplayEffectHandle.WasSuccessfullyApplied() ? EKlotoSuccessType::Successful : EKlotoSuccessType::Failed;

	return ActiveGameplayEffectHandle;
}

void UKlotoGameplayAbility::ApplyEffectSpecHandleToHitResults(const FGameplayEffectSpecHandle& InSpecHandle,
	const TArray<FHitResult>& InHitResults)
{
	if (InHitResults.IsEmpty()) return;

	APawn* OwingPawn = CastChecked<APawn>(GetAvatarActorFromActorInfo());
	for (const FHitResult& HitResult : InHitResults)
	{
		if (APawn* HitPawn = Cast<APawn>(HitResult.GetActor()))
		{
			if (UKlotoFunctionLibrary::IsTargetPawnHostile(OwingPawn, HitPawn))
			{
				FActiveGameplayEffectHandle EffectHandle = NativeApplyGameplayEffectSpecHandleToTarget(HitPawn, InSpecHandle);
				if (EffectHandle.WasSuccessfullyApplied())
				{
					FGameplayEventData Data;
					Data.Instigator = OwingPawn;
					Data.Target = HitPawn;
					UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
						HitPawn,
						KlotoGameplayTags::Shared_Event_HitReact,
						Data
						);
				}
			}
		}
	}
}
