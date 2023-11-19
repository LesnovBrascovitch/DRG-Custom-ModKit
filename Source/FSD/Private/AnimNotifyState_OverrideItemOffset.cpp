#include "AnimNotifyState_OverrideItemOffset.h"
#include <Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h>
#include "PlayerCharacter.h"
#include "InventoryComponent.h"
#include "Item.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "Animation/AnimSequenceBase.h"
#include "Animation/AnimMontage.h"
#include "Animation/AnimInstance.h"

void UAnimNotifyState_OverrideItemOffset::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    UKismetSystemLibrary::PrintString(MeshComp->GetWorld(), "[C++] OverrideItemOffset Notify State - NotifyEnd", true, true, FColor::Cyan, 2.f);

    APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(MeshComp->GetOwner());
    USkeletalMeshComponent* FPMeshDwarf = Cast<USkeletalMeshComponent>(PlayerCharacter->GetDefaultSubobjectByName(TEXT("FPMesh")));

    if (IsValid(PlayerCharacter) && IsValid(FPMeshDwarf)) {
        UInventoryComponent* InvComp = PlayerCharacter->FindComponentByClass<UInventoryComponent>();
        if (IsValid(InvComp)) {
            AItem* EquippedItem = InvComp->GetEquippedItem();
            if (EquippedItem != nullptr) {
                EquippedItem->SetActorRelativeLocation(FVector(0.f));
            }
        }
    }
}

void UAnimNotifyState_OverrideItemOffset::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
}

void UAnimNotifyState_OverrideItemOffset::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) {
    UKismetSystemLibrary::PrintString(MeshComp->GetWorld(), "[C++] OverrideItemOffset Notify State - NotifyBegin", true, true, FColor::Cyan, 2.f);

    APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(MeshComp->GetOwner());
    USkeletalMeshComponent* FPMeshDwarf = Cast<USkeletalMeshComponent>(PlayerCharacter->GetDefaultSubobjectByName(TEXT("FPMesh")));

    if (IsValid(PlayerCharacter) && IsValid(FPMeshDwarf)) {
        UInventoryComponent* InvComp = PlayerCharacter->FindComponentByClass<UInventoryComponent>();
        if (IsValid(InvComp)) {
            AItem* EquippedItem = InvComp->GetEquippedItem();
            if (EquippedItem != nullptr) {
                EquippedItem->SetActorRelativeLocation(FVector(1000.f));
            }
        }
    }
}
UAnimNotifyState_OverrideItemOffset::UAnimNotifyState_OverrideItemOffset() {
}

