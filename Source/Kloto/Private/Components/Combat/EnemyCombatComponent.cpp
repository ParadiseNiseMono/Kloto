// Paradise_NiseMono all rights reserved


#include "Components/Combat/EnemyCombatComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "KlotoDebugHelper.h"
#include "KlotoFunctionLibrary.h"
#include "KlotoGameplayTags.h"

void UEnemyCombatComponent::OnHitTargetActor(AActor* HitActor)
{
	if (OverlappedActors.Contains(HitActor)) return;

	OverlappedActors.AddUnique(HitActor);

	//TODO: Implement block check
	bool bIsValidBlock = false;

	const bool bIsPlayerBlocking = UKlotoFunctionLibrary::NativeDoesActorHasTag(HitActor, KlotoGameplayTags::Player_Status_Blocking);
	const bool bIsMyAttackUnBlockable = false;

	if (bIsPlayerBlocking && !bIsMyAttackUnBlockable)
	{
		bIsValidBlock = UKlotoFunctionLibrary::IsValidBlock(GetOwningPawn(), HitActor);
	}
	FGameplayEventData EventData;
	EventData.Instigator = GetOwningPawn();
	EventData.Target = HitActor;
	if (bIsValidBlock)
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
			HitActor,
			KlotoGameplayTags::Player_Event_SuccessfulBlock,
			EventData
			);
	}
	else
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
			GetOwningPawn(),
			KlotoGameplayTags::Shared_Event_MeleeHit,
			EventData);
	}
}
