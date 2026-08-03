// Make by linshao

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "CEnemyCharacter.generated.h"

UCLASS()
class GASBASE_API ACEnemyCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:

	ACEnemyCharacter();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
};
