// Make by linshao

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

class UGameplayAbility;

UCLASS()
class GASBASE_API ABaseCharacter : public ACharacter,public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	
protected:
	void GiveStartupAbilities();
private:
	
	UPROPERTY(EditDefaultsOnly,Category = "GASBase|Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;
};
