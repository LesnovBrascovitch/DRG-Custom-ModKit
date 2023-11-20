#include "AnimNotifyState_WeaponReload.h"
#include "AmmoDrivenWeapon.h"

void UAnimNotifyState_WeaponReload::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	AAmmoDrivenWeapon* AmmoDrivenWeapon = Cast<AAmmoDrivenWeapon>(MeshComp->GetOwner());
	if (IsValid(AmmoDrivenWeapon)) {
		AmmoDrivenWeapon->Receive_ReloadBegin();
	}
}
void UAnimNotifyState_WeaponReload::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	AAmmoDrivenWeapon* AmmoDrivenWeapon = Cast<AAmmoDrivenWeapon>(MeshComp->GetOwner());
	if (IsValid(AmmoDrivenWeapon)) {
		AmmoDrivenWeapon->Receive_ReloadEnd();
	}
}

UAnimNotifyState_WeaponReload::UAnimNotifyState_WeaponReload() {
}

