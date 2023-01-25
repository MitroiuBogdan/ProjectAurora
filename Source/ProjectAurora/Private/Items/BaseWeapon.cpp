// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/BaseWeapon.h"

void ABaseWeapon::OnEquipped(USceneComponent* InParent, FName SocketName)
{
	Super::OnEquipped(InParent, SocketName);
}

void ABaseWeapon::OnUnequipped()
{
	Super::OnUnequipped();
}
