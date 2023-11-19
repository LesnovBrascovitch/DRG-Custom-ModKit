#include "MultiHitscanComponent.h"
#include <Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h>
#include "AmmoDrivenWeapon.h"
#include "Math/UnrealMathUtility.h"
#include "DrawDebugHelpers.h"
#include "CollisionQueryParams.h"
#include "FSDPhysicalMaterial.h"
#include "HealthComponentBase.h"

void UMultiHitscanComponent::Server_RegisterHit_Implementation(const FMultiHitScanHits& hitResults) {
}

void UMultiHitscanComponent::All_ShowHit_Implementation(const FMultiHitScanHits& hitResults) {
}

UMultiHitscanComponent::UMultiHitscanComponent() {
    this->BulletsPerShot = 0;
    this->GeneralImpactAudioVolume = 1.00f;
    this->CountMultiHits = false;
}

void UMultiHitscanComponent::Fire(const FVector& Origin, const FVector_NetQuantizeNormal& Direction, bool playFireFX)
{
    AAmmoDrivenWeapon* OwnerWeapon = Cast<AAmmoDrivenWeapon>(GetOwner());

    UKismetSystemLibrary::PrintString(this, "[C++] MultiHitscanComponent - Fire", true, true, FColor::Cyan, 3.f);

    if (IsValid(OwnerWeapon)) {
        USkeletalMeshComponent* FPMesh = Cast<USkeletalMeshComponent>(OwnerWeapon->GetDefaultSubobjectByName(TEXT("FPMesh")));

        FCollisionQueryParams CollisionParameters;

        CollisionParameters.bTraceComplex = true;
        CollisionParameters.bReturnPhysicalMaterial = true;

        CollisionParameters.AddIgnoredActor(OwnerWeapon);
        APlayerCharacter* Character = Cast<APlayerCharacter>(OwnerWeapon->GetOwner());
        if (IsValid(Character)) {
            CollisionParameters.AddIgnoredActor(Character);
        }
        for (int32 i = 0; i < BulletsPerShot; ++i)
        {
            FRotator MuzzleRotation = FPMesh->GetSocketRotation(TEXT("Muzzle"));
            FVector MuzzleForwardVector = MuzzleRotation.Vector();
            FVector ForwardVector = FMath::VRandCone(MuzzleForwardVector , FMath::DegreesToRadians(MinSpread));

            FVector MuzzleLocation = FPMesh->GetSocketLocation(TEXT("Muzzle"));
            FVector TargetLocation = MuzzleLocation + (ForwardVector * 30000);
            // Calculate a random spread for each pellet

            
            FHitResult Hit;
            GetWorld()->LineTraceSingleByChannel(Hit, MuzzleLocation, TargetLocation, ECC_GameTraceChannel3, CollisionParameters);
            DrawDebugLine(GetWorld(), MuzzleLocation, TargetLocation, FColor::Red, false, 1.f, 0U, 0.1f);



            AActor* HitActor = Hit.GetActor();
            if (HitActor) {
                UKismetSystemLibrary::PrintString(this, "[C++] MultiHitscanComponent - Fire - HitActor -" + HitActor->GetName(), true, true, FColor::Red, 3.f);

                UFSDPhysicalMaterial* FSDPhysicalMat = Cast<UFSDPhysicalMaterial>(Hit.PhysMaterial);
                if (IsValid(FSDPhysicalMat)) {
                    FSDPhysicalMat->SpawnImpactParticlesFromHit(GetWorld(), Hit);
                }

                UHealthComponentBase* HealthComp = HitActor->FindComponentByClass<UHealthComponentBase>();
                if (IsValid(HealthComp)) {
                    HealthComp->TakeDamageSimple(Damage, NULL, DamageClass);
                }
            }

        }
    }

    else {
        UKismetSystemLibrary::PrintString(this, "[C++] MultiHitscanComponent - Fire - Invalid AmmoDrivenWeapon", true, true, FColor::Red, 3.f);
    }

}

