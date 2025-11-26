// Paradise_NiseMono all rights reserved

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "DataAssets/StartUpData/DataAsset_StartUpDataBase.h"
#include "DataAsset_RobotStartUpData.generated.h"

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

/**
 * 
 */
UCLASS()
class KLOTO_API UDataAsset_RobotStartUpData : public UDataAsset_StartUpDataBase
{
	GENERATED_BODY()
public:
	virtual void GiveToAbilitySystemComponent(UKlotoAbilitySystemComponent* InAscToGive, int32 ApplyLevel = 1) override;
private:
	UPROPERTY(EditDefaultsOnly, Category = "StartUpData", meta = (TitleProperty = "InputTag"))
	TArray<FKlotoRobotAbilitySet> RobotStartupAbilitySets;
};
