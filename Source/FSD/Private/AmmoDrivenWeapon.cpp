#include "AmmoDrivenWeapon.h"
#include "AmmoDriveWeaponAggregator.h"
#include "Net/UnrealNetwork.h"
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

bool AAmmoDrivenWeapon::GetFiring() {
    return IsFiring;
}

void AAmmoDrivenWeapon::BeginPlay() {
    Super::BeginPlay();

    this->AmmoCount = this->MaxAmmo;
    this->ClipCount = this->ClipSize;

    WeaponFire = this->FindComponentByClass<UWeaponFireComponent>();

    Aggregator->OnClipAmountChanged.Broadcast(ClipCount);
    Aggregator->OnTotalAmountChanged.Broadcast(AmmoCount);
    Aggregator->OnClipAndTotalChanged.Broadcast(AmmoCount + ClipCount);
}

void AAmmoDrivenWeapon::UpdateHoldToFire() {
}

void AAmmoDrivenWeapon::Server_StopReload_Implementation(float BlendOutTime) {
}

void AAmmoDrivenWeapon::Server_ReloadWeapon_Implementation() {
    if (AmmoCount > 0) {
        UE_LOG(LogTemp, Log, TEXT("Server_ReloadWeapon_Implementation"), *this->GetName());
        int32 AmmoToReload = FMath::Min((ClipSize - ClipCount), AmmoCount);

        ClipCount += AmmoToReload;

        AmmoCount -= AmmoToReload;
        Aggregator->OnClipAmountChanged.Broadcast(ClipCount);
        Aggregator->OnTotalAmountChanged.Broadcast(AmmoCount);
        Aggregator->OnClipAndTotalChanged.Broadcast(AmmoCount + ClipCount);
        Aggregator->OnReloadComplete.Broadcast();
    }
}

void AAmmoDrivenWeapon::Server_PlayBurstFire_Implementation(uint8 shotCount) {
}

void AAmmoDrivenWeapon::Server_Gunsling_Implementation(uint8 Index) {
    UKismetSystemLibrary::PrintString(this, "[C++] AmmoDrivenWeapon - Server_Gunsling", true, true, FColor::Cyan, 2.f);

    int32 random = (GunslingAnimations.Num() - 1);

    UAnimMontage* GunslingMontageFP = GunslingAnimations[FMath::RandRange(0, random)].FP_CharacterMontage;
    UAnimMontage* GunslingMontageItem = GunslingAnimations[FMath::RandRange(0, random)].ItemMontage;

    if (IsValid(GunslingMontageFP)) {
        UInventoryComponent* InvComp = Cast<UInventoryComponent>(Character->GetComponentByClass(UInventoryComponent::StaticClass()));
        if (IsValid(InvComp)) {
            UPlayerFPAnimInstance* FPAnim = Character->GetFPAnimInstance();

            //Play Dwarf's gunsling anim [FPMesh]
            FPAnim->UAnimInstance::Montage_Play(GunslingMontageFP,1.0f,EMontagePlayReturnType::Duration);

            if (IsValid(GunslingMontageItem)) {
                this->FPMesh->GetAnimInstance()->UAnimInstance::Montage_Play(GunslingMontageItem, 1.0f, EMontagePlayReturnType::Duration);
            }
        }
    }
}

void AAmmoDrivenWeapon::ResupplyAmmo(int32 Amount) {
}


void AAmmoDrivenWeapon::OnWeaponFireEnded() {
}


void AAmmoDrivenWeapon::OnWeaponFired(const FVector& Location) {
//Spawn Muzzle Particle and Call Fire from HitScan Component
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

                    UParticleSystem* Particle = Cast<UParticleSystem>(MuzzleParticles);
                    if (IsValid(Particle)) {
                        UGameplayStatics::SpawnEmitterAttached(Particle, FPMesh, TEXT("Muzzle"));
                    }
                    else
                    {
                        UNiagaraSystem* MuzzleNiagaraSystem = Cast<UNiagaraSystem>(MuzzleParticles);
                        if (IsValid(MuzzleNiagaraSystem)) {
                            UNiagaraFunctionLibrary::SpawnSystemAttached(MuzzleNiagaraSystem, FPMesh, TEXT("Muzzle"), FVector(0.f), FRotator(0.f), EAttachLocation::Type::KeepRelativeOffset, true);

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

    if (ClipCount == 0) {
        IsFiring = false;

        if (WeaponEmptySound) {
            UGameplayStatics::SpawnSoundAttached(WeaponEmptySound, this->FPMesh, TEXT("Muzzle"));
        }

        if (IsValid(FireSound)) {
            if (FireSound->GetDuration() == 10000.0f) {
                FireSoundInstance->FadeOut(0.15f, 0.f);
            }
        }
    }



}

void AAmmoDrivenWeapon::OnRicochet(const FVector& Origin, const FVector& Location, const FVector& Normal) {
}

void AAmmoDrivenWeapon::OnRep_IsFiring() {
}

bool AAmmoDrivenWeapon::IsClipFull() const {
    return false;
}

void AAmmoDrivenWeapon::InstantlyReload() {
}


void AAmmoDrivenWeapon::Client_RefillAmmo_Implementation(float percentage) {
}

void AAmmoDrivenWeapon::All_StopReload_Implementation(float BlendOutTime) {
}

void AAmmoDrivenWeapon::All_StartReload_Implementation() {
}

void AAmmoDrivenWeapon::All_PlayBurstFire_Implementation(uint8 shotCount) {
}

void AAmmoDrivenWeapon::All_Gunsling_Implementation(uint8 Index) {
}

void AAmmoDrivenWeapon::RecieveStopUsing_Implementation()
{
    Super::RecieveStopUsing_Implementation();
    IsFiring = false;
    IsUsing = false;

    if (IsValid(Character)) {
        UInventoryComponent* InvComp = Cast<UInventoryComponent>(Character->GetComponentByClass(UInventoryComponent::StaticClass()));
        if (IsValid(InvComp)) {
            UPlayerFPAnimInstance* FPAnim = Character->GetFPAnimInstance();
            if (HasAutomaticFire) {
            //Play Dwarf's FP Animation if valid
                if (IsValid(FP_FireAnimation)) {
                    FPAnim->UAnimInstance::StopAllMontages(0.1f);
                    //FPAnim->UAnimInstance::Montage_Play(FP_FireAnimation);
                }

            //Play WPN's FP Animation if valid
            
                if (IsValid(WPN_Fire)) {
                    this->FPMesh->GetAnimInstance()->UAnimInstance::StopAllMontages(0.1f);
                    //this->FPMesh->GetAnimInstance()->UAnimInstance::Montage_Play(WPN_Fire);
                }
            }
        }
    }
    UKismetSystemLibrary::PrintString(this, "[C++] AmmoDrivenWeapon - RecieveStopUsing", true, true, FColor::Cyan, 2.f);

    if (IsValid(FireSound)) {
        if (FireSound->GetDuration() == 10000.0f) {
            FireSoundInstance->FadeOut(0.15f, 0.f);

        }
    }
}

void AAmmoDrivenWeapon::RecieveStartUsing_Implementation()
{
    UKismetSystemLibrary::PrintString(this, "[C++] AmmoDrivenWeapon - RecieveStartUsing", true, true, FColor::Cyan, 2.f);
    
    IsUsing = true;

    if (AmmoCount == 0 && ClipCount == 0) {
        if (WeaponEmptySound) {
            UGameplayStatics::SpawnSoundAttached(WeaponEmptySound, this->FPMesh, TEXT("Muzzle"));
            
        }
    }

    else if (ClipCount > 0) {
        IsFiring = true;
        OnWeaponFired(FVector(0.f));

        
        if (IsValid(FireSound)) {
            UKismetSystemLibrary::PrintString(this, FString::SanitizeFloat(FireSound->GetDuration()), true, true, FColor::Cyan, 5.f);
            if (FireSound->GetDuration() == 10000.0f) {
                FireSoundInstance->SetFloatParameter(TEXT("RateOfFire"), RateOfFire);
                FireSoundInstance->SetSound(FireSound);
                FireSoundInstance->Play();

            }     
        }
    }
}

void AAmmoDrivenWeapon::RecieveCycledItem_Implementation()
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
                }
            }
        }
    }
}




void AAmmoDrivenWeapon::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    
    DOREPLIFETIME(AAmmoDrivenWeapon, FP_ReloadAnimation);
    DOREPLIFETIME(AAmmoDrivenWeapon, TP_ReloadAnimation);
    DOREPLIFETIME(AAmmoDrivenWeapon, WPN_Reload);
    DOREPLIFETIME(AAmmoDrivenWeapon, ClipCount);
    DOREPLIFETIME(AAmmoDrivenWeapon, IsFiring);
}

int AAmmoDrivenWeapon::GetCurrentClipCount()
{
    return ClipCount;
}

int AAmmoDrivenWeapon::GetMaxClipCount()
{
    return ClipSize;
}

int AAmmoDrivenWeapon::GetCurrentMaxAmmoCount()
{
    return AmmoCount;
}

int AAmmoDrivenWeapon::GetMaxAmmoCount()
{
    return MaxAmmo;
}

void AAmmoDrivenWeapon::StopFireWaitTimer()
{
    GetWorld()->GetTimerManager().ClearTimer(FireWaitHandle);
}

AAmmoDrivenWeapon::AAmmoDrivenWeapon() {
    this->WeaponFire = NULL;
    this->Aggregator = CreateDefaultSubobject<UAmmoDriveWeaponAggregator>(TEXT("Aggregator"));
    this->LoopFireAnimation = false;
    this->LoopFireAnimationBlendoutTime = 0.25f;
    this->FP_FireAnimation = NULL;
    this->TP_FireAnimation = NULL;
    this->FP_ReloadAnimation = NULL;
    this->TP_ReloadAnimation = NULL;
    this->WPN_Fire = NULL;
    this->WPN_FireLastBullet = NULL;
    this->WPN_Reload = NULL;
    this->WPN_Reload_TP = NULL;
    this->MuzzleParticles = NULL;
    this->TPMuzzleParticles = NULL;
    this->UseTriggeredMuzzleParticles = false;
    this->CasingParticles = NULL;
    this->UseTriggeredCasingParticleSystem = false;
    this->MuzzleFlashLight = NULL;
    this->FireSound = NULL;
    this->RicochetSound = NULL;
    this->RicochetParticle = NULL;
    this->FireSoundDelayToTail = -1.00f;
    this->FireSoundTail = NULL;
    this->IsFireSoundTail2D = false;
    this->FireForceFeedbackEffect = NULL;
    this->FireSoundFadeDuration = 0.20f;
    this->ReloadSound = NULL;
    this->BulletsRemainingForNearEmptySound = 0;
    this->PlayEmptySoundsIn3D = false;
    this->NearEmptySound = NULL;
    this->WeaponEmptySound = NULL;
    this->ShoutShotFired = NULL;
    this->ShoutOutOfAmmo = NULL;
    this->ShoutReloading = NULL;
    this->MaxAmmo = 0;
    this->ClipSize = 0;
    this->ShotCost = 1;
    this->RateOfFire = 0.00f;
    this->BurstCount = 0;
    this->BurstCycleTime = 20.00f;
    this->ReloadDuration = 0.00f;
    this->AmmoCount = 0;
    this->ClipCount = 0;
    this->FireInputBufferTime = 0.00f;
    this->AutoReloadDuration = 0.00f;
    this->AutoReloadCompleteCue = NULL;
    this->SupplyStatusWeight = 1.00f;
    this->CycleTimeLeft = 0.00f;
    this->UseCustomReloadDelay = false;
    this->CustomReloadDelay = 0.00f;
    this->ReloadTimeLeft = 0.00f;
    this->AutomaticReload = false;
    this->CanReload = false;
    this->HoldToFirePercentOfFireRatePenalty = -1.00f;
    this->ApplyRecoilAtEndOfBurst = false;
    this->EndOfBurstRecoilMultiplier = 1.00f;
    this->HasAutomaticFire = false;
    this->IsFiring = false;
    this->WeaponState = EAmmoWeaponState::Equipping;
    this->FireSoundInstance = CreateDefaultSubobject<UAudioComponent>(TEXT("SceneComponent"));
    this->FireSoundInstance->SetVolumeMultiplier(1.f);
    this->FireSoundInstance->AttachToComponent(FPMesh, FAttachmentTransformRules::SnapToTargetIncludingScale);
}


