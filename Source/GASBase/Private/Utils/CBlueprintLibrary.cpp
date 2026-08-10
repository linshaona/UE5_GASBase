// Make by linshao


#include "Utils/CBlueprintLibrary.h"

#include "AbilitySystem/CAttributeSet.h"
#include "Characters/CBaseCharacter.h"
#include "Characters/CEnemyCharacter.h"
#include "Engine/OverlapResult.h"
#include "GameplayTags/CTags.h"
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

void UCBlueprintLibrary::SendDamageEventToPlayer(AActor* Target, const TSubclassOf<UGameplayEffect>& DamageEffect, FGameplayEventData& Payload, const FGameplayTag& DataTag, float Damage, FGameplayTag EventTagOverride ,UObject* OptionalParticleSystem)
{
	ACBaseCharacter* PlayerCharacter = Cast<ACBaseCharacter>(Target);
	if (!IsValid(PlayerCharacter))return;
	if (!PlayerCharacter->GetAlive())return;

	FGameplayTag EventTag;
	if (!EventTagOverride.MatchesTagExact(FGameplayTag()))
	{
		EventTag=EventTagOverride;
	}
	else
	{
		
		UCAttributeSet* AttributeSet = Cast<UCAttributeSet>(PlayerCharacter->GetAttributeSet());
		if (!IsValid(AttributeSet))return;

		const bool bLethal = AttributeSet->GetHealth() - Damage <= 0.0f;
		EventTag = bLethal?CTags::Events::Player::Death:CTags::Events::Player::HitReact;
	}
	
	

	
	Payload.OptionalObject = OptionalParticleSystem;
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(PlayerCharacter,EventTag,Payload);

	UAbilitySystemComponent* TargetASC = PlayerCharacter->GetAbilitySystemComponent();
	if (!IsValid(TargetASC))return;

	FGameplayEffectContextHandle ContextHandle = TargetASC->MakeEffectContext();
	FGameplayEffectSpecHandle SpecHandle = TargetASC->MakeOutgoingSpec(DamageEffect,1.0f,ContextHandle);


	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle,DataTag,-Damage);

	TargetASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
}

void UCBlueprintLibrary::SendDamageEventToPlayers(TArray<AActor*> Targets,
	const TSubclassOf<UGameplayEffect>& DamageEffect, FGameplayEventData& Payload, const FGameplayTag& DataTag,
	float Damage, FGameplayTag EventTagOverride, UObject* OptionalParticleSystem)
{
	for (AActor* TargetActor : Targets)
	{
		SendDamageEventToPlayer(TargetActor,DamageEffect,Payload,DataTag,Damage,EventTagOverride,OptionalParticleSystem);
	}
}

TArray<AActor*> UCBlueprintLibrary::HitBoxOverlapTest(AActor* AvatarActor, float HitBoxRadius, float HitBoxElevationOffset, float HitBoxForwardOffset,const bool&bDrawDebug)
{
	TArray<AActor*> ActorsToIgnore;
	if (!IsValid(AvatarActor))return ActorsToIgnore;
	
	ActorsToIgnore.Add(AvatarActor);
	
	//防止打到发起者
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActors(ActorsToIgnore);
	
	FCollisionResponseParams ResponseParams;
	ResponseParams.CollisionResponse.SetAllChannels(ECR_Ignore);
	ResponseParams.CollisionResponse.SetResponse(ECC_Pawn,ECR_Block);
	
	TArray<FOverlapResult> OverlapResults;
	FCollisionShape Sphere = FCollisionShape::MakeSphere(HitBoxRadius);
	
	const FVector Forward = AvatarActor->GetActorForwardVector() * HitBoxForwardOffset;
	const FVector HitBoxLocation = AvatarActor->GetActorLocation() + Forward + FVector(0.0f,0.0f,HitBoxElevationOffset);
	
	UWorld* World = GEngine->GetWorldFromContextObject(AvatarActor,EGetWorldErrorMode::LogAndReturnNull);
	if (!IsValid(World))return ActorsToIgnore;
	
	World->OverlapMultiByChannel(OverlapResults, HitBoxLocation, FQuat::Identity,ECC_Visibility,Sphere,QueryParams,ResponseParams);
	
	TArray<AActor*> ActorsHit;
	for (const FOverlapResult& Result : OverlapResults)
	{
		// if (!IsValid(Result.GetActor())) 
		// 	continue;
		ACBaseCharacter* BaseCharacter = Cast<ACBaseCharacter>(Result.GetActor());
		if (!IsValid(BaseCharacter)||!BaseCharacter->GetAlive())
			continue;
		
		ActorsHit.AddUnique(Result.GetActor());
	}
	
	
	
	
	if (bDrawDebug)
	{
		DrawHitBoxOverlapDebugs(AvatarActor,OverlapResults,HitBoxLocation,HitBoxRadius);
	}
	
	return ActorsHit;
}

void UCBlueprintLibrary::DrawHitBoxOverlapDebugs(const UObject* WorldContextObject,const TArray<FOverlapResult>& OverlapResults,
	const FVector& HitBoxLocation,const float&HitBoxRadius)
{
		
	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject,EGetWorldErrorMode::LogAndReturnNull);
	if (!IsValid(World))return;
	DrawDebugSphere(World, HitBoxLocation,HitBoxRadius, 16,FColor::Red,false ,3.0f);
		
	for (const FOverlapResult& Result : OverlapResults)
	{
			
		if (IsValid(Result.GetActor()))
		{
			FVector DebugLocation = Result.GetActor()->GetActorLocation();
			DebugLocation.Z+=100.0f;
			DrawDebugSphere(World, DebugLocation,30.0f, 10,FColor::Green,false ,3.0f);
		}
	}
}

TArray<AActor*> UCBlueprintLibrary::ApplyKnockback(AActor* AvatarActor, const TArray<AActor*>& HitActors, float InnerRadius,float OuterRadius, float LaunchForceMagnitude, float RotationAngle, bool bDrawDebug)
{
	
	if (!IsValid(AvatarActor))return TArray<AActor*>() ;
	
	for (AActor* HitActor : HitActors)
	{
	  	ACharacter*HitCharacter = Cast<ACharacter>(HitActor);
	  	if (!IsValid(HitCharacter))continue;
		
		const FVector HitCharacterLocation = HitCharacter->GetActorLocation();
		const FVector AvatarLocation = AvatarActor->GetActorLocation();
	  	
	  	const FVector ToHitActor  = HitCharacterLocation-AvatarLocation;
		const float Distance = FVector::Dist(AvatarLocation,HitCharacterLocation);
		
		float LaunchForce = 0.0f;
		if (Distance > OuterRadius) continue;
		
	  	if (Distance<= InnerRadius)
	  	{
	  		LaunchForce = LaunchForceMagnitude;
	  	}
	    else
	    {
		    const FVector2D FalloffRange(InnerRadius,OuterRadius);
	    	const FVector2D LaunchForceRange(LaunchForceMagnitude,0.0f);
	    	LaunchForce = FMath::GetMappedRangeValueClamped(FalloffRange,LaunchForceRange,Distance);
	    }
		
		if (bDrawDebug)
		{
			GEngine->AddOnScreenDebugMessage(-1,3.0f,FColor::Red,FString::Printf(TEXT("LaunchForce:%f"),LaunchForce));
		}
		
		FVector KnockbackForce = ToHitActor.GetSafeNormal();
		KnockbackForce.Z=0.0f;
		
		const FVector Right = KnockbackForce.RotateAngleAxis(90.0f,FVector::UpVector);
		KnockbackForce = KnockbackForce.RotateAngleAxis(-RotationAngle,Right) * LaunchForce;
		
		if (ACEnemyCharacter* EnemyCharacter = Cast<ACEnemyCharacter>(HitCharacter))
		{
			EnemyCharacter->StopMovingUntilLanding();
		}
		
		HitCharacter->LaunchCharacter(KnockbackForce,true,true);
	}
	return HitActors ;
}
	

