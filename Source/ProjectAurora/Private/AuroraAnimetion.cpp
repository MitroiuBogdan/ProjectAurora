// Fill out your copyright notice in the Description page of Project Settings.


#include "AuroraAnimetion.h"

#include "Slash.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UAuroraAnimetion::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	AuroraCharacter = Cast<ASlash>(TryGetPawnOwner());
	if (AuroraCharacter)
	{
		CharacterMovementComponent = AuroraCharacter->GetCharacterMovement();
	}
}

void UAuroraAnimetion::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (CharacterMovementComponent)
	{
		const FVector Velocity = CharacterMovementComponent->Velocity;
		GroundSpeed = UKismetMathLibrary::VSizeXY(Velocity);
		Is_Falling = CharacterMovementComponent->IsFalling();
	}
}
