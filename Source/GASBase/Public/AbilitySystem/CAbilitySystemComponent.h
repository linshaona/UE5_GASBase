// Make by linshao

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "CAbilitySystemComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GASBASE_API UCAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	
	UCAbilitySystemComponent();

	virtual void OnGiveAbility(FGameplayAbilitySpec& AbilitySpec) override;
	virtual void OnRep_ActivateAbilities() override;
	
	UFUNCTION(BlueprintCallable,Category="GASBase|Abilities")
	void SetAbilityLevel(TSubclassOf<UGameplayAbility> AbilityClass,int32 Level);
	
	UFUNCTION(BlueprintCallable,Category="GASBase|Abilities")
	void AddToAbilityLevel(TSubclassOf<UGameplayAbility> AbilityClass,int32 Level = 1);
	
private:
	
	void HandleAutoActivatedAbility(const FGameplayAbilitySpec& AbilitySpec);
};
