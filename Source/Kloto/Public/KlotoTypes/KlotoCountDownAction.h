// Paradise_NiseMono all rights reserved

#pragma once

#include "CoreMinimal.h"
#include "KlotoEnumTypes.h"

/**
 * 
 */
class FKlotoCountDownAction : public FPendingLatentAction
{
public:
	FKlotoCountDownAction(float InTotalCountTime,
		float InUpdateInterval,
		float& InOutRemainingTime,
		EKlotoCountDownActionOutput& InCountDownActionOutput,
		const FLatentActionInfo& InLatentInfo)
	: bNeedToCancel(false),
	TotalCountDownTime(InTotalCountTime),
	UpdateInterval(InUpdateInterval),
	OutRemainTime(InOutRemainingTime),
	CountDownActionOutput(InCountDownActionOutput),
	ExecutionFunction(InLatentInfo.ExecutionFunction),
	OutputLink(InLatentInfo.Linkage),
	CallbackTarget(InLatentInfo.CallbackTarget),
	ElapsedInterval(0.f),
	ElapsedTimeSinceStart(0.f)
	{
		
	}

private:
	bool bNeedToCancel;
	float TotalCountDownTime;
	float UpdateInterval;
	float& OutRemainTime;
	EKlotoCountDownActionOutput& CountDownActionOutput;
	FName ExecutionFunction;
	int32 OutputLink;
	FWeakObjectPtr CallbackTarget;
	float ElapsedInterval;
	float ElapsedTimeSinceStart;
};