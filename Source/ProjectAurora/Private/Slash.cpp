#include "Slash.h"

#include "Sword.h"
#include "Camera/CameraComponent.h"
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
	ASword* OverlappingWeapon = Cast<ASword>(this->GetOverlappingItem());
	if (OverlappingWeapon)
	{
		OverlappingWeapon->Equip(this->GetMesh(), FName("hand_r_socket"));
		this->CharacterState = ECharacterState::ECS_EquippedOneHanded;
	}
}

void ASlash::Attack()
{
	UAnimInstance* AnimInstance = this->GetMesh()->GetAnimInstance();
	if (AnimInstance && this->AttackMontage)
	{
		UE_LOG(LogTemp, Display, TEXT("Animation instantiated"));
		AnimInstance->Montage_Play(this->AttackMontage);
		// int32 Selection = FMath::RandRange(0, 1);
		// FName SelectionName = FName();
		// switch (Selection)
		// {
		// case 0:
		// 	{
		// 		SelectionName = FName("Primary_Attack_C_Montage'");
		// 		break;
		// 	}
		// case 1:
		// 	{
		// 		SelectionName = FName("Primary_Attack_A_Montage");
		// 		break;
		// 	}
		// default: break;
		// }
		// AnimInstance->Montage_JumpToSection(SelectionName, AttackMontage);
	}
	UE_LOG(LogTemp, Warning, TEXT("Attack"));
}
