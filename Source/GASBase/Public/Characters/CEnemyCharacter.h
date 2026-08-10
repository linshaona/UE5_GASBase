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
	
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	ACEnemyCharacter();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual UAttributeSet* GetAttributeSet() const override;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="GASBase|AI")
	float AcceptanceRadius{500.0f};
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="GASBase|AI")
	float MinAttackDelay{0.1f};
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="GASBase|AI")
	float MaxAttackDelay{0.5f};
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Replicated)
	bool bIsBeingLaunched{false};
	
	UFUNCTION()
	void StopMovingUntilLanding();
protected:
	
	virtual void BeginPlay() override;
	virtual void HandleDeath() override;

private:
	UFUNCTION()
	void EnableMovementOnLanded(const FHitResult& Hit);
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
};
