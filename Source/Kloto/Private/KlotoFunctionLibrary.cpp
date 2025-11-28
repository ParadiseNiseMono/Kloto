// Paradise_NiseMono all rights reserved


#include "KlotoFunctionLibrary.h"

#include "AbilitySystem/KlotoAbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"

UKlotoAbilitySystemComponent* UKlotoFunctionLibrary::NativeGetKlotoAscFromActor(AActor* InActor)
{
	check(InActor);
	
	return CastChecked<UKlotoAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InActor));
}

void UKlotoFunctionLibrary::AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag TagToAdd)
{
	UKlotoAbilitySystemComponent* ASC = NativeGetKlotoAscFromActor(InActor);

	if (ASC->HasMatchingGameplayTag(TagToAdd))
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
