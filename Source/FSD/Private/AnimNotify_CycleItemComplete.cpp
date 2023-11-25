#include "AnimNotify_CycleItemComplete.h"
#include "AmmoDrivenWeapon.h"
#include "PlayerCharacter.h"
#include "InventoryComponent.h"

UAnimNotify_CycleItemComplete::UAnimNotify_CycleItemComplete() {
}

void UAnimNotify_CycleItemComplete::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	AAmmoDrivenWeapon* Owner = Cast<AAmmoDrivenWeapon>(MeshComp->GetOwner());

	if (IsValid(Owner)) {
		Owner->Server_ReloadWeapon_Implementation();
		UE_LOG(LogTemp, Log, TEXT("CycleItemComplete Notify - Server_ReloadWeapon_Implementation call to %s"), *Owner->GetName());
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("CycleItemComplete Notify - Failed to call Server_ReloadWeapon_Implementation"));

		APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(MeshComp->GetOwner());
		if (IsValid(PlayerCharacter)) {
			UInventoryComponent* InvComp = PlayerCharacter->FindComponentByClass<UInventoryComponent>();
			if (IsValid(InvComp)) {
				Owner = Cast<AAmmoDrivenWeapon>(InvComp->GetEquippedItem());
				if (IsValid(Owner)) {
					Owner->Server_ReloadWeapon_Implementation();
					UE_LOG(LogTemp, Log, TEXT("CycleItemComplete Notify - Server_ReloadWeapon_Implementation call to %s via player character"), *Owner->GetName());
				}
			}
		}
	}
}
