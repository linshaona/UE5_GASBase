// Make by linshao

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameplayEffect.h"
#include "GameFramework/Character.h"
#include "CBaseCharacter.generated.h"

namespace GASBaseTags
{
	extern GASBASE_API const FName Player;
}

class UGameplayAbility;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FASCInitialized,UAbilitySystemComponent*,ASC,UAttributeSet*,AS);

UCLASS(Abstract)
class GASBASE_API ACBaseCharacter : public ACharacter,public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACBaseCharacter();
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual UAttributeSet* GetAttributeSet() const {return nullptr;};
	void SetAlive(const bool&Value){bAlive = Value;};
	bool GetAlive() const {return bAlive;};
	
	
	UPROPERTY(BlueprintAssignable)
	FASCInitialized OnASCInitialized;
	
	UFUNCTION(BlueprintCallable,Category = "GASBase|Death")
	virtual void HandleRespawn();
	
	UFUNCTION(BlueprintCallable,Category = "GASBase|Attributes")
	void ResetAttributes(); 
	
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
	
	UPROPERTY(EditDefaultsOnly,Category = "GASBase|Effects")
	TSubclassOf<UGameplayEffect> ResetAttributesEffect;
	
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true),Replicated)
	bool bAlive = true;
};
