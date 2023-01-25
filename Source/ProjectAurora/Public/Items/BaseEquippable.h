#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseEquippable.generated.h"

UCLASS()
class PROJECTAURORA_API ABaseEquippable : public AActor
{
	GENERATED_BODY()

private:
	EItemState ItemState;

public:
	ABaseEquippable();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* MeshComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USkeletalMeshComponent* SkeletalMeshComponent;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void OnEquipped(USceneComponent* InParent, FName SocketName);
	virtual void OnUnequipped();
	//INLINES
	FORCEINLINE UPrimitiveComponent* GetMesh() { MeshComponent ? MeshComponent : SkeletalMeshComponent; }

private:
	void AttachMeshToSocket(USceneComponent* InParent, FName SocketName);
};
