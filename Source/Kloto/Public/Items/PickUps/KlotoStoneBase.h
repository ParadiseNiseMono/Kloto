// Paradise_NiseMono all rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Items/PickUps/KlotoPickUpBase.h"
#include "KlotoStoneBase.generated.h"

/**
 * 
 */
UCLASS()
class KLOTO_API AKlotoStoneBase : public AKlotoPickUpBase
{
	GENERATED_BODY()

protected:
	virtual void OnPickUpCollisionSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
};
