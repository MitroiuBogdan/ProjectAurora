// Fill out your copyright notice in the Description page of Project Settings.


#include "Sword.h"

#include "Slash.h"
#include "Components/BoxComponent.h"


ASword::ASword()
{
	RootComponent = ItemMeshComponent;
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetupAttachment(ItemMeshComponent);
}

void ASword::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                            UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                            const FHitResult& SweepResult)
{
	Super::OnBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red,TEXT("SWORD"));
	}
}

void ASword::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                          int32 OtherBodyIndex)
{
	Super::OnEndOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red,TEXT("SWORD"));
	}
}


void ASword::Equip(USceneComponent* InParent, FName SocketName)
{
	AttachMeshToSocket(InParent, SocketName);
	SwordState = EItemState::EIS_Equiped;
}

void ASword::AttachMeshToSocket(USceneComponent* InParent, FName SocketName)
{
	FAttachmentTransformRules TransformRules(EAttachmentRule::SnapToTarget, true);
	ItemMeshComponent->AttachToComponent(InParent, TransformRules, SocketName);
}
