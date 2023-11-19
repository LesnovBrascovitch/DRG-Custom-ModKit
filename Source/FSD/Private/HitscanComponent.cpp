#include "HitscanComponent.h"
#include <Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h>
#include "AmmoDrivenWeapon.h"
#include "Math/UnrealMathUtility.h"
#include "DrawDebugHelpers.h"
#include "CollisionQueryParams.h"
#include "FSDPhysicalMaterial.h"

void UHitscanComponent::Fire(const FVector& Origin, const FVector_NetQuantizeNormal& Direction, bool playFireFX)
{
    AAmmoDrivenWeapon* OwnerWeapon = Cast<AAmmoDrivenWeapon>(GetOwner());

    UKismetSystemLibrary::PrintString(this, "[C++] HitscanComponent - Fire", true, true, FColor::Cyan, 3.f);

    if (IsValid(OwnerWeapon)) {
        USkeletalMeshComponent* FPMesh = Cast<USkeletalMeshComponent>(OwnerWeapon->GetDefaultSubobjectByName(TEXT("FPMesh")));

        FCollisionQueryParams CollisionParameters;

        CollisionParameters.bTraceComplex = true;
        CollisionParameters.bReturnPhysicalMaterial = true;

        CollisionParameters.AddIgnoredActor(OwnerWeapon);

        FRotator MuzzleRotation = FPMesh->GetSocketRotation(TEXT("Muzzle"));
        FVector MuzzleForwardVector = MuzzleRotation.Vector();
        FVector ForwardVector = FMath::VRandCone(MuzzleForwardVector, FMath::DegreesToRadians(MinSpread));

        FVector MuzzleLocation = FPMesh->GetSocketLocation(TEXT("Muzzle"));
        FVector TargetLocation = MuzzleLocation + (ForwardVector * 30000);
        // Calculate a random spread for each pellet

        FHitResult Hit;
        GetWorld()->LineTraceSingleByChannel(Hit, MuzzleLocation, TargetLocation, ECC_GameTraceChannel3, CollisionParameters);
        DrawDebugLine(GetWorld(), MuzzleLocation, TargetLocation, FColor::Red, false, 1.f, 0U, 0.1f);

        AActor* HitActor = Hit.GetActor();
        if (HitActor) {
            UKismetSystemLibrary::PrintString(this, "[C++] HitscanComponent - Fire - HitActor -" + HitActor->GetName(), true, true, FColor::Red, 3.f);

            UFSDPhysicalMaterial* FSDPhysicalMat = Cast<UFSDPhysicalMaterial>(Hit.PhysMaterial);
            if (IsValid(FSDPhysicalMat)) {
                FSDPhysicalMat->SpawnImpactParticlesFromHit(GetWorld(), Hit);
            }
        }
    }

    else {
        UKismetSystemLibrary::PrintString(this, "[C++] MultiHitscanComponent - Fire - Invalid AmmoDrivenWeapon", true, true, FColor::Red, 3.f);
    }
}

void UHitscanComponent::Server_RegisterRicochetHit_Terrain_Implementation(FVector_NetQuantize Origin, FVector_NetQuantize Location, FVector_NetQuantizeNormal Normal, UFSDPhysicalMaterial* PhysMaterial) {
}

void UHitscanComponent::Server_RegisterRicochetHit_Destructable_Implementation(FVector_NetQuantize Origin, FVector_NetQuantize Location, FVector_NetQuantizeNormal Normal, UPrimitiveComponent* Target, UFSDPhysicalMaterial* PhysMaterial, uint8 BoneIndex) {
}

void UHitscanComponent::Server_RegisterRicochetHit_Implementation(FVector_NetQuantize Origin, FVector_NetQuantize Location, FVector_NetQuantizeNormal Normal, UPrimitiveComponent* Target, UFSDPhysicalMaterial* PhysMaterial) {
}

void UHitscanComponent::Server_RegisterHit_Terrain_Implementation(FVector_NetQuantize Location, FVector_NetQuantizeNormal Normal, UFSDPhysicalMaterial* PhysMaterial) {
}

void UHitscanComponent::Server_RegisterHit_Destructable_Implementation(FVector_NetQuantize Location, FVector_NetQuantizeNormal Normal, UPrimitiveComponent* Target, UFSDPhysicalMaterial* PhysMaterial, uint8 BoneIndex) {
}

void UHitscanComponent::Server_RegisterHit_Implementation(FVector_NetQuantize Location, FVector_NetQuantizeNormal Normal, UPrimitiveComponent* Target, UFSDPhysicalMaterial* PhysMaterial) {
}

void UHitscanComponent::All_ShowRicochetHit_Terrain_Implementation(FVector_NetQuantize Origin, FVector_NetQuantize Location, FVector_NetQuantizeNormal Normal, uint8 MaterialID, UFSDPhysicalMaterial* PhysMaterial) {
}

void UHitscanComponent::All_ShowRicochetHit_Destructable_Implementation(FVector_NetQuantize Origin, FVector_NetQuantize Location, FVector_NetQuantizeNormal Normal, UPrimitiveComponent* Target, UFSDPhysicalMaterial* PhysMaterial, uint8 BoneIndex) {
}

void UHitscanComponent::All_ShowRicochetHit_Implementation(FVector_NetQuantize Origin, FVector_NetQuantize Location, FVector_NetQuantizeNormal Normal, bool SpawnDecal, UFSDPhysicalMaterial* PhysMaterial) {
}

void UHitscanComponent::All_ShowHit_Terrain_Implementation(FVector_NetQuantize Location, FVector_NetQuantizeNormal Normal, uint8 MaterialID, UFSDPhysicalMaterial* PhysMaterial) {
}

void UHitscanComponent::All_ShowHit_Destructable_Implementation(FVector_NetQuantize Location, FVector_NetQuantizeNormal Normal, UPrimitiveComponent* Target, UFSDPhysicalMaterial* PhysMaterial, uint8 BoneIndex) {
}

void UHitscanComponent::All_ShowHit_Implementation(FVector_NetQuantize Location, FVector_NetQuantizeNormal Normal, bool SpawnDecal, UFSDPhysicalMaterial* PhysMaterial) {
}

UHitscanComponent::UHitscanComponent() {
    this->CanHitInstigator = false;
    this->BulletsCanCarve = false;
    this->CarveDiameter = 50.00f;
    this->CarveNoise = 25.00f;
    this->CarveDebrisSize = 0.25f;
    this->GeneralImpactAudioVolume = 1.00f;
    this->ImpactDelay = 0.02f;
    this->OnlyUseImpactEffects = false;
    this->ImpactParticles = NULL;
    this->ImpactSound = NULL;
    this->IgnoreAlwaysPenetrate = false;
}

