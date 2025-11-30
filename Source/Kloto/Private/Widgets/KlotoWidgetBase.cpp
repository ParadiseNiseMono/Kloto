// Paradise_NiseMono all rights reserved


#include "Widgets/KlotoWidgetBase.h"

#include "Components/UI/RobotUIComponent.h"
#include "Interfaces/PawnUIInterface.h"

void UKlotoWidgetBase::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (IPawnUIInterface* PawnUIInterface = Cast<IPawnUIInterface>(GetOwningPlayerPawn()))
	{
		if (URobotUIComponent* RobotUIComponent = PawnUIInterface->GetRobotUIComponent())
		{
			BP_OnOwningRobotUIComponentInitialized(RobotUIComponent);
		}
	}
}

void UKlotoWidgetBase::InitEnemyCreatedWidget(AActor* OwningEnemyActor)
{
	if (IPawnUIInterface* PawnUIInterface = Cast<IPawnUIInterface>(OwningEnemyActor))
	{
		UEnemyUIComponent* EnemyUIComponent = PawnUIInterface->GetEnemyUIComponent();

		checkf(EnemyUIComponent, TEXT("Failed to get an EnemyUIComponent form %s"), *OwningEnemyActor->GetActorNameOrLabel());

		BP_OnOwningEnemyUIComponentInitialized(EnemyUIComponent);
	}
}
