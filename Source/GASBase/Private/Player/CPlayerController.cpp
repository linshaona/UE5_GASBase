// Make by linshao


#include "GASBase/Public/Player/CPlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/Character.h"
#include "GameplayTags/CTags.h"

void ACPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	
	if (!IsValid(InputSubsystem)) return;
	
	if (IsValid(InputSubsystem))
	{
		for (UInputMappingContext* Context:InputMappingContexts)
		{
			InputSubsystem->AddMappingContext(Context,0);
		}
	}
	
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	if (!IsValid(EnhancedInputComponent)) return;
	
	EnhancedInputComponent->BindAction(JumpAction,ETriggerEvent::Started,this,&ThisClass::Jump);
	EnhancedInputComponent->BindAction(JumpAction,ETriggerEvent::Completed,this,&ThisClass::StopJumping);
	EnhancedInputComponent->BindAction(MoveAction,ETriggerEvent::Triggered,this,&ThisClass::Move);
	EnhancedInputComponent->BindAction(LookAction,ETriggerEvent::Triggered,this,&ThisClass::Look);
	
	EnhancedInputComponent->BindAction(PrimaryAction,ETriggerEvent::Started,this,&ThisClass::Primary);
	EnhancedInputComponent->BindAction(SecondaryAction,ETriggerEvent::Started,this,&ThisClass::Secondary);
	EnhancedInputComponent->BindAction(TertiaryAction,ETriggerEvent::Started,this,&ThisClass::Tertiary);
}

void ACPlayerController::Jump()
{
	if (!IsValid(GetCharacter()))
		return;
		
		GetCharacter()->Jump();
	
}     

void ACPlayerController::StopJumping()
{
	if (!IsValid(GetCharacter()))
		return
	
	GetCharacter()->StopJumping();
	
}

void ACPlayerController::Move(const FInputActionValue& Value)
{
	if (!IsValid(GetPawn()))
		return;
	
	const FVector2D MovementVector = Value.Get<FVector2D>();
	
	//找到正前方
	const FRotator YawRotation(0.0f,GetControlRotation().Yaw,0.0f);
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	
	GetPawn()->AddMovementInput(ForwardDirection,MovementVector.Y);
	GetPawn()->AddMovementInput(RightDirection,MovementVector.X);
}

void ACPlayerController::Look(const FInputActionValue& Value)
{
	
	const FVector2D LookAxisVector = Value.Get<FVector2D>();
	
	AddYawInput(LookAxisVector.X);
	AddPitchInput(LookAxisVector.Y);
}

void ACPlayerController::Primary()
{
	ActivateAbility(CTags::CAbilities::Primary);
}

void ACPlayerController::Secondary()
{
	ActivateAbility(CTags::CAbilities::Secondary);
	UE_LOG(LogTemp,Display,TEXT("Secondary"));
}

void ACPlayerController::Tertiary()
{
	ActivateAbility(CTags::CAbilities::Tertiary);
	UE_LOG(LogTemp,Display,TEXT("Tertiary"));
}

void ACPlayerController::ActivateAbility(const FGameplayTag& AbilityTag) const
{
	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn());
	
	if (!IsValid(ASC))return;
	
	ASC->TryActivateAbilitiesByTag(AbilityTag.GetSingleTagContainer());
	
}
