// Paradise_NiseMono all rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "KlotoTypes/KlotoEnumTypes.h"
#include "KlotoFunctionLibrary.generated.h"

class UKlotoGameInstance;
struct FGameplayEffectSpecHandle;
struct FScalableFloat;
class UPawnCombatComponent;

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

	static UPawnCombatComponent* NativeGetPawnCombatComponentFromActor(AActor* InActor);

	UFUNCTION(BlueprintCallable, Category = "Kloto|FunctionLibary", meta = (DisplayName = "Get Pawn Combat Component From Actor", ExpandEnumAsExecs = "OutValidType"))
	static UPawnCombatComponent* BP_GetPawnCombatComponentFromActor(AActor* InActor, EKlotoValidType& OutValidType);

	UFUNCTION(BlueprintPure, Category = "Kloto|FunctionLibary")
	static bool IsTargetPawnHostile(APawn* QueryPawn, APawn* TargetPawn);

	UFUNCTION(BlueprintPure, Category = "Kloto|FunctionLibary", meta = (CompactNodeTitle = "Get Value At Level"))
	static float GetScalableFloatValueAtLevel(const FScalableFloat& InScalableFloat, int32 InLevel = 1);

	UFUNCTION(BlueprintPure, Category = "Kloto|FunctionLibary")
	static FGameplayTag ComputeHitReactDirectionTag(AActor* InAttacker, AActor* InVictim, float& OutAngleDifference);

	UFUNCTION(BlueprintPure, Category = "Kloto|FunctionLibary")
	static bool IsValidBlock(AActor* InAttacker, AActor* InDefender);

	UFUNCTION(BlueprintCallable, Category = "Kloto|FunctionLibary")
	static bool ApplyGameplayEffectSpecHandleToTargetActor(AActor* InInstigator, AActor* InTargetActor, const FGameplayEffectSpecHandle& InSpecHandle);

	UFUNCTION(BlueprintCallable, Category = "Kloto|FunctionLibary", meta=(Latent, WorldContext = "WorldContextObject", LatentInfo = "LatentInfo", ExpandEnumAsExecs = "CountDownActionInput|CountDownActionOutput", TotalTime = "1", UpdateInterval = "0.1"))
	static void CountDown(const UObject* WorldContextObject, float TotalTime, float UpdateInterval, float& OutRemainTime,
		EKlotoCountDownActionInput CountDownActionInput,
		UPARAM(DisplayName = "Output") EKlotoCountDownActionOutput& CountDownActionOutput,
		FLatentActionInfo LatentInfo);

	UFUNCTION(BlueprintPure, Category = "Kloto|FunctionLibary", meta=(WorldContext = "WorldContextObject"))
	static UKlotoGameInstance* GetKlotoGameInstance(const UObject* WorldContextObject);
};
