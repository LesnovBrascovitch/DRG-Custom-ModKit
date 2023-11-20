#include "ProjectileLauncherComponent.h"
#include "Templates/SubclassOf.h"
#include <Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h>
#include "AmmoDrivenWeapon.h"
#include "Math/UnrealMathUtility.h"
#include "DrawDebugHelpers.h"
#include "CollisionQueryParams.h"
#include "FSDPhysicalMaterial.h"
#include "Engine/World.h"
#include "ProjectileBase.h"
#include "Kismet/KismetMathLibrary.h"

void UProjectileLauncherComponent::SetProjectileClass(TSubclassOf<AProjectileBase> NewProjectileClass) {
}

void UProjectileLauncherComponent::Fire(const FVector& Origin, const FVector_NetQuantizeNormal& Direction, bool playFireFX)
{
    AAmmoDrivenWeapon* OwnerWeapon = Cast<AAmmoDrivenWeapon>(GetOwner());

    UKismetSystemLibrary::PrintString(this, "[C++] UProjectileLauncherComponent - Fire", true, true, FColor::Cyan, 3.f);

    if (IsValid(OwnerWeapon)) {
        UWorld* World = GetWorld();

        USkeletalMeshComponent* FPMesh = Cast<USkeletalMeshComponent>(OwnerWeapon->GetDefaultSubobjectByName(TEXT("FPMesh")));

        FCollisionQueryParams CollisionParameters;

        CollisionParameters.bTraceComplex = true;
        CollisionParameters.bReturnPhysicalMaterial = true;

        CollisionParameters.AddIgnoredActor(OwnerWeapon);

        FRotator MuzzleRotation = FPMesh->GetSocketRotation(TEXT("Muzzle"));
        FVector MuzzleForwardVector = MuzzleRotation.Vector();
        //FVector ForwardVector = FMath::VRandCone(MuzzleForwardVector, FMath::DegreesToRadians(MinSpread));

        FVector MuzzleLocation = FPMesh->GetSocketLocation(TEXT("Muzzle"));
        //FVector TargetLocation = MuzzleLocation + (ForwardVector * 30000);
        // Calculate a random spread for each pellet

        //FHitResult Hit;
        if(IsValid(ProjectileClass)){


            FTransform SpawnTransform;
            SpawnTransform.SetLocation(MuzzleLocation);
            
            APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(OwnerWeapon->GetOwner());

            SpawnTransform.SetRotation(MuzzleRotation.Quaternion());

            if (IsValid(PlayerCharacter)) {
                USceneComponent* Camera = Cast<USceneComponent>(PlayerCharacter->GetDefaultSubobjectByName(TEXT("FirstPersonCamera")));
                if (IsValid(Camera)) {
                    FVector OriginLocation = MuzzleLocation;
                    FVector TargetLocation = Camera->GetSocketLocation(TEXT("NONE")) + (Camera->GetForwardVector() * 10000);
                
                    FQuat Quat = UKismetMathLibrary::FindLookAtRotation(OriginLocation, TargetLocation).Quaternion();
                    SpawnTransform.SetRotation(Quat);
                }
                
            }
            else {
                SpawnTransform.SetRotation(MuzzleRotation.Quaternion());
            }

            SpawnTransform.SetScale3D(FVector(1.f));

            FActorSpawnParameters SpawnParameter;
            SpawnParameter.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
            SpawnParameter.bNoFail;
            SpawnParameter.Owner = OwnerWeapon->GetOwner();

            AProjectileBase* SpawnedProjectile = World->SpawnActor<AProjectileBase>(ProjectileClass, SpawnTransform, SpawnParameter);
            OnProjectileSpawned.Broadcast(SpawnedProjectile);
        }
        //GetWorld()->LineTraceSingleByChannel(Hit, MuzzleLocation, TargetLocation, ECC_GameTraceChannel3, CollisionParameters);
        //DrawDebugLine(GetWorld(), MuzzleLocation, TargetLocation, FColor::Red, false, 1.f, 0U, 0.1f);

        /*AActor* HitActor = Hit.GetActor();
        if (HitActor) {
            UKismetSystemLibrary::PrintString(this, "[C++] HitscanComponent - Fire - HitActor -" + HitActor->GetName(), true, true, FColor::Red, 3.f);

            UFSDPhysicalMaterial* FSDPhysicalMat = Cast<UFSDPhysicalMaterial>(Hit.PhysMaterial);
            if (IsValid(FSDPhysicalMat)) {
                FSDPhysicalMat->SpawnImpactParticlesFromHit(GetWorld(), Hit);
            }
        }*/
    }

    else {
        UKismetSystemLibrary::PrintString(this, "[C++] UProjectileLauncherComponent - Fire - Invalid AmmoDrivenWeapon", true, true, FColor::Red, 3.f);
    }
}

UProjectileLauncherComponent::UProjectileLauncherComponent() {
    this->ProjectileClass = NULL;
}

