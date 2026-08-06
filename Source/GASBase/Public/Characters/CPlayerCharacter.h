// Make by linshao

#pragma once

#include "CoreMinimal.h"
#include "CBaseCharacter.h"
#include "CPlayerCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class GASBASE_API ACPlayerCharacter : public ACBaseCharacter//,public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACPlayerCharacter();
	virtual UAttributeSet* GetAttributeSet() const override;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	
private:
	UPROPERTY(VisibleAnywhere,Category = "Camera")
	TObjectPtr<USpringArmComponent> CameraBoom;
	
	UPROPERTY(VisibleAnywhere,Category = "Camera")
	TObjectPtr<UCameraComponent> FollowCamera;
	
};
