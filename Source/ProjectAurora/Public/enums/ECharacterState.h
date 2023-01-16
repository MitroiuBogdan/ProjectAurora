#pragma once

UENUM(BlueprintType)
enum class ECharacterState: uint8
{
	ECS_Unequipped UMETA("Unequipped State"),
	ECS_EquippedOneHanded UMETA("Equipped One Handed State"),
	ECS_EquippedTwoHanded UMETA("Equipped Two Handed State")
};
