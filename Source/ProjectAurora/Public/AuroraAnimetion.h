// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AuroraAnimetion.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTAURORA_API UAuroraAnimetion : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	class AAuroraCharacter* AuroraCharacter;

	UPROPERTY(BlueprintReadOnly, Category= Movement)
	class UCharacterMovementComponent* CharacterMovementComponent;

	UPROPERTY(BlueprintReadOnly, Category= Movement)
	float GroundSpeed;

	UPROPERTY(BlueprintReadOnly, Category= Movement)
	bool Is_Falling;

	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
};
