// Paradise_NiseMono all rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Items/PickUps/KlotoPickUpBase.h"
#include "KlotoStoneBase.generated.h"

class UGameplayEffect;
class UKlotoAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class KLOTO_API AKlotoStoneBase : public AKlotoPickUpBase
{
	GENERATED_BODY()

public:
	void Consume(UKlotoAbilitySystemComponent* AbilitySystemComponent, int32 ApplyLevel);

protected:
	virtual void OnPickUpCollisionSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName = "On Stone Consumed"))
	void BP_OnStoneConsumed();
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> StoneGameplayEffectClass;
};
