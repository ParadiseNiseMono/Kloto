// Paradise_NiseMono all rights reserved


#include "Components/UI/EnemyUIComponent.h"

#include "Widgets/KlotoWidgetBase.h"

void UEnemyUIComponent::RegisterEnemyDrawnWidget(UKlotoWidgetBase* InWidgetToRegister)
{
	EnemyDrawnWidgets.Add(InWidgetToRegister);
}

void UEnemyUIComponent::RemoveEnemyDrawnWidgetsIfAny()
{
	if (EnemyDrawnWidgets.IsEmpty()) return;

	for (UKlotoWidgetBase* Widget : EnemyDrawnWidgets)
	{
		if (Widget)
		{
			Widget->RemoveFromParent();
		}
	}
}
