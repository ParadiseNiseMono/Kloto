// Paradise_NiseMono all rights reserved


#include "AbilitySystem/Abilities/KlotoRobotGA_TargetLock.h"

#include "KlotoDebugHelper.h"
#include "Characters/KlotoRobotCharacter.h"
#include "Kismet/KismetSystemLibrary.h"

void UKlotoRobotGA_TargetLock::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                               const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                               const FGameplayEventData* TriggerEventData)
{
	TryLockOnTarget();
	
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UKlotoRobotGA_TargetLock::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UKlotoRobotGA_TargetLock::TryLockOnTarget()
{
	GetAvailableActorsToLock();
}

void UKlotoRobotGA_TargetLock::GetAvailableActorsToLock()
{
	TArray<FHitResult> OutHits;

	UKismetSystemLibrary::BoxTraceMultiForObjects(
		GetRobotCharacterFromActorInfo(),
		GetRobotCharacterFromActorInfo()->GetActorLocation(),
		GetRobotCharacterFromActorInfo()->GetActorLocation() + GetRobotCharacterFromActorInfo()->GetActorForwardVector() * BoxTraceDistance,
		BoxTraceSize / 2,
		GetRobotCharacterFromActorInfo()->GetActorLocation().ToOrientationRotator(),
		BoxTraceChannel,
		false,
		TArray<AActor*>(),
		bShowPersistentDebugShape ? EDrawDebugTrace::Persistent : EDrawDebugTrace::None,
		OutHits,
		true
	);

	for (const FHitResult& HitResult : OutHits)
	{
		if (AActor* HitActor = HitResult.GetActor())
		{
			if (HitActor != GetRobotCharacterFromActorInfo())
			{
				AvailableActorsToLock.AddUnique(HitActor);

				Debug::Print(HitActor->GetActorNameOrLabel());
			}
		}
	}
}
