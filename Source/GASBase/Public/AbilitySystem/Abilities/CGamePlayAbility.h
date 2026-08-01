// Make by linshao

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "CGamePlayAbility.generated.h"

/**
 * 
 */
UCLASS()
class GASBASE_API UCGamePlayAbility : public UGameplayAbility
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = "GASBase|Debug")
	bool bDrawDebug = false;
};
