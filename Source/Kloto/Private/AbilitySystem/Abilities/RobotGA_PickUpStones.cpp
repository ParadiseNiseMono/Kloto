// Paradise_NiseMono all rights reserved


#include "AbilitySystem/Abilities/RobotGA_PickUpStones.h"

#include "Characters/KlotoRobotCharacter.h"
#include "Components/UI/RobotUIComponent.h"
#include "Items/PickUps/KlotoStoneBase.h"
#include "Kismet/KismetSystemLibrary.h"

void URobotGA_PickUpStones::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                            const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                            const FGameplayEventData* TriggerEventData)
{
	GetRobotUIComponentFromActorInfo()->OnStoneInteracted.Broadcast(true);
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void URobotGA_PickUpStones::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	GetRobotUIComponentFromActorInfo()->OnStoneInteracted.Broadcast(false);
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void URobotGA_PickUpStones::CollectStones()
{
	CollectedStones.Empty();
	TArray<FHitResult> OutHits;
	
	UKismetSystemLibrary::BoxTraceMultiForObjects(
		GetRobotCharacterFromActorInfo(),
		GetRobotCharacterFromActorInfo()->GetActorLocation(),
		GetRobotCharacterFromActorInfo()->GetActorLocation() + -GetRobotCharacterFromActorInfo()->GetActorUpVector() * BoxTraceDistance,
		TraceBoxSize / 2.f,
		(-GetRobotCharacterFromActorInfo()->GetActorUpVector()).ToOrientationRotator(),
		BoxTraceTypes,
		false,
		TArray<AActor*>(),
		bDrawDebugShape ? EDrawDebugTrace::ForOneFrame : EDrawDebugTrace::None,
		OutHits,
		true
		);

	for (FHitResult HitResult : OutHits)
	{
		if (AKlotoStoneBase* FoundStone = Cast<AKlotoStoneBase>(HitResult.GetActor()))
		{
			CollectedStones.AddUnique(FoundStone);
		}
	}

	if (CollectedStones.IsEmpty())
	{
		CancelAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true);
	}
}

void URobotGA_PickUpStones::ConsumeStones()
{
	if (CollectedStones.IsEmpty())
	{
		CancelAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true);
		return;
	}

	for (AKlotoStoneBase* StoneToConsume : CollectedStones)
	{
		StoneToConsume->Consume(GetKlotoAbilitySystemComponentFromActorInfo(), GetAbilityLevel());
	}
}
