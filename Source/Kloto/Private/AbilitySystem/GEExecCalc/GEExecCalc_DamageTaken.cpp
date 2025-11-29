// Paradise_NiseMono all rights reserved


#include "AbilitySystem/GEExecCalc/GEExecCalc_DamageTaken.h"

#include "AbilitySystem/KlotoAttributeSet.h"

// 定義一個 Struct 來集中管理屬性捕捉
struct FKlotoDamageCapture
{
	// 宣告我們要捕捉的屬性變數 (會自動生成 AttackPowerDef 等變數)
	DECLARE_ATTRIBUTE_CAPTUREDEF(AttackPower)
	DECLARE_ATTRIBUTE_CAPTUREDEF(DefensePower)

	FKlotoDamageCapture()
	{
		// 定義捕捉細節
		// 參數：AttributeSet類別, 屬性名稱, 來源(Source/Target), 是否快照(Snapshot)
		
		DEFINE_ATTRIBUTE_CAPTUREDEF(UKlotoAttributeSet, AttackPower, Source, false)
		DEFINE_ATTRIBUTE_CAPTUREDEF(UKlotoAttributeSet, DefensePower, Target, false)
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
}
