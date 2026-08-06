// Make by linshao

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameplayEffect.h"
#include "GameFramework/Character.h"
#include "CBaseCharacter.generated.h"

class UGameplayAbility;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FASCInitialized,UAbilitySystemComponent*,ASC,UAttributeSet*,AS);

UCLASS()
class GASBASE_API ACBaseCharacter : public ACharacter,public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACBaseCharacter();
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual UAttributeSet* GetAttributeSet() const {return nullptr;};
	void SetAlive(bool Value){bAlive = Value;};
	bool GetAlive(){return bAlive;};
	
	
	UPROPERTY(BlueprintAssignable)
	FASCInitialized OnASCInitialized;
	
	UFUNCTION(BlueprintCallable,Category = "GASBase|Death")
	virtual void HandleRespawn();
	
protected:
	void GiveStartupAbilities();
	void InitializeAttributes() const; 
	
	void OnHealthChanged(const FOnAttributeChangeData& AttributeChangeData);
	virtual void HandleDeath();
private:
	
	UPROPERTY(EditDefaultsOnly,Category = "GASBase|Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;
	
	UPROPERTY(EditDefaultsOnly,Category = "GASBase|Effects")
	TSubclassOf<UGameplayEffect> InitializeAttributesEffect;
	
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true),Replicated)
	bool bAlive = true;
};
