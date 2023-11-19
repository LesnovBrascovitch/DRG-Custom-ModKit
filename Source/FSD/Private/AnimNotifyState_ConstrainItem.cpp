#include "AnimNotifyState_ConstrainItem.h"
#include "AnimatedItem.h"
#include "InventoryComponent.h"
#include "PlayerCharacter.h"

UAnimNotifyState_ConstrainItem::UAnimNotifyState_ConstrainItem() {
}

void UAnimNotifyState_ConstrainItem::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    UKismetSystemLibrary::PrintString(MeshComp->GetWorld(), "[C++] ConstrainItem Notify State - NotifyEnd", true, true, FColor::Cyan, 2.f);

    AAnimatedItem* EquippedAnimatedItem = Cast<AAnimatedItem>(MeshComp->GetOwner());

    if (IsValid(EquippedAnimatedItem)) {
        APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(EquippedAnimatedItem->GetOwner());
        USkeletalMeshComponent* FPMeshDwarf = Cast<USkeletalMeshComponent>(PlayerCharacter->GetDefaultSubobjectByName(TEXT("FPMesh")));

        if (IsValid(PlayerCharacter) && IsValid(FPMeshDwarf)) {
            UInventoryComponent* InvComp = PlayerCharacter->FindComponentByClass<UInventoryComponent>();
            if (IsValid(InvComp)) {
                AItem* EquippedItem = InvComp->GetEquippedItem();
                if (EquippedItem != nullptr) {
                    EquippedItem->AttachToComponent(FPMeshDwarf, FAttachmentTransformRules::KeepRelativeTransform, OldConstraint);
                }
            }
        }
    }
}

void UAnimNotifyState_ConstrainItem::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
}

void UAnimNotifyState_ConstrainItem::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) {
    UKismetSystemLibrary::PrintString(MeshComp->GetWorld(), "[C++] ConstrainItem Notify State - NotifyBegin", true, true, FColor::Cyan, 2.f);

    AAnimatedItem* EquippedAnimatedItem = Cast<AAnimatedItem>(MeshComp->GetOwner());

    if (IsValid(EquippedAnimatedItem)) {
        APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(EquippedAnimatedItem->GetOwner());
        USkeletalMeshComponent* FPMeshDwarf = Cast<USkeletalMeshComponent>(PlayerCharacter->GetDefaultSubobjectByName(TEXT("FPMesh")));

        if (IsValid(PlayerCharacter) && IsValid(FPMeshDwarf)) {
            UInventoryComponent* InvComp = PlayerCharacter->FindComponentByClass<UInventoryComponent>();
            if (IsValid(InvComp)) {
                AItem* EquippedItem = InvComp->GetEquippedItem();
                if (EquippedItem != nullptr) {
                    EquippedItem->AttachToComponent(FPMeshDwarf, FAttachmentTransformRules::KeepRelativeTransform, NewConstraint);
                }
            }
        }
    }
}