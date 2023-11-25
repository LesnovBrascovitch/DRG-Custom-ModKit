#pragma once
#include "CoreMinimal.h"
#include "AmmoDrivenWeapon.h"
#include "DualWieldWeapon.generated.h"

class UAnimMontage;
class UFXSystemAsset;
class UFirstPersonSkeletalMeshComponent;
class USkeletalMeshComponent;

UCLASS(Abstract, Blueprintable)

//DualWieldWeapon is used from WPN_DualPistol, handling dual wielding weapon.
class ADualWieldWeapon : public AAmmoDrivenWeapon {
    GENERATED_BODY()
public:
    virtual void OnSkinChanged_Implementation(USkinEffect* Skin);

    virtual void UpdateSkin();

    void RecieveEquipped();
    virtual void RecieveEquipped_Implementation() override;

    void RecieveUnequipped();
    virtual void RecieveUnequipped_Implementation() override;
protected:
    virtual void OnWeaponFired(const FVector& Location);


    virtual void RecieveCycledItem_Implementation() override;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UFirstPersonSkeletalMeshComponent* FPMeshLeft;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    USkeletalMeshComponent* TPMeshLeft;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UAnimMontage* WPN_Left_Reload;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UAnimMontage* WPN_Left_TP_Reload;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UFXSystemAsset* CasingParticlesLeft;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName MuzzleLeft;
    
public:
    ADualWieldWeapon();
};

