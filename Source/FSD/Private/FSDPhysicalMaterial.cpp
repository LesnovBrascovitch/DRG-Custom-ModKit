#include "FSDPhysicalMaterial.h"
#include <Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h>
#include "FXSystem.h"
#include "Engine/EngineTypes.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include "Math/Rotator.h"
#include "Math/Quat.h"
#include "Sound/SoundCue.h"

UFXSystemComponent* UFSDPhysicalMaterial::SpawnImpactParticlesFromHit(UObject* WorldContextObject, const FHitResult& HitResult) {
    UKismetSystemLibrary::PrintString(WorldContextObject, "[C++] PhysicalMaterial - SpawnImpactParticlesFromHit", true, true, FColor::Cyan, 3.f);
    
    UWorld* World = WorldContextObject->GetWorld();

    AActor* HitActor = HitResult.GetActor();
    if (IsValid(HitActor)) {
        UFSDPhysicalMaterial* FSDPhysicMat = Cast<UFSDPhysicalMaterial>(HitResult.PhysMaterial);

        if (IsValid(FSDPhysicMat)) {
            UFXSystemAsset* SpawnParticle = FSDPhysicMat->ImpactParticles;
        
            //Spawn Impact Particle
            if (IsValid(SpawnParticle)) {
                UParticleSystem* ParticleSystem = Cast<UParticleSystem>(SpawnParticle);
                FTransform SpawnTransform;
                FRotator SpawnRotation = HitResult.ImpactNormal.Rotation();
                SpawnTransform.SetLocation(HitResult.Location);
                SpawnTransform.SetRotation(SpawnRotation.Quaternion());
                SpawnTransform.SetScale3D(FVector{ 1.f });

                UGameplayStatics::SpawnEmitterAtLocation(WorldContextObject->GetWorld(), ParticleSystem, SpawnTransform);
            }

            USoundCue* Sound = FSDPhysicMat->ImpactSound;

            if (IsValid(FSDPhysicMat->ImpactSound)) {
                UGameplayStatics::PlaySoundAtLocation(World, Sound, HitResult.Location);
            }
        }

    }
    return NULL;
}

UFXSystemComponent* UFSDPhysicalMaterial::SpawnImpactParticles(UObject* WorldContextObject, FVector Location, FVector Normal) const {
    return NULL;
}

UFSDPhysicalMaterial* UFSDPhysicalMaterial::GetPhysicalMaterialFromPrimitive(UPrimitiveComponent* Component) {
    return NULL;
}

UFSDPhysicalMaterial::UFSDPhysicalMaterial() {
    this->BreakingDecelerationScale = 1.00f;
    this->BreakingFrictionScale = 1.00f;
    this->MaxAccelerationScale = 1.00f;
    this->RepulsePlayer = false;
    this->RepulsePlayerRandomDegreeOffset = 0.00f;
    this->RepulsePlayerSound = NULL;
    this->RepulsePlayerParticle = NULL;
    this->ImpactParticles = NULL;
    this->ImpactMaterialOverride = NULL;
    this->ImpactSound = NULL;
    this->MeleeImpactSound = NULL;
    this->UseImpactDecalOverrides = false;
    this->ImpactDecals.AddDefaulted(3);
    this->FirstPersonDamageIndicatorSound = NULL;
    this->IsWeakPoint = false;
    this->AllowFrozenBonus = true;
    this->IsSubhealthCollider = false;
    this->DamageMultiplier = 1.00f;
    this->FootstepParticle = NULL;
    this->FootstepMaterialOverride = NULL;
    this->FootstepSound = NULL;
    this->ExtraFallVelocity = 0.00f;
    this->FallImpactEffect = NULL;
    this->FallImpactSound = NULL;
    this->alwaysPenetrate = false;
    this->ReactiveTerrain = NULL;
}

