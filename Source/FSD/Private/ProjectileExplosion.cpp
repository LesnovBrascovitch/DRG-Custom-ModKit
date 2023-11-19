#include "ProjectileExplosion.h"
#include "ExplosionBaseComponent.h"
#include "ScaledEffect.h"
#include "FSDPhysicalMaterial.h"
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

void UProjectileExplosion::SpawnEffectsFromHit(const FHitResult& Hit) {
    UWorld* World = GetWorld();
    

    AActor* HitActor = Hit.GetActor();
    if (IsValid(HitActor)) {
        if (IsValid(ExplosionEffect.ParticleSystem)) {
            UParticleSystem* ParticleSystem = Cast<UParticleSystem>(ExplosionEffect.ParticleSystem);
            FTransform SpawnTransform;
            FRotator SpawnRotation = Hit.ImpactNormal.Rotation();
            SpawnTransform.SetLocation(Hit.Location);
            SpawnTransform.SetRotation(SpawnRotation.Quaternion());
            SpawnTransform.SetScale3D(FVector{ ExplosionEffect.Scale });

            if (IsValid(ParticleSystem)) {
                UGameplayStatics::SpawnEmitterAtLocation(World, ParticleSystem, SpawnTransform);

            }
        }
    }
    
}

void UProjectileExplosion::SpawnEffects(FVector Location, FVector Normal) {

}

UProjectileExplosion::UProjectileExplosion() {
    this->ExplosionSound = NULL;
    this->ForceFeedbackEffect = NULL;
    this->ForceFeedbackAttanuation = NULL;
}

