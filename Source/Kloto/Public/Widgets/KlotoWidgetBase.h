// Paradise_NiseMono all rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "KlotoWidgetBase.generated.h"

class UEnemyUIComponent;
class URobotUIComponent;
/**
 * 
 */
UCLASS()
class KLOTO_API UKlotoWidgetBase : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;

	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName = "On Owning Robot UI Component Initialized"))
	void BP_OnOwningRobotUIComponentInitialized(URobotUIComponent* OwningRobotUIComponent);

	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName = "On Owning Enemy UI Component Initialized"))
	void BP_OnOwningEnemyUIComponentInitialized(UEnemyUIComponent* OwningEnemyUIComponent);
public:
	UFUNCTION(BlueprintCallable)
	void InitEnemyCreatedWidget(AActor* OwningEnemyActor);
};
