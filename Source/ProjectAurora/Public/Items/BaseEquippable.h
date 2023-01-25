#pragma once

#include "CoreMinimal.h"
#include "enums/ECharacterState.h"
#include "GameFramework/Actor.h"
#include "BaseEquippable.generated.h"

UCLASS()
class PROJECTAURORA_API ABaseEquippable : public AActor
{
	GENERATED_BODY()


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
	UFUNCTION(BlueprintCallable)
	virtual void OnEquipped(USceneComponent* InParent, FName SocketName);
	UFUNCTION(BlueprintCallable)
	virtual void OnUnequipped();
	

	//INLINES
	UPrimitiveComponent* GetMesh();
	// FORCEINLINE EItemState GetItemState() { return this->ItemState; }
	// FORCEINLINE void SetItemState(EItemState ItemState) { this->ItemState = ItemState; }

private:
	void AttachMeshToSocket(USceneComponent* InParent, FName SocketName);
};
