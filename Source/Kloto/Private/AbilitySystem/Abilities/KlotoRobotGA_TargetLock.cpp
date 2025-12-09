// Paradise_NiseMono all rights reserved


#include "AbilitySystem/Abilities/KlotoRobotGA_TargetLock.h"

#include "KlotoDebugHelper.h"
#include "KlotoFunctionLibrary.h"
#include "KlotoGameplayTags.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Blueprint/WidgetTree.h"
#include "Characters/KlotoRobotCharacter.h"
#include "Components/SizeBox.h"
#include "Controllers/KlotoRobotController.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
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

void UKlotoRobotGA_TargetLock::OnTargetLockTick(float DeltaTime)
{
	if (!CurrentLockedActor ||
		UKlotoFunctionLibrary::NativeDoesActorHasTag(CurrentLockedActor, KlotoGameplayTags::Shared_Ability_Death) ||
		UKlotoFunctionLibrary::NativeDoesActorHasTag(GetRobotCharacterFromActorInfo(), KlotoGameplayTags::Shared_Ability_Death))
	{
		CancelTargetLockAbility();
		return;
	}

	SetTargetLockWidgetPosition();

	const bool bShouldOverrideRotation =
		!UKlotoFunctionLibrary::NativeDoesActorHasTag(GetRobotCharacterFromActorInfo(), KlotoGameplayTags::Player_Status_Rolling) &&
			!UKlotoFunctionLibrary::NativeDoesActorHasTag(GetRobotCharacterFromActorInfo(), KlotoGameplayTags::Player_Status_Blocking);

	if (bShouldOverrideRotation)
	{
		const FRotator LookAtRot = UKismetMathLibrary::FindLookAtRotation(
			GetRobotCharacterFromActorInfo()->GetActorLocation(), CurrentLockedActor->GetActorLocation());

		const FRotator CurrentRot = GetRobotControllerFromActorInfo()->GetControlRotation();
		const FRotator TargetRot = FMath::RInterpTo(CurrentRot, LookAtRot, DeltaTime, TargetLockRotationInterpSpeed);

		GetRobotControllerFromActorInfo()->SetControlRotation(FRotator(TargetRot.Pitch, TargetRot.Yaw, 0.f));
		GetRobotCharacterFromActorInfo()->SetActorRotation(FRotator(0.f, TargetRot.Yaw, 0.f));
	}
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

		SetTargetLockWidgetPosition();
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
	DrawnTargetLockWidget = nullptr;
	DrawnTargetLockWidgetSize = FVector2D::ZeroVector;
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

void UKlotoRobotGA_TargetLock::SetTargetLockWidgetPosition()
{
	if (!DrawnTargetLockWidget || !CurrentLockedActor)
	{
		CancelTargetLockAbility();
		return;
	}

	FVector2D ScreenPosition;
	UWidgetLayoutLibrary::ProjectWorldLocationToWidgetPosition(
		GetRobotControllerFromActorInfo(),
		CurrentLockedActor->GetActorLocation(),
		ScreenPosition,
		true
		);
	if (DrawnTargetLockWidgetSize == FVector2D::ZeroVector)
	{
		DrawnTargetLockWidget->WidgetTree->ForEachWidget(
		[this](UWidget* Widget)
			{
				if (USizeBox* FoundSizeBox = Cast<USizeBox>(Widget))
				{
					DrawnTargetLockWidgetSize.X = FoundSizeBox->GetWidthOverride();
					DrawnTargetLockWidgetSize.Y = FoundSizeBox->GetHeightOverride();
				}
			});
	}

	ScreenPosition -= DrawnTargetLockWidgetSize / 2.f;

	DrawnTargetLockWidget->SetPositionInViewport(ScreenPosition, false);
}

AActor* UKlotoRobotGA_TargetLock::GetNearestTargetFromAvailableActors(const TArray<AActor*>& InAvailableActors)
{
	float ClosestDistance = BIG_NUMBER;
	return UGameplayStatics::FindNearestActor(GetAvatarActorFromActorInfo()->GetActorLocation(), InAvailableActors, ClosestDistance);
}
