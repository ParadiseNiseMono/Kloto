#pragma once

UENUM()
enum class EKlotoConfirmType : uint8
{
	Yes,
	No
};

UENUM()
enum class EKlotoValidType : uint8
{
	Valid,
	Invalid
};

UENUM()
enum class EKlotoSuccessType : uint8
{
	Successful,
	Failed
};

UENUM()
enum class EKlotoCountDownActionInput : uint8
{
	Start,
	Cancel
};

UENUM()
enum class EKlotoCountDownActionOutput : uint8
{
	Updated,
	Completed,
	Canceled
};

UENUM(BlueprintType)
enum class EKlotoGameDifficulty : uint8
{
	Easy,
	Normal,
	Hard,
	VeryHard
};

UENUM(BlueprintType)
enum class EKlotoInputMode : uint8
{
	GameOnly,
	UIOnly
};