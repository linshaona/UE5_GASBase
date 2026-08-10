// Make by linshao


#include "UI/CAttributeWidget.h"

#include "AbilitySystem/CAttributeSet.h"

void UCAttributeWidget::OnAttributeChanged(const TTuple<FGameplayAttribute, FGameplayAttribute> Pair,
                                           UCAttributeSet* AttributeSet,float OldValue)
{
	const float AttributeValue = Pair.Key.GetNumericValue(AttributeSet);
	const float MaxAttributeValue = Pair.Value.GetNumericValue(AttributeSet);
	
	BP_OnAttributeChange(AttributeValue,MaxAttributeValue,OldValue);
}

bool UCAttributeWidget::MatchesAttribute(const TTuple<FGameplayAttribute, FGameplayAttribute> Pair) const
{
	return Attribute == Pair.Key && MaxAttribute == Pair.Value;
}
