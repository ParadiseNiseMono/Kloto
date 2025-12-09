// Paradise_NiseMono all rights reserved


#include "AbilitySystem/AbilityTasks/AbilityTask_ExecuteOnTick.h"

UAbilityTask_ExecuteOnTick::UAbilityTask_ExecuteOnTick()
{
	bTickingTask = true;
}

UAbilityTask_ExecuteOnTick* UAbilityTask_ExecuteOnTick::ExecuteOnTick(UGameplayAbility* OwningAbility)
{
	UAbilityTask_ExecuteOnTick* Node = NewAbilityTask<UAbilityTask_ExecuteOnTick>(OwningAbility);

	return Node;
}

void UAbilityTask_ExecuteOnTick::TickTask(float DeltaTime)
{
	Super::TickTask(DeltaTime);

	if (ShouldBroadcastAbilityTaskDelegates())
	{
		OnAbilityTaskTick.Broadcast(DeltaTime);
	}
	else
	{
		EndTask();
	}
}
