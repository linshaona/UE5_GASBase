// Make by linshao

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/CGamePlayAbility.h"
#include "CPrimary.generated.h"

/**
 * 
 */
UCLASS()
class GASBASE_API UCPrimary : public UCGameplayAbility
{
	GENERATED_BODY()
	
public:
	
	// UFUNCTION(BlueprintCallable,Category = "GASBase|Abilities")
	// TArray<AActor*>  HitBoxOverlapTest();
	//
	UFUNCTION(BlueprintCallable,Category = "GASBase|Abilities")
	void SendHitReactEventToActor(const TArray<AActor*>& ActorsHit);
	
protected:
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category = "GASBase|Abilities")
	float HitBoxRadius = 100.0f;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category = "GASBase|Abilities")
	float HitBoxForwardOffset = 200.0f;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category = "GASBase|Abilities")
	float HitBoxElevationOffset = 20.0f;
	
	
	//void DrawHitBoxOverlapDebugs(const TArray<FOverlapResult>& OverlapResults,const FVector& HitBoxLocation) const;
};
