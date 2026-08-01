// Make by linshao

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "CPlayerState.generated.h"


class UAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class GASBASE_API ACPlayerState : public APlayerState , public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:
	ACPlayerState();
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const;
private:
	UPROPERTY(VisibleAnywhere,Category="GASBase|Abilities")
	TObjectPtr<UAbilitySystemComponent>	 AbilitySystemComponent;
};
