#include "DualWieldWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "FirstPersonSkeletalMeshComponent.h"
#include "AnimatedItem.h"
#include "Item.h"
#include "Animation/AnimInstance.h"
#include "Kismet/GameplayStatics.h"
#include <Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h>
#include "Components/AudioComponent.h"
#include "Sound/SoundCue.h"
#include "ItemAnimationItem.h"
#include "Kismet/KismetArrayLibrary.h"
#include "Animation/AnimMontage.h"
#include "HitDelegateDelegate.h"
#include "HitscanBaseComponent.h"
#include "MultiHitScanHits.h"
#include "MultiHitscanComponent.h"
#include "FXSystem.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "PlayerFPAnimInstance.h"
#include "ItemCharacterAnimationSet.h"
#include "Skinnable.h"
#include "SkinEffect.h"
#include "SkeletalMeshSkinEffect.h"
#include "AmmoDriveWeaponAggregator.h"

void ADualWieldWeapon::OnWeaponFired(const FVector& Location) {

    if (ClipCount > 0 && IsFiring) {
        if (GetWorldTimerManager().IsTimerActive(FireWaitHandle) == false) {
            if (IsValid(Character)) {
                UInventoryComponent* InvComp = Cast<UInventoryComponent>(Character->GetComponentByClass(UInventoryComponent::StaticClass()));
                if (IsValid(InvComp)) {
                    IsFiring = true;
                    UPlayerFPAnimInstance* FPAnim = Character->GetFPAnimInstance();

                    //Play Dwarf's FP Animation if valid
                    if (IsValid(FP_FireAnimation)) {
                        FPAnim->UAnimInstance::Montage_Play(FP_FireAnimation);
                    }

                    //Play WPN's FP Animation if valid
                    if (IsValid(WPN_Fire)) {
                        this->FPMesh->GetAnimInstance()->UAnimInstance::Montage_Play(WPN_Fire);
                        this->FPMeshLeft->GetAnimInstance()->UAnimInstance::Montage_Play(WPN_Fire);
                    }

                    //Play Fire Sounds
                    if (FireSound) {
                        if (HasAutomaticFire) {
                            //Fullauto Sound
                        }
                        else {
                            //Semiauto Sound
                            IsFiring = false;
                            UGameplayStatics::SpawnSoundAttached(FireSound, this->FPMesh, TEXT("Muzzle"));
                        }
                    }

                    //Play Muzzle Particle Effect
                    FTransform MuzzleTransform = FPMesh->GetSocketTransform(TEXT("Muzzle"));
                    FTransform MuzzleTransformLeft = FPMeshLeft->GetSocketTransform(TEXT("Muzzle"));

                    UParticleSystem* Particle = Cast<UParticleSystem>(MuzzleParticles);
                    if (IsValid(Particle)) {
                        UGameplayStatics::SpawnEmitterAttached(Particle, FPMesh, TEXT("Muzzle"));
                        UGameplayStatics::SpawnEmitterAttached(Particle, FPMeshLeft, TEXT("Muzzle"));
                    }
                    else
                    {
                        UNiagaraSystem* MuzzleNiagaraSystem = Cast<UNiagaraSystem>(MuzzleParticles);
                        if (IsValid(MuzzleNiagaraSystem)) {
                            UNiagaraFunctionLibrary::SpawnSystemAttached(MuzzleNiagaraSystem, FPMesh, TEXT("Muzzle"), FVector(0.f), FRotator(0.f), EAttachLocation::Type::KeepRelativeOffset, true);
                            UNiagaraFunctionLibrary::SpawnSystemAttached(MuzzleNiagaraSystem, FPMeshLeft, TEXT("Muzzle"), FVector(0.f), FRotator(0.f), EAttachLocation::Type::KeepRelativeOffset, true);
                        }
                    }

                    //Fire by hitscan
                    if (IsValid(WeaponFire)) {
                        FVector_NetQuantize NetQuantize = { 0,0,0 };
                        WeaponFire->Fire(FVector(0.f), NetQuantize, false);

                    }

                    auto FirePerSecondTimer = UKismetMathLibrary::SafeDivide(1, RateOfFire);
                    GetWorld()->GetTimerManager().SetTimer(FireWaitHandle, this, &AAmmoDrivenWeapon::StopFireWaitTimer, FirePerSecondTimer - 0.1f, false);

                    //Consume Clip
                    ClipCount = FMath::Clamp((ClipCount - ShotCost), 0, 99999);
                    OnClipCountChanged.Broadcast(ClipCount);
                    Aggregator->OnClipAmountChanged.Broadcast(ClipCount);

                    //Automatic Fire
                    if (HasAutomaticFire) {
                        auto FirePerSecond = UKismetMathLibrary::SafeDivide(1, RateOfFire);

                        this->TimerDelegate.BindUFunction(this, FName("OnWeaponFired"), FVector{ 0,0,0 });
                        GetWorld()->GetTimerManager().SetTimer(handle, TimerDelegate, FirePerSecond, false);
                    }
                }
            }
        }
    }
}

void ADualWieldWeapon::RecieveUnequipped_Implementation()
{
    Super::RecieveUnequipped_Implementation();

    UKismetSystemLibrary::PrintString(this, "[C++] ADualWieldWeapon - RecieveUnequipped", true, true, FColor::Cyan, 2.f);
    FPMeshLeft->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
}

void ADualWieldWeapon::OnSkinChanged_Implementation(USkinEffect* Skin) {
    Super::OnSkinChanged_Implementation(Skin);

    if (IsValid(Skin)) {
        USkeletalMeshSkinEffect* SkeletalSkinEffect = Cast<USkeletalMeshSkinEffect>(Skin);
        if (IsValid(SkeletalSkinEffect)) {
            USkeletalMesh* LoadedSkin = SkeletalSkinEffect->LoadMesh();
            if (IsValid(LoadedSkin)) {
                
                FPMeshLeft->SetSkeletalMesh(LoadedSkin);
            }
        }
    }

}

void ADualWieldWeapon::UpdateSkin() {

}
void ADualWieldWeapon::RecieveEquipped_Implementation()
{
    UKismetSystemLibrary::PrintString(this, "[C++] ADualWieldWeapon - RecieveEquipped", true, true, FColor::Cyan, 2.f);
    if (this->Character) {
        UPlayerFPAnimInstance* FPAnim = Character->GetFPAnimInstance();
        //FPAnim->UAnimInstance::Montage_Play();
        FPAnim->UAnimInstance::Montage_Play(FP_EquipAnimation);

        USkeletalMeshComponent* FPMeshDwarf = Cast<USkeletalMeshComponent>(Character->GetDefaultSubobjectByName(TEXT("FPMesh")));

        if (IsValid(FPMeshDwarf)) {
            this->FPMesh->AttachToComponent(FPMeshDwarf, FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("Dwarf_HandR_Attach"));
            this->FPMeshLeft->AttachToComponent(FPMeshDwarf, FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("Dwarf_HandL_Attach"));
        }
    }
}

void ADualWieldWeapon::RecieveCycledItem_Implementation()
{
    if ((AmmoCount == 0 && ClipCount == 0) || ClipCount == ClipSize)
    {
        Server_Gunsling_Implementation(0);
    }
    else
    {
        if (IsValid(FP_ReloadAnimation) && IsValid(Character)) {
            UInventoryComponent* InvComp = Cast<UInventoryComponent>(Character->GetComponentByClass(UInventoryComponent::StaticClass()));
            if (IsValid(InvComp)) {
                UPlayerFPAnimInstance* FPAnim = Character->GetFPAnimInstance();
                //FPAnim->UAnimInstance::Montage_Play();

                Aggregator->OnReloadStarted.Broadcast();

                FPAnim->UAnimInstance::Montage_Play(FP_ReloadAnimation);

                if (IsValid(WPN_Reload)) {
                    this->FPMesh->GetAnimInstance()->UAnimInstance::Montage_Play(WPN_Reload);
                    this->FPMeshLeft->GetAnimInstance()->UAnimInstance::Montage_Play(WPN_Reload);
                }
            }
        }
    }
}

ADualWieldWeapon::ADualWieldWeapon() {
    this->FPMeshLeft = CreateDefaultSubobject<UFirstPersonSkeletalMeshComponent>(TEXT("FPMeshLeft"));
    this->TPMeshLeft = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("TPMeshLeft"));
    this->WPN_Left_Reload = NULL;
    this->WPN_Left_TP_Reload = NULL;
    this->CasingParticlesLeft = NULL;
}

