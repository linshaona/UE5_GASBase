// Make by linshao

#pragma once

#include "CoreMinimal.h"
#include "InputMappingContext.h"
#include "GameFramework/PlayerController.h"
#include "CPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class GASBASE_API ACPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void SetupInputComponent() override;
	
private:
	
	UPROPERTY(EditDefaultsOnly,Category = "GASBase|Input")
	TArray<TObjectPtr<UInputMappingContext>>InputMappingContexts;
	
	UPROPERTY(EditDefaultsOnly,Category = "GASBase|Input")
	TObjectPtr<UInputAction>JumpAction;
	
	UPROPERTY(EditDefaultsOnly,Category = "GASBase|Input")
	TObjectPtr<UInputAction>MoveAction;
	
	UPROPERTY(EditDefaultsOnly,Category = "GASBase|Input")
	TObjectPtr<UInputAction>LookAction;
	
	UPROPERTY(EditDefaultsOnly,Category = "GASBase|Input")
	TObjectPtr<UInputAction>PrimaryAction;
	
		
	UPROPERTY(EditDefaultsOnly,Category = "GASBase|Input")
	TObjectPtr<UInputAction>SecondaryAction;
	
		
	UPROPERTY(EditDefaultsOnly,Category = "GASBase|Input")
	TObjectPtr<UInputAction>TertiaryAction;
public:
	void Jump();
	void StopJumping();
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void ActivateAbility(const FGameplayTag& AbilityTag) const;
	
	//abilities
	void Primary();
	void Secondary();
	void Tertiary();
};
