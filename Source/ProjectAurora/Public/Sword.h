#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "enums/ECharacterState.h"
#include "Sword.generated.h"


UCLASS()
class PROJECTAURORA_API ASword : public AItem
{
	GENERATED_BODY()
	EItemState SwordState;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sword Box")
	class UBoxComponent* BoxComponent;

protected:
	ASword();
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                            UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                            const FHitResult& SweepResult) override;

	virtual void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                          UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

public:
	void Equip(USceneComponent* InParent, FName SocketName);
	void AttachMeshToSocket(USceneComponent* InParent, FName SocketName);
};
