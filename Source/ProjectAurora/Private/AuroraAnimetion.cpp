// Fill out your copyright notice in the Description page of Project Settings.


#include "AuroraAnimetion.h"

#include "AuroraCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UAuroraAnimetion::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	AuroraCharacter = Cast<AAuroraCharacter>(TryGetPawnOwner());
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
	}
}
