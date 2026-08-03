#include "GameplayTags/CTags.h"


namespace CTags
{
	namespace CAbilities
	{
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(ActivateOnGiven,"CTags.CAbilities.ActivateOnGiven","Activate on Given Ability");
		
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Primary,"CTags.CAbilities.Primary","Tag for the Primary Ability");
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Secondary,"CTags.CAbilities.Secondary","Tag for the Secondary Ability");
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Tertiary,"CTags.CAbilities.Tertiary","Tag for the Tertiary Ability");
		
	}
	
	namespace Events
	{
		namespace Enemy
		{
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(HitReact,"CTags.Events.Enemy.HitReact","Tag for the Enemy HitReact Event");
		}
	}
}
