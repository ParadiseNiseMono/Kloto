// Paradise_NiseMono all rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "KlotoFunctionLibrary.generated.h"

UENUM()
enum class EKlotoConfirmType : uint8
{
	Yes,
	No
};

struct FGameplayTag;
class UKlotoAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class KLOTO_API UKlotoFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static UKlotoAbilitySystemComponent* NativeGetKlotoAscFromActor(AActor* InActor);

	UFUNCTION(BlueprintCallable, Category = "Kloto|FunctionLibary")
	static void AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag TagToAdd);

	UFUNCTION(BlueprintCallable, Category = "Kloto|FunctionLibary")
	static void RemoveGameplayTagFromActorIfFound(AActor* InActor, FGameplayTag TagToRemove);

	static bool NativeDoesActorHasTag(AActor* InActor, FGameplayTag TagToCheck);

	UFUNCTION(BlueprintCallable, Category = "Kloto|FunctionLibary", meta = (DisplayName = "Does Actor Has Tag", ExpandEnumAsExecs = "OutConfirmType"))
	static void BP_DoesActorHasTag(AActor* InActor, FGameplayTag TagToCheck,EKlotoConfirmType& OutConfirmType);
};
