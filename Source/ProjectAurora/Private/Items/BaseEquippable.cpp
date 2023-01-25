#include "Items/BaseEquippable.h"

#include "enums/ECharacterState.h"


ABaseEquippable::ABaseEquippable()
{
	PrimaryActorTick.bCanEverTick = true;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("ItemMeshComponent");
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMeshComponent");
	// ItemState=EItemState::EIS_Unequiped;
}

void ABaseEquippable::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseEquippable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseEquippable::OnEquipped(USceneComponent* InParent, FName SocketName)
{
	// ItemState = EItemState::EIS_Equiped;
	AttachMeshToSocket(InParent, SocketName);
}

void ABaseEquippable::OnUnequipped()
{
	// ItemState = EItemState::EIS_Unequiped;
}

UPrimitiveComponent* ABaseEquippable::GetMesh()
{
	if (MeshComponent)
	{
		return MeshComponent;
	}
	return SkeletalMeshComponent;
}

void ABaseEquippable::AttachMeshToSocket(USceneComponent* InParent, FName SocketName)
{
	FAttachmentTransformRules TransformRules(EAttachmentRule::SnapToTarget, true);
	GetMesh()->AttachToComponent(InParent, TransformRules, SocketName);
}
