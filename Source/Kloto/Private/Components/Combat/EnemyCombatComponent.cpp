	// Paradise_NiseMono all rights reserved


#include "Components/Combat/EnemyCombatComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "KlotoDebugHelper.h"
#include "KlotoFunctionLibrary.h"
#include "KlotoGameplayTags.h"
#include "Characters/KlotoEnemyCharacter.h"
#include "Components/BoxComponent.h"

	void UEnemyCombatComponent::OnHitTargetActor(AActor* HitActor)
{
	if (OverlappedActors.Contains(HitActor)) return;

	OverlappedActors.AddUnique(HitActor);

	//TODO: Implement block check
	bool bIsValidBlock = false;

	const bool bIsPlayerBlocking = UKlotoFunctionLibrary::NativeDoesActorHasTag(HitActor, KlotoGameplayTags::Player_Status_Blocking);
	const bool bIsMyAttackUnBlockable = UKlotoFunctionLibrary::NativeDoesActorHasTag(GetOwningPawn(), KlotoGameplayTags::Enemy_Status_Unblockable);

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

void UEnemyCombatComponent::ToggleBodyCollisionBoxCollision(bool bShouldEnable, EToggleDamageType ToggleDamageType)
{
	AKlotoEnemyCharacter* KlotoEnemyCharacter = Cast<AKlotoEnemyCharacter>(GetOwningPawn());

	check(KlotoEnemyCharacter);
	UBoxComponent* LeftHandCollisionBox = KlotoEnemyCharacter->GetLeftHandCollisionBox();
	UBoxComponent* RightHandCollisionBox = KlotoEnemyCharacter->GetRightHandCollisionBox();

	switch (ToggleDamageType)
	{
	case EToggleDamageType::LeftHand:
			LeftHandCollisionBox->SetCollisionEnabled(bShouldEnable? ECollisionEnabled::QueryOnly : ECollisionEnabled::NoCollision);
			break;
		case EToggleDamageType::RightHand:
			RightHandCollisionBox->SetCollisionEnabled(bShouldEnable? ECollisionEnabled::QueryOnly : ECollisionEnabled::NoCollision);
			break;
		default:
			break;
	}

	if (!bShouldEnable)
	{
		OverlappedActors.Empty();
	}

		
}
