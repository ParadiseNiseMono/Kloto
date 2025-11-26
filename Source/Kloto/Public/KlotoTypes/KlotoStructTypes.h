// Paradise_NiseMono all rights reserved

#pragma once
#include "GameplayTagContainer.h"

#include "KlotoStructTypes.generated.h"

class UInputMappingContext;
class UKlotoGameplayAbility;
class UKlotoRobotLinkedAnimLayer;

USTRUCT(BlueprintType)
struct FKlotoRobotAbilitySet
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "InputTag"))
	FGameplayTag InputTag;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UKlotoGameplayAbility> AbilityToGrant;

	bool IsValid() const;
};

USTRUCT(BlueprintType)
struct FKlotoRobotWeaponData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UKlotoRobotLinkedAnimLayer> WeaponAnimLayerToLink;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputMappingContext* WeaponInputMappingContext;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "InputTag"))
	TArray<FKlotoRobotAbilitySet> DefaultWeaponAbilities;
};
