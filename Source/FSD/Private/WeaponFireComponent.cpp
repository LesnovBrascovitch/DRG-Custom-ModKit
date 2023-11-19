#include "WeaponFireComponent.h"

#include <FSD/Public/AmmoDrivenWeapon.h>
#include <Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h>

void UWeaponFireComponent::StopFire() {
}

void UWeaponFireComponent::Server_SetShotPower_Implementation(float shotPower) {
}

void UWeaponFireComponent::Fire(const FVector& Origin, const FVector_NetQuantizeNormal& Direction, bool playFireFX) {
	UKismetSystemLibrary::PrintString(this, "[C++] WeaponFireComponent - Fire", true, true, FColor::Cyan, 1.f);
	
	if (playFireFX) {
		AAmmoDrivenWeapon* OwnerWeapon = Cast<AAmmoDrivenWeapon>(GetOwner());
		if (IsValid(OwnerWeapon)) {

		}
	}
}

UWeaponFireComponent::UWeaponFireComponent() {
}
