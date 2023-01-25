// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/BaseEquippable.h"
#include "BaseWeapon.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTAURORA_API ABaseWeapon : public ABaseEquippable
{
	GENERATED_BODY()

public:
	virtual void OnEquipped(USceneComponent* InParent, FName SocketName) override;
	virtual void OnUnequipped() override;
};
