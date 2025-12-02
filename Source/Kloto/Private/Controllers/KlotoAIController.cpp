// Paradise_NiseMono all rights reserved


#include "Controllers/KlotoAIController.h"

#include "KlotoDebugHelper.h"
#include "Navigation/CrowdFollowingComponent.h"

AKlotoAIController::AKlotoAIController(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>("PathFollowingComponent"))
{
	if (UCrowdFollowingComponent* CrowdComp = Cast<UCrowdFollowingComponent>(GetPathFollowingComponent()))
	{
		Debug::Print(TEXT("CrowdFollowingComponent Valid!"));
	}
}
