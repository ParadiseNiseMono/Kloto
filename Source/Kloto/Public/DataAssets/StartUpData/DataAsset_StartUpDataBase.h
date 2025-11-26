// Paradise_NiseMono all rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DataAsset_StartUpDataBase.generated.h"

class UKlotoAbilitySystemComponent;
class UKlotoGameplayAbility;
/**
 * 
 */
UCLASS()
class KLOTO_API UDataAsset_StartUpDataBase : public UDataAsset
{
	GENERATED_BODY()

public:
	virtual void GiveToAbilitySystemComponent(UKlotoAbilitySystemComponent* InAscToGive, int32 ApplyLevel = 1);
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
	TArray<TSubclassOf<UKlotoGameplayAbility>> ActivateOnGivenAbilities;
	
	UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
	TArray<TSubclassOf<UKlotoGameplayAbility>> ReactiveAbilities;

	void GrantAbilities(const TArray<TSubclassOf<UKlotoGameplayAbility>>& InAbilitiesToGive, UKlotoAbilitySystemComponent* InAscToGive, int32 ApplyLevel = 1);
};
