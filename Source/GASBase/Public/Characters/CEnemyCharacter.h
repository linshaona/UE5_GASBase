// Make by linshao

#pragma once

#include "CoreMinimal.h"
#include "CBaseCharacter.h"
#include "CEnemyCharacter.generated.h"

class UAttributeSet;

UCLASS()
class GASBASE_API ACEnemyCharacter : public ACBaseCharacter
{
	GENERATED_BODY()

public:

	ACEnemyCharacter();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual UAttributeSet* GetAttributeSet() const override;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="GASBase|AI")
	float AcceptanceRadius{500.0f};
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="GASBase|AI")
	float MinAttackDelay{0.1f};
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="GASBase|AI")
	float MaxAttackDelay{0.5f};
	
protected:
	
	virtual void BeginPlay() override;
	virtual void HandleDeath() override;

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
};
