#include "AnimNotifyState_Salute.h"
#include "Kismet/KismetSystemLibrary.h"
#include <Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h>
#include "PlayerCharacter.h"
#include "InventoryComponent.h"
#include "Item.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "Animation/AnimSequenceBase.h"
#include "Animation/AnimMontage.h"
#include "Animation/AnimInstance.h"

void UAnimNotifyState_Salute::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    UKismetSystemLibrary::PrintString(MeshComp->GetWorld(), "[C++] Salute Notify State - NotifyEnd", true, true, FColor::Cyan, 2.f);

    APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(MeshComp->GetOwner());
    USkeletalMeshComponent* FPMeshDwarf = Cast<USkeletalMeshComponent>(PlayerCharacter->GetDefaultSubobjectByName(TEXT("FPMesh")));

    if (IsValid(PlayerCharacter) && IsValid(FPMeshDwarf)) {
        UInventoryComponent* InvComp = PlayerCharacter->FindComponentByClass<UInventoryComponent>();
        if (IsValid(InvComp)) {
            AItem* Pickaxe = InvComp->GetItem(EItemCategory::MiningTool);
            if (Pickaxe != nullptr) {
                Pickaxe->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
            }
        }
    }
}

void UAnimNotifyState_Salute::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
}

void UAnimNotifyState_Salute::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration){
    UKismetSystemLibrary::PrintString(MeshComp->GetWorld(), "[C++] Salute Notify State - NotifyBegin", true, true, FColor::Cyan, 2.f);

    APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(MeshComp->GetOwner());
    USkeletalMeshComponent* FPMeshDwarf = Cast<USkeletalMeshComponent>(PlayerCharacter->GetDefaultSubobjectByName(TEXT("FPMesh")));

    if (IsValid(PlayerCharacter) && IsValid(FPMeshDwarf)) {
        UInventoryComponent* InvComp = PlayerCharacter->FindComponentByClass<UInventoryComponent>();
        if (IsValid(InvComp)) {
            AItem* Pickaxe = InvComp->GetItem(EItemCategory::MiningTool);
            if (Pickaxe != nullptr) {
                Pickaxe->AttachToComponent(FPMeshDwarf, FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("Dwarf_HandR_Pickaxe"));
            }
        }
    }
}

UAnimNotifyState_Salute::UAnimNotifyState_Salute() {
    this->FirstPerson = false;
}

