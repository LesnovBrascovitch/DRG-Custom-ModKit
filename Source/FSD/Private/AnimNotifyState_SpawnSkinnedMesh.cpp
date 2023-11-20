#include "AnimNotifyState_SpawnSkinnedMesh.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include <Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h>
#include "PlayerCharacter.h"
#include "InventoryComponent.h"
#include "Item.h"
#include "FirstPersonStaticMeshComponent.h"

void UAnimNotifyState_SpawnSkinnedMesh::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
    

    UKismetSystemLibrary::PrintString(MeshComp->GetWorld(), "[C++] SpawnSkinnedMesh Notify State - NotifyBegin", true, true, FColor::Cyan, 2.f);

    AActor* Owner = MeshComp->GetOwner();
    APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(Owner);

    if (IsValid(PlayerCharacter)) {
        UInventoryComponent* InvComp = PlayerCharacter->FindComponentByClass<UInventoryComponent>();
        if (IsValid(InvComp)) {
            AItem* EquippedItem = InvComp->GetEquippedItem();
            if (IsValid(EquippedItem)) {
                UStaticMeshComponent* Mesh = EquippedItem->GetFPAnimationEventMesh();
                if (IsValid(Mesh)) {
                    UStaticMeshComponent* AttachedMeshComp = Cast<UStaticMeshComponent>(Owner->AActor::AddComponentByClass(UStaticMeshComponent::StaticClass(), true, FTransform(FRotator(0.f), FVector(0.f), FVector(0.f)), true));

                    if (IsValid(AttachedMeshComp)) {
                        AttachedMeshComp->SetStaticMesh(Mesh->GetStaticMesh());
                        AttachedMeshComp->AttachToComponent(MeshComp, FAttachmentTransformRules::SnapToTargetIncludingScale, SocketName);
                        AttachedMeshComp->RegisterComponent();
                    }
                }
            }
        }
    }
    
    
}

//Destroy added components by finding through attached components.
void UAnimNotifyState_SpawnSkinnedMesh::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    TArray<USceneComponent*> AttachedComps = MeshComp->GetAttachChildren();
    for (USceneComponent* AttachedComp : AttachedComps) {
        UStaticMeshComponent* StaticMesh = Cast<UStaticMeshComponent>(AttachedComp);
        if (IsValid(StaticMesh)) {
            //if (StaticMesh->GetStaticMesh() == Mesh) {
                AttachedComp->DestroyComponent();
            //}
        }

    }
}

UAnimNotifyState_SpawnSkinnedMesh::UAnimNotifyState_SpawnSkinnedMesh() {
    this->ItemCategory = EItemCategory::PrimaryWeapon;
    this->UseFirstPersonComponent = false;
    
}

