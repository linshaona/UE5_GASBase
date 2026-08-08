// Make by linshao


#include "Utils/CBlueprintLibrary.h"

#include "Characters/CBaseCharacter.h"
#include "Kismet/GameplayStatics.h"

EHitDirection UCBlueprintLibrary::GetHitDirection(const FVector& TargetForward, const FVector& ToInstigator)
{
	
	//向量点乘 a·b=|a||b|cos<a,b> 其中若a,b为单位向量，则有a·b=cos<a,b>,可以计算相对方向
	const float Dot = FVector::DotProduct(TargetForward,ToInstigator);
	if (Dot < -0.5f)
	{
		return EHitDirection::Back;
	}
	
	if (Dot < 0.5f)
	{
		//叉乘 axb=|a||b|sin<a,b>
		const FVector Cross = FVector::CrossProduct(TargetForward,ToInstigator);
		if (Cross.Z < 0.0f)
		{
			return EHitDirection::Left;
		}
		
		return EHitDirection::Right;
	}
	
	return EHitDirection::Forward;
}
	
FName UCBlueprintLibrary::GetHitDirectionName(const EHitDirection& HitDirection)
{
		switch (HitDirection)
		{
			case EHitDirection::Left : return FName("Left");
			case EHitDirection::Right : return FName("Right");
			case EHitDirection::Back : return FName("Back");
			case EHitDirection::Forward : return FName("Forward");
			default: return FName("None");
		}
}

FClosestActorWithTagResult UCBlueprintLibrary::FindClosestActorWithTag(const UObject* WorldContextObject,const FVector& Origin, const FName& Tag)
{
	TArray<AActor*> ActorsWithTag;
	UGameplayStatics::GetAllActorsWithTag(WorldContextObject, Tag, ActorsWithTag);
	
	float ClosestDistance = TNumericLimits<float>::Max();
	AActor* ClosestActor = nullptr;
	
	for (AActor* Actor : ActorsWithTag)
	{
		if (!IsValid(Actor))continue;
		ACBaseCharacter* BaseCharacter = Cast<ACBaseCharacter>(Actor);
		if (!IsValid(BaseCharacter))continue;
		
		const float Distance = FVector::Dist(Origin,Actor->GetActorLocation());
		if (Distance < ClosestDistance)
		{
			ClosestDistance = Distance;
			ClosestActor = Actor;
		}
	}
	
	FClosestActorWithTagResult Result;
	Result.Actor = ClosestActor;
	Result.Distance = ClosestDistance;
	return Result;
}
	
	

