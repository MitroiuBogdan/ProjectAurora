#pragma once

#include "CoreMinimal.h"
#include "enums/ECharacterState.h"
#include "GameFramework/Character.h"
#include "Slash.generated.h"


UCLASS()
class PROJECTAURORA_API ASlash : public ACharacter
{
	GENERATED_BODY()

public:
	ASlash();
	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* CameraBoom;
	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* ViewCamera;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleInstanceOnly)
	class AItem* OverlappingItem;
	ECharacterState CharacterState = ECharacterState::ECS_Unequipped;

	/**Animation Montages*/
	UPROPERTY(EditDefaultsOnly, Category= Montages)
	UAnimMontage* AttackMontage;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void MoveForward(float Value);
	virtual void MoveRight(float Value);
	virtual void ViewYaw(float Value);
	virtual void ViewPitch(float Value);
	void FKeyPressed();
	void Attack();

public:
	FORCEINLINE void SetOverlappingItem(AItem* Item) { this->OverlappingItem = Item; }
	FORCEINLINE AItem* GetOverlappingItem() { return this->OverlappingItem; }
	FORCEINLINE ECharacterState GetCharacterState() { return this->CharacterState; }
};
