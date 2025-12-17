// Paradise_NiseMono all rights reserved


#include "KlotoTypes/KlotoCountDownAction.h"

void FKlotoCountDownAction::CancelAction()
{
	bNeedToCancel = true;
}

void FKlotoCountDownAction::UpdateOperation(FLatentResponse& Response)
{
	if (bNeedToCancel)
	{
		CountDownActionOutput = EKlotoCountDownActionOutput::Canceled;

		Response.FinishAndTriggerIf(true, ExecutionFunction, OutputLink, CallbackTarget);

		return;
	}

	if (ElapsedTimeSinceStart >= TotalCountDownTime)
	{
		CountDownActionOutput = EKlotoCountDownActionOutput::Completed;	

		Response.FinishAndTriggerIf(true, ExecutionFunction, OutputLink, CallbackTarget);
		return;
	}
	if (ElapsedInterval < UpdateInterval)
	{
		ElapsedInterval += Response.ElapsedTime();
	}
	else
	{
		ElapsedTimeSinceStart += UpdateInterval > 0.f? UpdateInterval : Response.ElapsedTime();

		OutRemainTime = TotalCountDownTime - ElapsedTimeSinceStart;

		CountDownActionOutput = EKlotoCountDownActionOutput::Updated;

		Response.TriggerLink(ExecutionFunction, OutputLink, CallbackTarget);
		ElapsedInterval = 0.f;
	}
}
