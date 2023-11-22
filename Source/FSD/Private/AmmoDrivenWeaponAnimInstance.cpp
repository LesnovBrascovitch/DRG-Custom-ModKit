#include "AmmoDrivenWeaponAnimInstance.h"
#include "AmmoDrivenWeapon.h"
#include "Math/UnrealMathUtility.h"
#include "Kismet/KismetMathLibrary.h"

void UAmmoDrivenWeaponAnimInstance::NativeUpdateAnimation(float DeltaSeconds) {
    Super::NativeUpdateAnimation(DeltaSeconds);

    AAmmoDrivenWeapon* AmmoDrivenWeapon = Cast<AAmmoDrivenWeapon>(this->GetOwningActor());

    if (AmmoDrivenWeapon) {
        Weapon = AmmoDrivenWeapon;
        IsFiring = AmmoDrivenWeapon->GetFiring();
        ClipFullPercentage = UKismetMathLibrary::SafeDivide(float(AmmoDrivenWeapon->GetCurrentClipCount()), float(AmmoDrivenWeapon->GetMaxClipCount()));
    }
}

bool UAmmoDrivenWeaponAnimInstance::IsFull() const {
    return false;
}

bool UAmmoDrivenWeaponAnimInstance::isEmpty() const {
    return false;
}

UAmmoDrivenWeaponAnimInstance::UAmmoDrivenWeaponAnimInstance() {
    this->Weapon = NULL;
    this->IsFiring = false;
    this->ClipFullPercentage = 0.00f;
    this->overHeated = false;
    this->Temperature = 0.00f;
}

