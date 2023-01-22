// Fill out your copyright notice in the Description page of Project Settings.


#include "Sword.h"

#include "Slash.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetSystemLibrary.h"


ASword::ASword()
{
	RootComponent = ItemMeshComponent;
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetupAttachment(ItemMeshComponent);

	BoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	BoxComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
	// BoxComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);

	StartBoxTrace = CreateDefaultSubobject<USceneComponent>(TEXT("StartBoxTrace"));
	EndBoxTrace = CreateDefaultSubobject<USceneComponent>(TEXT("EndBoxTrace"));

	StartBoxTrace->SetupAttachment(ItemMeshComponent);
	EndBoxTrace->SetupAttachment(ItemMeshComponent);
}

void ASword::BeginPlay()
{
	Super::BeginPlay();
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ASword::OnBoxOverlap);
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

void ASword::OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                          int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("BOX Overlap"));
	const FVector Start = StartBoxTrace->GetComponentLocation();
	const FVector End = EndBoxTrace->GetComponentLocation();

	TArray<AActor*> ActorsToIgnore;
	FHitResult BoxHit;
	ActorsToIgnore.Add(this);
	UKismetSystemLibrary::BoxTraceSingle(this, Start, End, FVector(5.f, 5.f, 5.f),
	                                     StartBoxTrace->GetComponentRotation(), TraceTypeQuery1, false, ActorsToIgnore,
	                                     EDrawDebugTrace::ForDuration, BoxHit, true);
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
