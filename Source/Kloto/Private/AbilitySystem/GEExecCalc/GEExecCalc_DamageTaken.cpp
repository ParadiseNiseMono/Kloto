// Paradise_NiseMono all rights reserved


#include "AbilitySystem/GEExecCalc/GEExecCalc_DamageTaken.h"

#include "KlotoDebugHelper.h"
#include "KlotoGameplayTags.h"
#include "AbilitySystem/KlotoAttributeSet.h"

// 定義一個 Struct 來集中管理屬性捕捉
struct FKlotoDamageCapture
{
	// 宣告我們要捕捉的屬性變數 (會自動生成 AttackPowerDef 等變數)
	DECLARE_ATTRIBUTE_CAPTUREDEF(AttackPower)
	DECLARE_ATTRIBUTE_CAPTUREDEF(DefensePower)
	DECLARE_ATTRIBUTE_CAPTUREDEF(DamageTaken)

	FKlotoDamageCapture()
	{
		// 定義捕捉細節
		// 參數：AttributeSet類別, 屬性名稱, 來源(Source/Target), 是否快照(Snapshot)
		
		DEFINE_ATTRIBUTE_CAPTUREDEF(UKlotoAttributeSet, AttackPower, Source, false)
		DEFINE_ATTRIBUTE_CAPTUREDEF(UKlotoAttributeSet, DefensePower, Target, false)
		DEFINE_ATTRIBUTE_CAPTUREDEF(UKlotoAttributeSet, DamageTaken, Target, false)
	}
};

// Singleton Getter
static const FKlotoDamageCapture& GetKlotoDamageCapture()
{
	static FKlotoDamageCapture KlotoDamageCapture;
	return KlotoDamageCapture;
}
UGEExecCalc_DamageTaken::UGEExecCalc_DamageTaken()
{
	/*Slow way of doing capture*/
	/*FProperty* AttackPowerProperty = FindFieldChecked<FProperty>(
		UKlotoAttributeSet::StaticClass(),
		GET_MEMBER_NAME_CHECKED(UKlotoAttributeSet, AttackPower)
		);

	FGameplayEffectAttributeCaptureDefinition AttackPowerCaptureDefinition(
		AttackPowerProperty,
		EGameplayEffectAttributeCaptureSource::Source,
		false
		);

	RelevantAttributesToCapture.Add(AttackPowerCaptureDefinition);*/

	// 將定義好的屬性加入到 GAS 的捕捉清單中
	RelevantAttributesToCapture.Add(GetKlotoDamageCapture().AttackPowerDef);
	RelevantAttributesToCapture.Add(GetKlotoDamageCapture().DefensePowerDef);
	RelevantAttributesToCapture.Add(GetKlotoDamageCapture().DamageTakenDef);
}

void UGEExecCalc_DamageTaken::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const FGameplayEffectSpec& EffectSpec = ExecutionParams.GetOwningSpec();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = EffectSpec.CapturedSourceTags.GetAggregatedTags();
	EvaluationParameters.TargetTags = EffectSpec.CapturedTargetTags.GetAggregatedTags();

	float SourceAttackPower = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetKlotoDamageCapture().AttackPowerDef, EvaluationParameters, SourceAttackPower);
	/*Debug::Print(TEXT("SourceAttackPower"), SourceAttackPower);*/

	float BaseDamage = 0.f;
	int32 UsedLightAttackComboCount = 0;
	int32 UsedHeavyAttackComboCount = 0;
	for (const TPair<FGameplayTag, float> TagMagnitude : EffectSpec.SetByCallerTagMagnitudes)
	{
		if (TagMagnitude.Key.MatchesTagExact(KlotoGameplayTags::Shared_SetByCaller_BaseDamage))
		{
			BaseDamage = TagMagnitude.Value;
			/*Debug::Print(TEXT("BaseDamage"), BaseDamage);*/
		}

		if (TagMagnitude.Key.MatchesTagExact(KlotoGameplayTags::Player_SetByCaller_AttackType_Light))
		{
			UsedLightAttackComboCount = TagMagnitude.Value;
			/*Debug::Print(TEXT("UsedLightAttackComboCount"), UsedLightAttackComboCount);*/
		}
		if (TagMagnitude.Key.MatchesTagExact(KlotoGameplayTags::Player_SetByCaller_AttackType_Heavy))
		{
			UsedHeavyAttackComboCount = TagMagnitude.Value;
			/*Debug::Print(TEXT("UsedHeavyAttackComboCount"), UsedHeavyAttackComboCount);*/
		}
	}
	
	float TargetDefensePower = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetKlotoDamageCapture().DefensePowerDef, EvaluationParameters, TargetDefensePower);
	/*Debug::Print(TEXT("TargetDefensePower"), TargetDefensePower);*/

	if (UsedLightAttackComboCount != 0)
	{
		const float DamageIncreasePercentLight = (UsedLightAttackComboCount - 1) * 0.1f + 1.f;

		BaseDamage *= DamageIncreasePercentLight;
	}
	if (UsedHeavyAttackComboCount != 0)
	{
		const float DamageIncreasePercentHeavy = (UsedHeavyAttackComboCount - 1) * 0.15f + 1.f;

		BaseDamage *= DamageIncreasePercentHeavy;
	}

	const float FinalDamageDone = BaseDamage * SourceAttackPower / TargetDefensePower;
	Debug::Print(TEXT("FinalDamageDone"), FinalDamageDone);

	if (FinalDamageDone > 0.f)
	{
		OutExecutionOutput.AddOutputModifier(
			FGameplayModifierEvaluatedData(GetKlotoDamageCapture().DamageTakenProperty, EGameplayModOp::Override, FinalDamageDone)
			);
	}
}
