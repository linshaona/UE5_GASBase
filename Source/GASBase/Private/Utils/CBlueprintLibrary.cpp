// Make by linshao


#include "Utils/CBlueprintLibrary.h"

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
	
	

