// Make by linshao

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "Blueprint/UserWidget.h"
#include "CAttributeWidget.generated.h"

class UCAttributeSet;
/**
 * 
 */
UCLASS()
class GASBASE_API UCAttributeWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="GASBase|Attributes")
	FGameplayAttribute Attribute;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="GASBase|Attributes")
	FGameplayAttribute MaxAttribute;
	
	void OnAttributeChanged(const TTuple<FGameplayAttribute, FGameplayAttribute> Pair,UCAttributeSet * AttributeSet);
	bool MatchesAttribute(const TTuple<FGameplayAttribute, FGameplayAttribute> Pair) const;
	
	UFUNCTION(BlueprintImplementableEvent,meta = (DisplayName = "On Attribute Change"))
	void BP_OnAttributeChange(float NewValue,float NewMaxValue);//可以在蓝图中实现
};
