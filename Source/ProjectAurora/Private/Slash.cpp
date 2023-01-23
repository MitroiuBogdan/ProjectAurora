#include "Slash.h"

#include "Sword.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"


ASlash::ASlash()
{
	PrimaryActorTick.bCanEverTick = true;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("ArmComponent"));
	CameraBoom->SetupAttachment(GetRootComponent());

	ViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	ViewCamera->SetupAttachment(CameraBoom);

	ViewCamera->bUsePawnControlRotation = true;
}

void ASlash::BeginPlay()
{
	Super::BeginPlay();
}

void ASlash::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASlash::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("M_F"), this, &ASlash::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("M_R"), this, &ASlash::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("Yaw"), this, &ASlash::ViewYaw);
	PlayerInputComponent->BindAxis(TEXT("Pitch"), this, &ASlash::ViewPitch);

	PlayerInputComponent->BindAction(TEXT("JUMP"), IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Equip"), IE_Pressed, this, &ASlash::FKeyPressed);
	PlayerInputComponent->BindAction(TEXT("Attack"), IE_Pressed, this, &ASlash::Attack);
}

void ASlash::MoveForward(float Value)
{
	if (ActionState == EActionState::EAS_Attacking || ActionState == EActionState::EAS_EQUIPPING) { return; }
	if (Controller && Value != 0)
	{
		const FRotator ControlRotation = GetControlRotation();
		const FRotator YawRotation(0.f, ControlRotation.Yaw, 0.f);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
	// UE_LOG(LogTemp, Warning, TEXT("M_F - %f"), Value);
}

void ASlash::MoveRight(float Value)
{
	if (ActionState == EActionState::EAS_Attacking || ActionState == EActionState::EAS_EQUIPPING) { return; }
	if (Controller && Value != 0)
	{
		{
			const FRotator ControlRotation = GetControlRotation();
			const FRotator YawRotation(0.f, ControlRotation.Yaw, 0.f);
			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
			AddMovementInput(Direction, Value);
		}
	}
	// UE_LOG(LogTemp, Warning, TEXT("M_F - %f"), Value);
}


void ASlash::ViewYaw(float Value)
{
	AddControllerYawInput(Value);
}

void ASlash::ViewPitch(float Value)
{
	AddControllerPitchInput(Value);
}

void ASlash::FKeyPressed()
{
	UE_LOG(LogTemp, Warning, TEXT("FKeyPressed"));
	ASword* OverlappingWeapon = Cast<ASword>(this->GetOverlappingItem());
	if (OverlappingWeapon && CharacterState == ECharacterState::ECS_Unequipped && Sword == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("FKeyPressed - OverlappingWeapon"));
		OverlappingWeapon->Equip(this->GetMesh(), FName("hand_r_socket"));
		this->Sword = OverlappingWeapon;
		this->Sword->GetBoxCollision()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		this->CharacterState = ECharacterState::ECS_EquippedOneHanded;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("FKeyPressed - Weapon present"));
		if (CanDisarm())
		{
			UE_LOG(LogTemp, Warning, TEXT("Unequip"));
			PlayEquipMontage(FName("UNEQUIP"));
			CharacterState = ECharacterState::ECS_Unequipped;
			ActionState = EActionState::EAS_EQUIPPING;
		}
		else if (CanArm() && Sword)
		{
			UE_LOG(LogTemp, Warning, TEXT("Equip"));
			PlayEquipMontage(FName("EQUIP"));
			CharacterState = ECharacterState::ECS_EquippedOneHanded;
			ActionState = EActionState::EAS_EQUIPPING;
		}
	}
}


void ASlash::Attack()
{
	UE_LOG(LogTemp, Warning, TEXT("Attack"))
	if (CanAttack())
	{
		PlayAttackMontage();
		ActionState = EActionState::EAS_Attacking;
	}
}

void ASlash::PlayAttackMontage()
{
	UAnimInstance* AnimInstance = this->GetMesh()->GetAnimInstance();
	if (AnimInstance && this->AttackMontage)
	{
		UE_LOG(LogTemp, Warning, TEXT("Attack montage"));
		AnimInstance->Montage_Play(this->AttackMontage);
		int32 Selection = FMath::RandRange(0, 2);
		FName SelectionName = FName();
		switch (Selection)
		{
		case 0:
			{
				SelectionName = FName("AT_A");
				break;
			}
		case 1:
			{
				SelectionName = FName("AT_B");
				break;
			}
		case 2:
			{
				SelectionName = FName("AT_C");
				break;
			}
		default: break;
		}
		AnimInstance->Montage_JumpToSection(SelectionName, AttackMontage);
	};
}

void ASlash::PlayEquipMontage(FName SectionName)
{
	UAnimInstance* AnimInstance = this->GetMesh()->GetAnimInstance();
	if (AnimInstance && this->EquipMontage)
	{
		AnimInstance->Montage_Play(this->EquipMontage);
		AnimInstance->Montage_JumpToSection(SectionName, EquipMontage);
	};
}

void ASlash::AttackEnd()
{
	ActionState = EActionState::EAS_Unoccupied;
}

void ASlash::EquipEnd()
{
	ActionState = EActionState::EAS_Unoccupied;
}


void ASlash::Arm()
{
	if (Sword)
	{
		Sword->AttachMeshToSocket(this->GetMesh(), FName("hand_r_socket"));
		ActionState = EActionState::EAS_EQUIPPING;
	}
}

void ASlash::Disarm()
{
	if (Sword)
	{
		Sword->AttachMeshToSocket(this->GetMesh(), FName("SPINE_SOCKET"));
		ActionState = EActionState::EAS_EQUIPPING;
	}
}

void ASlash::SetWeaponCollisionEnabled(ECollisionEnabled::Type CollisionEnabled)
{
	if (Sword && Sword->GetBoxCollision())
	{
		Sword->GetBoxCollision()->SetCollisionEnabled(CollisionEnabled);
		Sword->ActorsToIgnore.Empty();
	}
}

void ASlash::SetWeaponCollisionDisabled(ECollisionEnabled::Type CollisionEnabled)
{
	if (Sword && Sword->GetBoxCollision())
	{
		Sword->GetBoxCollision()->SetCollisionEnabled(CollisionEnabled);
	}
}

bool ASlash::CanAttack()
{
	return ActionState == EActionState::EAS_Unoccupied && CharacterState != ECharacterState::ECS_Unequipped;
}

bool ASlash::CanDisarm()
{
	return this->GetCharacterState() != ECharacterState::ECS_Unequipped
		&& this->ActionState == EActionState::EAS_Unoccupied;
}

bool ASlash::CanArm()
{
	return this->GetCharacterState() == ECharacterState::ECS_Unequipped
		&& this->ActionState == EActionState::EAS_Unoccupied;
}
