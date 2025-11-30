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
