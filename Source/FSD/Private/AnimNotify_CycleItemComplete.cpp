#include "AnimNotify_CycleItemComplete.h"
#include "AmmoDrivenWeapon.h"

UAnimNotify_CycleItemComplete::UAnimNotify_CycleItemComplete() {
}

void UAnimNotify_CycleItemComplete::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	AAmmoDrivenWeapon* Owner = Cast<AAmmoDrivenWeapon>(MeshComp->GetOwner());

	if (IsValid(Owner)) {
		Owner->Server_ReloadWeapon_Implementation();
	}
}
