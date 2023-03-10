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

private:
	UPROPERTY(EditAnywhere, Category="Weapon Properties")
	float Damage = 30.f;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sword Box")
	class UBoxComponent* BoxComponent;

	UPROPERTY(VisibleAnywhere, Category = "Sword Box")
	USceneComponent* StartBoxTrace;
	UPROPERTY(VisibleAnywhere, Category = "Sword Box")
	USceneComponent* EndBoxTrace;

	TArray<AActor*> ActorsToIgnore;

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
	void Equip(USceneComponent* InParent, FName SocketName, AActor* NewOwner, APawn* NewInstigator);
	void AttachMeshToSocket(USceneComponent* InParent, FName SocketName);

	UFUNCTION(BlueprintImplementableEvent)
	void CreateField(const FVector& FieldLocation);

	FORCEINLINE UBoxComponent* GetBoxCollision() { return this->BoxComponent; }
};
