// Make by linshao

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "C_AttributeSet.generated.h"


//属性初始化的宏
#define ATTRIBUTE_ACCESSORS(ClassName,PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName) 


UCLASS()
class GASBASE_API UC_AttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
	
	//在GAS中创建一个属性的模板
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_Health/*网络同步的回调函数*/)
	FGameplayAttributeData Health;
	
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldValue);
	
	ATTRIBUTE_ACCESSORS(ThisClass, Health);
	
	//-----
	
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_MaxMano)
	FGameplayAttributeData MaxMano;
	
	
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;
	
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_Mano)
	FGameplayAttributeData Mano;
	
	
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldValue);
	
	UFUNCTION()
	void OnRep_Mano(const FGameplayAttributeData& OldValue);
	
	UFUNCTION()
	void OnRep_MaxMano(const FGameplayAttributeData& OldValue);
	
	
	ATTRIBUTE_ACCESSORS(ThisClass, MaxHealth);
	ATTRIBUTE_ACCESSORS(ThisClass, MaxMano);
	ATTRIBUTE_ACCESSORS(ThisClass, Mano);

};



