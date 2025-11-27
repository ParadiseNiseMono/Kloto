// Paradise_NiseMono all rights reserved

#pragma once

#include "CoreMinimal.h"
#include "GameplayAbilitySpecHandle.h"
#include "Items/Weapons/KlotoWeaponBase.h"
#include "KlotoTypes/KlotoStructTypes.h"
#include "KlotoRobotWeapon.generated.h"

/**
 * 
 */
UCLASS()
class KLOTO_API AKlotoRobotWeapon : public AKlotoWeaponBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WeaponData")
	FKlotoRobotWeaponData RobotWeaponData;

	UFUNCTION(BlueprintCallable)
	void AssignGrantedAbilitySpecHandles(const TArray<FGameplayAbilitySpecHandle>& InSpecHandles);

	UFUNCTION(BlueprintPure)
	TArray<FGameplayAbilitySpecHandle> GetGrantedAbilitySpecHandles() const;
private:
	TArray<FGameplayAbilitySpecHandle> GrantedAbilitySpecHandles;
};
