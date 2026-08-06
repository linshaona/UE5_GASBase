// Make by linshao

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/CAbilitySystemComponent.h"
#include "AbilitySystem/CAttributeSet.h"
#include "Characters/CBaseCharacter.h"
#include "Components/WidgetComponent.h"
#include "AttributeSet.h"

#include "CWidgetComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GASBASE_API UCWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()

public:
	

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TMap<FGameplayAttribute,FGameplayAttribute> AttributeMap;
	
private:
	TWeakObjectPtr<ACBaseCharacter> GASBaseCharacter;
	TWeakObjectPtr<UCAbilitySystemComponent> AbilitySystemComponent;
	TWeakObjectPtr<UCAttributeSet> AttributeSet;
	
	void InitAbilitySystemData();
	bool IsASCInitialized();
	void InitializeAttributeDelegate();
	void BindWidgetToAttributeChanges(UWidget* WidgetObject,const TTuple<FGameplayAttribute,FGameplayAttribute>& Pair) const;
	
	UFUNCTION()
	void OnASCInitialized(UAbilitySystemComponent*  ASC,UAttributeSet* AS);
	
	UFUNCTION()
	void BindToAttributeChanges();
};
