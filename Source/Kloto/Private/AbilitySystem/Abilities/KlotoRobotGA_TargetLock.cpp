// Paradise_NiseMono all rights reserved


#include "AbilitySystem/Abilities/KlotoRobotGA_TargetLock.h"

#include "KlotoDebugHelper.h"
#include "Characters/KlotoRobotCharacter.h"
#include "Controllers/KlotoRobotController.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Widgets/KlotoWidgetBase.h"

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
	CleanUp();
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UKlotoRobotGA_TargetLock::TryLockOnTarget()
{
	GetAvailableActorsToLock();

	if (AvailableActorsToLock.IsEmpty())
	{
		CancelTargetLockAbility();
		return;
	}
	CurrentLockedActor = GetNearestTargetFromAvailableActors(AvailableActorsToLock);

	if (CurrentLockedActor)
	{
		DrawTargetLockWidget();
	}
	else
	{
		CancelTargetLockAbility();
	}
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
			}
		}
	}
}

void UKlotoRobotGA_TargetLock::CancelTargetLockAbility()
{
	CancelAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true);
}

void UKlotoRobotGA_TargetLock::CleanUp()
{
	AvailableActorsToLock.Empty();
	CurrentLockedActor = nullptr;
	if (DrawnTargetLockWidget)
	{
		DrawnTargetLockWidget->RemoveFromParent();
	}
}

void UKlotoRobotGA_TargetLock::DrawTargetLockWidget()
{
	if (!DrawnTargetLockWidget)
	{
		checkf(TargetLockWidgetClass, TEXT("Forgot to assign a valid widget class in blueprint"));

		DrawnTargetLockWidget = CreateWidget<UKlotoWidgetBase>(GetRobotControllerFromActorInfo(), TargetLockWidgetClass);

		check(DrawnTargetLockWidget);
	
		DrawnTargetLockWidget->AddToViewport();
	}
}

AActor* UKlotoRobotGA_TargetLock::GetNearestTargetFromAvailableActors(const TArray<AActor*>& InAvailableActors)
{
	float ClosestDistance = BIG_NUMBER;
	return UGameplayStatics::FindNearestActor(GetAvatarActorFromActorInfo()->GetActorLocation(), InAvailableActors, ClosestDistance);
}
