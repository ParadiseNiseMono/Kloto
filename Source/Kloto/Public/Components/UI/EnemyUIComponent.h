// Paradise_NiseMono all rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/UI/PawnUIComponent.h"
#include "EnemyUIComponent.generated.h"

class UKlotoWidgetBase;
/**
 * 
 */
UCLASS()
class KLOTO_API UEnemyUIComponent : public UPawnUIComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void RegisterEnemyDrawnWidget(UKlotoWidgetBase* InWidgetToRegister);

	UFUNCTION(BlueprintCallable)
	void RemoveEnemyDrawnWidgetsIfAny();
private:
	TArray<UKlotoWidgetBase*> EnemyDrawnWidgets;
};
