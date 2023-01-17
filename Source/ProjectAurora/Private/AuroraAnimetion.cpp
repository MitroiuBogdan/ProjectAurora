// Fill out your copyright notice in the Description page of Project Settings.


#include "AuroraAnimetion.h"

#include "Slash.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UAuroraAnimetion::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	this->AuroraCharacter = Cast<ASlash>(TryGetPawnOwner());
	if (this->AuroraCharacter)
	{
		this->CharacterMovementComponent = this->AuroraCharacter->GetCharacterMovement();
	}
}

void UAuroraAnimetion::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (this->CharacterMovementComponent)
	{
		const FVector Velocity = this->CharacterMovementComponent->Velocity;
		this->GroundSpeed = UKismetMathLibrary::VSizeXY(Velocity);
		this->Is_Falling = this->CharacterMovementComponent->IsFalling();
		this->CharacterState = this->AuroraCharacter->GetCharacterState();
	}
}

