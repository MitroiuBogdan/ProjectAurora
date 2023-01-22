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

	UPROPERTY(VisibleAnywhere, Category = "Sword Box")
	class USceneComponent* StartBoxTrace;
	UPROPERTY(VisibleAnywhere, Category = "Sword Box")
	class USceneComponent* EndBoxTrace;

protected:
	ASword();
	virtual void BeginPlay() override;
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                            UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                            const FHitResult& SweepResult) override;

	virtual void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                          UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

	UFUNCTION()
	virtual void OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                          UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                          const FHitResult& SweepResult);

public:
	void Equip(USceneComponent* InParent, FName SocketName);
	void AttachMeshToSocket(USceneComponent* InParent, FName SocketName);

	FORCEINLINE UBoxComponent* GetBoxCollision() { return this->BoxComponent; }
};
