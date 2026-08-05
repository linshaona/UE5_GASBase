// Make by linshao

#include "AbilitySystem/Abilities/Player/CPrimary.h"
#include "Engine/OverlapResult.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayTags/CTags.h"

TArray<AActor*> UCPrimary::HitBoxOverlapTest()
{
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(GetAvatarActorFromActorInfo());
	
	//防止打到发起者
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActors(ActorsToIgnore);
	
	FCollisionResponseParams ResponseParams;
	ResponseParams.CollisionResponse.SetAllChannels(ECR_Ignore);
	ResponseParams.CollisionResponse.SetResponse(ECC_Pawn,ECR_Block);
	
	TArray<FOverlapResult> OverlapResults;
	FCollisionShape Sphere = FCollisionShape::MakeSphere(HitBoxRadius);
	
	const FVector Forward = GetAvatarActorFromActorInfo()->GetActorForwardVector() * HitBoxForwardOffset;
	const FVector HitBoxLocation = GetAvatarActorFromActorInfo()->GetActorLocation() + Forward + FVector(0.0f,0.0f,HitBoxElevationOffset);
	
	GetWorld()->OverlapMultiByChannel(OverlapResults, HitBoxLocation, FQuat::Identity,ECC_Visibility,Sphere,QueryParams,ResponseParams);
	
	TArray<AActor*> ActorsHit;
	for (const FOverlapResult& Result : OverlapResults)
	{
		if (!IsValid(Result.GetActor())) 
			continue;
		
		ActorsHit.AddUnique(Result.GetActor());
	}
	
	
	
	
	if (bDrawDebug)
	{
		DrawHitBoxOverlapDebugs(OverlapResults,HitBoxLocation);
	}
	
	return ActorsHit;
}

void UCPrimary::SendHitReactEventToActor(const TArray<AActor*>& ActorsHit)
{
	//发送事件
	for (AActor* HitActor : ActorsHit)
	{
		FGameplayEventData Payload;
		Payload.Instigator = GetAvatarActorFromActorInfo();
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(HitActor, CTags::Events::Enemy::HitReact,Payload);
	}
}

void UCPrimary::DrawHitBoxOverlapDebugs(const TArray<FOverlapResult>& OverlapResults,const FVector& HitBoxLocation) const
{
	DrawDebugSphere(GetWorld(), HitBoxLocation,HitBoxRadius, 16,FColor::Red,false ,3.0f);
		
		for (const FOverlapResult& Result : OverlapResults)
		{
			
			if (IsValid(Result.GetActor()))
			{
				FVector DebugLocation = Result.GetActor()->GetActorLocation();
				DebugLocation.Z+=100.0f;
				DrawDebugSphere(GetWorld(), DebugLocation,30.0f, 10,FColor::Green,false ,3.0f);
			}
		}
	
}
