#include "AnimNotifyState_SpawnMesh.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include <Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h>

//Add a static mesh component.
void UAnimNotifyState_SpawnMesh::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
    UKismetSystemLibrary::PrintString(MeshComp->GetWorld(), "[C++] SpawnMesh Notify State - NotifyBegin", true, true, FColor::Cyan, 2.f);

    AActor* Owner = MeshComp->GetOwner();
    UStaticMeshComponent* AttachedMeshComp = Cast<UStaticMeshComponent>(Owner->AActor::AddComponentByClass(UStaticMeshComponent::StaticClass(), true, FTransform(FRotator(0.f), FVector(0.f), FVector(0.f)), true));

    if (IsValid(AttachedMeshComp)) {
        AttachedMeshComp->SetStaticMesh(Mesh);
        AttachedMeshComp->AttachToComponent(MeshComp, FAttachmentTransformRules::SnapToTargetIncludingScale, SocketName);
        AttachedMeshComp->RegisterComponent();
    }
}

//Destroy added components by finding through attached components.
void UAnimNotifyState_SpawnMesh::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    TArray<USceneComponent*> AttachedComps = MeshComp->GetAttachChildren();
    for(USceneComponent* AttachedComp: AttachedComps) {
        UStaticMeshComponent* StaticMesh = Cast<UStaticMeshComponent>(AttachedComp);
        if (IsValid(StaticMesh)) {
            if (StaticMesh->GetStaticMesh() == Mesh) {
                AttachedComp->DestroyComponent();
            }
        }

    }
}

UAnimNotifyState_SpawnMesh::UAnimNotifyState_SpawnMesh() {
    this->Mesh = NULL;
    this->HasOverrideMaterial = false;
    this->OverrideMaterial = NULL;
    this->OverrideMaterialSlot = 0;
    this->UseFirstPersonComponent = false;
}

