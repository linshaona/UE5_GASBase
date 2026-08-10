// Make by linshao


#include "UI/CWidgetComponent.h"

#include "Blueprint/WidgetTree.h"
#include "UI/CAttributeWidget.h"


void UCWidgetComponent::BeginPlay()
{
	Super::BeginPlay();

	InitAbilitySystemData();
	
	if (!IsASCInitialized())
	{
		GASBaseCharacter->OnASCInitialized.AddDynamic(this,&ThisClass::OnASCInitialized);
		return;
	}
	
	InitializeAttributeDelegate();
}

void UCWidgetComponent::InitAbilitySystemData()
{
	GASBaseCharacter = Cast<ACBaseCharacter>(GetOwner());
	AttributeSet = Cast<UCAttributeSet>(GASBaseCharacter->GetAttributeSet());
	AbilitySystemComponent = Cast<UCAbilitySystemComponent>(GASBaseCharacter->GetAbilitySystemComponent());
}

bool UCWidgetComponent::IsASCInitialized()
{
	return AbilitySystemComponent.IsValid() && AttributeSet.IsValid();
}

void UCWidgetComponent::InitializeAttributeDelegate()
{
	if (!AttributeSet->bAttributesInitialized)
	{
		AttributeSet->OnAttributeSetInitialized.AddDynamic(this,&ThisClass::BindToAttributeChanges);
	}
	else
	{
		BindToAttributeChanges();
	}
}


void UCWidgetComponent::OnASCInitialized(UAbilitySystemComponent* ASC, UAttributeSet* AS)  
{
	AbilitySystemComponent = Cast<UCAbilitySystemComponent>(ASC);
	AttributeSet = Cast<UCAttributeSet>(AS);
	
	if (!IsASCInitialized()) return;
	
	InitializeAttributeDelegate();
	
}

void UCWidgetComponent::BindToAttributeChanges()
{
	for (const TTuple<FGameplayAttribute,FGameplayAttribute>& Pair : AttributeMap)
	{
		BindWidgetToAttributeChanges(GetUserWidgetObject(),Pair);//检查widget
		
		GetUserWidgetObject()->WidgetTree->ForEachWidget([this,&Pair](UWidget* ChildWidget)
		{
			BindWidgetToAttributeChanges(ChildWidget,Pair);
		});
	}
}
void UCWidgetComponent::BindWidgetToAttributeChanges(UWidget* WidgetObject,const TTuple<FGameplayAttribute, FGameplayAttribute>& Pair) const
{
	UCAttributeWidget* AttributeWidget = Cast<UCAttributeWidget>(WidgetObject);
	if (!IsValid(AttributeWidget)) return;
	if (!AttributeWidget->MatchesAttribute(Pair)) return;
	AttributeWidget->AvatarActor=GASBaseCharacter;
		
	AttributeWidget->OnAttributeChanged(Pair,AttributeSet.Get(),0);//初始化
		
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Key).AddLambda([this,AttributeWidget,&Pair](const FOnAttributeChangeData& AttributeChangeData)
	{
		AttributeWidget->OnAttributeChanged(Pair,AttributeSet.Get(),AttributeChangeData.OldValue);
	});
}



      

