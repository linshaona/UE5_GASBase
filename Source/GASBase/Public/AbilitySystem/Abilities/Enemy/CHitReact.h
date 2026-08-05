// Make by linshao

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/CGameplayAbility.h"
#include "CHitReact.generated.h"

/**
 * 
 */
UCLASS()
class GASBASE_API UCHitReact : public UCGameplayAbility
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable,Category="GASBase|Abilities")
	void CacheHitDirectionVectors(AActor* Instigator);
	
	UPROPERTY(BlueprintReadOnly,Category="GASBase|Abilities")
	FVector AvatarForward;
	
	UPROPERTY(BlueprintReadOnly,Category="GASBase|Abilities")
	FVector ToInstigator;
};
