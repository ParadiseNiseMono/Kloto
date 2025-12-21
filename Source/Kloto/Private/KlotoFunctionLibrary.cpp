// Paradise_NiseMono all rights reserved


#include "KlotoFunctionLibrary.h"

#include "AbilitySystem/KlotoAbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GenericTeamAgentInterface.h"
#include "KlotoDebugHelper.h"
#include "KlotoGameplayTags.h"
#include "Interfaces/PawnCombatInterface.h"
#include "Kismet/KismetMathLibrary.h"
#include "KlotoTypes/KlotoCountDownAction.h"
#include "KlotoGameInstance.h"


UKlotoAbilitySystemComponent* UKlotoFunctionLibrary::NativeGetKlotoAscFromActor(AActor* InActor)
{
	check(InActor);
	
	return CastChecked<UKlotoAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InActor));
}

void UKlotoFunctionLibrary::AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag TagToAdd)
{
	UKlotoAbilitySystemComponent* ASC = NativeGetKlotoAscFromActor(InActor);

	if (!ASC->HasMatchingGameplayTag(TagToAdd))
	{
		ASC->AddLooseGameplayTag(TagToAdd);
	}
}

void UKlotoFunctionLibrary::RemoveGameplayTagFromActorIfFound(AActor* InActor, FGameplayTag TagToRemove)
{
	UKlotoAbilitySystemComponent* ASC = NativeGetKlotoAscFromActor(InActor);

	if (ASC->HasMatchingGameplayTag(TagToRemove))
	{
		ASC->RemoveLooseGameplayTag(TagToRemove);
	}
}

bool UKlotoFunctionLibrary::NativeDoesActorHasTag(AActor* InActor, FGameplayTag TagToCheck)
{
	UKlotoAbilitySystemComponent* ASC = NativeGetKlotoAscFromActor(InActor);

	return ASC->HasMatchingGameplayTag(TagToCheck);
}

void UKlotoFunctionLibrary::BP_DoesActorHasTag(AActor* InActor, FGameplayTag TagToCheck,
	EKlotoConfirmType& OutConfirmType)
{
	OutConfirmType = NativeDoesActorHasTag(InActor, TagToCheck) ? EKlotoConfirmType::Yes : EKlotoConfirmType::No;
}

UPawnCombatComponent* UKlotoFunctionLibrary::NativeGetPawnCombatComponentFromActor(AActor* InActor)
{
	check(InActor);

	if (IPawnCombatInterface* PawnCombatInterface = Cast<IPawnCombatInterface>(InActor))
	{
		return PawnCombatInterface->GetPawnCombatComponent();
	}
	return nullptr;
}

UPawnCombatComponent* UKlotoFunctionLibrary::BP_GetPawnCombatComponentFromActor(AActor* InActor,
	EKlotoValidType& OutValidType)
{
	UPawnCombatComponent* PawnCombatComponent = NativeGetPawnCombatComponentFromActor(InActor);

	OutValidType = PawnCombatComponent ? EKlotoValidType::Valid : EKlotoValidType::Invalid;

	return PawnCombatComponent;
}

bool UKlotoFunctionLibrary::IsTargetPawnHostile(APawn* QueryPawn, APawn* TargetPawn)
{
	check(QueryPawn && TargetPawn);

	IGenericTeamAgentInterface* QueryTeamAgent = Cast<IGenericTeamAgentInterface>(QueryPawn->GetController());
	IGenericTeamAgentInterface* TargetTeamAgent = Cast<IGenericTeamAgentInterface>(TargetPawn->GetController());

	if (QueryTeamAgent && TargetTeamAgent)
	{
		return QueryTeamAgent->GetGenericTeamId() != TargetTeamAgent->GetGenericTeamId();
	}
	return false;
}

float UKlotoFunctionLibrary::GetScalableFloatValueAtLevel(const FScalableFloat& InScalableFloat, int32 InLevel)
{
	return InScalableFloat.GetValueAtLevel(InLevel);
}

FGameplayTag UKlotoFunctionLibrary::ComputeHitReactDirectionTag(AActor* InAttacker, AActor* InVictim,
	float& OutAngleDifference)
{
	check(InAttacker && InVictim);

	const FVector VictimForward = InVictim->GetActorForwardVector();
	const FVector VictimToAttackerNormalized = (InAttacker->GetActorLocation() - InVictim->GetActorLocation()).GetSafeNormal();

	const float DotResult = FVector::DotProduct(VictimForward, VictimToAttackerNormalized);
	OutAngleDifference = UKismetMathLibrary::DegAcos(DotResult);

	const FVector CrossResult = FVector::CrossProduct(VictimForward, VictimToAttackerNormalized);

	if (CrossResult.Z < 0.0f)
	{
		OutAngleDifference *= -1.0f;
	}

	if (OutAngleDifference >= -45.f && OutAngleDifference <= 45.f)
	{
		return KlotoGameplayTags::Shared_Status_HitReact_Front;
	}
	else if (OutAngleDifference > 45.f && OutAngleDifference < 135.f)
	{
		return KlotoGameplayTags::Shared_Status_HitReact_Right;
	}
	else if (OutAngleDifference >= 135.f || OutAngleDifference < -135.f)
	{
		return KlotoGameplayTags::Shared_Status_HitReact_Back;
	}
	else if (OutAngleDifference >= -135.f && OutAngleDifference < -45.f)
	{
		return KlotoGameplayTags::Shared_Status_HitReact_Left;
	}

	return KlotoGameplayTags::Shared_Status_HitReact_Front;
}

bool UKlotoFunctionLibrary::IsValidBlock(AActor* InAttacker, AActor* InDefender)
{
	check(InAttacker && InDefender);

	const float DotResult = FVector::DotProduct(InAttacker->GetActorForwardVector(), InDefender->GetActorForwardVector());

	const FString DebugString = FString::Printf(TEXT("DotResult = %f %s"), DotResult, DotResult < 0.1f ? TEXT("Valid Block") : TEXT("In Valid Block"));

	Debug::Print(DebugString);
	return DotResult < 0.1f;
}

bool UKlotoFunctionLibrary::ApplyGameplayEffectSpecHandleToTargetActor(AActor* InInstigator, AActor* InTargetActor,
	const FGameplayEffectSpecHandle& InSpecHandle)
{
	UKlotoAbilitySystemComponent* InstigatorASC = NativeGetKlotoAscFromActor(InInstigator);
	UKlotoAbilitySystemComponent* TargetASC = NativeGetKlotoAscFromActor(InTargetActor);

	FActiveGameplayEffectHandle ActiveGameplayEffectHandle = InstigatorASC->ApplyGameplayEffectSpecToTarget(*InSpecHandle.Data, TargetASC);

	return ActiveGameplayEffectHandle.WasSuccessfullyApplied();
}

void UKlotoFunctionLibrary::CountDown(const UObject* WorldContextObject, float TotalTime, float UpdateInterval,
	float& OutRemainTime, EKlotoCountDownActionInput CountDownActionInput,
	UPARAM(DisplayName = "Output") EKlotoCountDownActionOutput& CountDownActionOutput, FLatentActionInfo LatentInfo)
{
	UWorld* World = nullptr;

	if(GEngine)
	{
		World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	}
	if (!World) return;

	FLatentActionManager& LatentActionManager = World->GetLatentActionManager();
	FKlotoCountDownAction* FoundAction = LatentActionManager.FindExistingAction<FKlotoCountDownAction>(LatentInfo.CallbackTarget, LatentInfo.UUID);

	if (CountDownActionInput == EKlotoCountDownActionInput::Start)
	{
		if (!FoundAction)
		{
			LatentActionManager.AddNewAction(
			 LatentInfo.CallbackTarget,
				LatentInfo.UUID,
				new FKlotoCountDownAction(TotalTime, UpdateInterval, OutRemainTime, CountDownActionOutput, LatentInfo));
		}
	}
	if (CountDownActionInput == EKlotoCountDownActionInput::Cancel)
	{
		if (FoundAction)
		{
			FoundAction->CancelAction();
		}
	}
}

UKlotoGameInstance* UKlotoFunctionLibrary::GetKlotoGameInstance(const UObject* WorldContextObject)
{
	if (GEngine)
	{
		if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
		{
			return World->GetGameInstance<UKlotoGameInstance>();
		}
	}
	return nullptr;
}
