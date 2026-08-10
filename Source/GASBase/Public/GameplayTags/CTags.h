#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"

namespace CTags
{
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(None);
	namespace SetByCaller
	{
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Projectile);
	}
	
	namespace CAbilities
	{
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(ActivateOnGiven);
		
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Primary);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Secondary);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tertiary);
	
	}
	
	namespace Events
	{
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(KillScored);
		
		namespace Player
		{
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(HitReact);
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(Death);
		}
		namespace Enemy
		{
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(HitReact);
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(MeleeTraceHit);
		}
	}
	
	
}
