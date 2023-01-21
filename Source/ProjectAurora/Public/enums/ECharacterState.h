#pragma once

UENUM(BlueprintType)
enum class ECharacterState: uint8
{
	ECS_Unequipped UMETA("Unequipped State"),
	ECS_EquippedOneHanded UMETA("Equipped One Handed State"),
	ECS_EquippedTwoHanded UMETA("Equipped Two Handed State")
};


UENUM(BlueprintType)
enum class EActionState: uint8
{
	EAS_Unoccupied UMETA("Unoccupied State"),
	EAS_Attacking UMETA("Attaking State"),
	EAS_EQUIPPING UMETA("Equipping State")
	// EAS_EquippedTwoHanded UMETA("Equipped Two Handed State")
};

UENUM(BlueprintType)
enum class EItemState: uint8
{
	EIS_Equiped UMETA("Equiped State"),
	EEI_Unequiped UMETA("Unequiped State")
};
