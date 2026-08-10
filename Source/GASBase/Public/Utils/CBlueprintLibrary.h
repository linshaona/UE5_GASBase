// Make by linshao

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "GameplayTags/CTags.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CBlueprintLibrary.generated.h"

UENUM(BlueprintType)
enum class EHitDirection : uint8
{
	Left,
	Right,
	Forward,
	Back,
};

USTRUCT(BlueprintType)
struct FClosestActorWithTagResult
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite)
	TWeakObjectPtr<AActor> Actor;
	
	UPROPERTY(BlueprintReadWrite)
	float Distance{0.0f};
};


UCLASS()
class GASBASE_API UCBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure)
	static EHitDirection GetHitDirection(const FVector& TargetForward,const FVector&ToInstigator);
	
	UFUNCTION(BlueprintPure)
	static FName GetHitDirectionName(const EHitDirection& HitDirection);
	
	UFUNCTION(BlueprintCallable)
	static FClosestActorWithTagResult FindClosestActorWithTag(const UObject* WorldContextObject,const FVector& Origin,const FName& TagName);
	
	UFUNCTION(BlueprintCallable)
	static void SendDamageEventToPlayer(AActor* Target,const TSubclassOf<UGameplayEffect>& DamageEffect,UPARAM(ref) FGameplayEventData& Payload,const FGameplayTag& DataTag,float Damage, FGameplayTag EventTagOverride = FGameplayTag() ,UObject* OptionalParticleSystem = nullptr);
	
	UFUNCTION(BlueprintCallable)
	static void SendDamageEventToPlayers(TArray<AActor*> Targets,const TSubclassOf<UGameplayEffect>& DamageEffect,UPARAM(ref) FGameplayEventData& Payload,const FGameplayTag& DataTag,float Damage, FGameplayTag EventTagOverride = FGameplayTag() ,UObject* OptionalParticleSystem = nullptr);
	
	UFUNCTION(BlueprintCallable,Category = "GASBase|Abilities")
	static TArray<AActor*>  HitBoxOverlapTest(AActor* AvatarActor, float HitBoxRadius=0.0f, float HitBoxElevationOffset=0.0f, float HitBoxForwardOffset=0.0f,const bool&bDrawDebug=false);

		
	static void DrawHitBoxOverlapDebugs(const UObject* WorldContextObject,const TArray<FOverlapResult>& OverlapResults,const FVector& HitBoxLocation,const float&HitBoxRadius);
	
	UFUNCTION(BlueprintCallable,Category = "GASBase|Abilities")
	static TArray<AActor*> ApplyKnockback(AActor* AvatarActor,const TArray<AActor*>& HitActors,float InnerRadius,float OuterRadius,float LaunchForceMagnitude,float RotationAngle=45.0f,bool bDrawDebug=false);
};
