// Fill out your copyright notice in the Description page of Project Settings.


#include "Sword.h"

#include "Slash.h"

void ASword::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                            UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                            const FHitResult& SweepResult)
{
	Super::OnBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red,TEXT("SWORD"));
	}

	ASlash* Slash = Cast<ASlash>(OtherActor);
	if (Slash)
	{
		FAttachmentTransformRules TransformRules(EAttachmentRule::SnapToTarget,true);
		ItemMeshComponent->AttachToComponent(Slash->GetMesh(), TransformRules, FName("hand_r_socket"));
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
