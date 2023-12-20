#include "DamageComponent.h"
#include "Templates/SubclassOf.h"
#include "HealthComponentBase.h"
#include "SimpleArmorDamageComponent.h"
#include "Kismet/KismetSystemLibrary.h"

void UDamageComponent::PreTestDamageConditions() {
}

UDamageComponent* UDamageComponent::GetDamageComponentCDO(TSubclassOf<UDamageComponent> DamageComponent) {
    return NULL;
}

float UDamageComponent::GetDamage() const {
    return 0.0f;
}

void UDamageComponent::DamageTargetFromHit(const FHitResult& HitResult) const {
    AActor* HitActor = HitResult.GetActor();
    if (IsValid(HitActor)) {
        UHealthComponentBase* HealthComp = HitActor->FindComponentByClass<UHealthComponentBase>();
        USimpleArmorDamageComponent* SimpleArmorComp = HitActor->FindComponentByClass<USimpleArmorDamageComponent>();

        bool CanBeDamaged = true;

        if (IsValid(SimpleArmorComp)) {
            UE_LOG(LogTemp, Log, TEXT("SimpleArmorComp detected"));
            if (SimpleArmorComp->CanBeDestroyed(HitResult.BoneName)) {
                USkeletalMeshComponent* EnemyMesh = Cast<USkeletalMeshComponent>(HitResult.Component);
                if (IsValid(EnemyMesh)) {
                    
                    EnemyMesh->HideBoneByName(HitResult.BoneName, EPhysBodyOp::PBO_None);
                    CanBeDamaged = false;
                    UE_LOG(LogTemp, Log, TEXT("Armor got destroyed"));

                }
                else {
                    UE_LOG(LogTemp, Error, TEXT("EnemyMesh Invalid"));
                }
            }
            else {
                UE_LOG(LogTemp, Log, TEXT("SimpleArmorComp cannot be destroyed"));
            }
        }

        if (IsValid(HealthComp)) {
            if (CanBeDamaged) {
                HealthComp->TakeDamageSimple(Damage, NULL, DamageClass);
            }
        }
    }

    

    if (UseAreaOfEffect == true) {
        TArray<AActor*> OutActors;

        TArray<AActor*> ActorToIgnore;

        TArray<TEnumAsByte<EObjectTypeQuery>> traceObjectTypes;
        traceObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));
        traceObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldDynamic));

        
        UKismetSystemLibrary::SphereOverlapActors(GetWorld(), HitResult.Location, DamageRadius, traceObjectTypes, AActor::StaticClass(), ActorToIgnore, OutActors);
        
        for (AActor* HitActor: OutActors) {
            if (IsValid(HitActor)) {
                UHealthComponentBase* HealthComp = HitActor->FindComponentByClass<UHealthComponentBase>();
                if (IsValid(HealthComp)) {
                    HealthComp->TakeDamageSimple(RadialDamage, NULL, RadialDamageClass);
                    UE_LOG(LogTemp, Log, TEXT("%s got damaged with %f"), *HitActor->GetName(), RadialDamage);
                }
            }
        }

        
    }
}

void UDamageComponent::DamageTarget_CDO(const FVector& Location, AActor* Owner, AActor* hitActor) {
}

void UDamageComponent::DamageTarget(AActor* Target, const FVector& Location, UPrimitiveComponent* HitComponent, UFSDPhysicalMaterial* PhysMat, int32 BoneIndex) const {
}

void UDamageComponent::DamageArmor_Server(AActor* Target, UPrimitiveComponent* collider, int32 BoneIndex, const FVector& impactLocation) const {
}

void UDamageComponent::DamageArmor_All(AActor* Target, UPrimitiveComponent* collider, int32 BoneIndex) const {
}

bool UDamageComponent::ArmorSupportsLocalOnlyCall(AActor* Target) const {
    return false;
}

UDamageComponent::UDamageComponent() {
    this->DamageComponentType = EDamageComponentType::Primary;
    this->DamageImpulse = NULL;
    this->Damage = 5.00f;
    this->armorDamageMultiplier = 1.00f;
    this->ArmorPenetration = 0.00f;
    this->ShattersArmor = false;
    this->DamageClass = NULL;
    this->ArmorDamageType = EArmorDamageType::Normal;
    this->WeakpointDamageMultiplier = 1.00f;
    this->FrozenDamageBonusScale = 1.00f;
    this->FriendlyFireModifier = 1.00f;
    this->SelfFriendlyFireMultiplier = 1.00f;
    this->StaggerOnlyOnWeakpointHit = false;
    this->StaggerChance = 0.00f;
    this->StaggerDuration = 1.50f;
    this->FearFactor = 0.00f;
    this->UseAreaOfEffect = false;
    this->RadialDamage = 5.00f;
    this->NoFriendlyFireFromRadial = false;
    this->RadialDamageClass = NULL;
    this->MinDamagePct = 0.25f;
    this->DamageRadius = 100.00f;
    this->MaxDamageRadius = 50.00f;
}

