// Paradise_NiseMono all rights reserved


#include "Components/Combat/EnemyCombatComponent.h"

#include "KlotoDebugHelper.h"

void UEnemyCombatComponent::OnHitTargetActor(AActor* HitActor)
{
	if (HitActor)
	{
		Debug::Print(TEXT("OnHitTargetActor " + GetOwningPawn()->GetActorNameOrLabel() + HitActor->GetActorNameOrLabel()));
	}
}
