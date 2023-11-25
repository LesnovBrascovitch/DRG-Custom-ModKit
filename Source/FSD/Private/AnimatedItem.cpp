#include "AnimatedItem.h"
#include "Components/SkeletalMeshComponent.h"
#include "FirstPersonSkeletalMeshComponent.h"
#include "SkinnableComponent.h"
#include "Item.h"
#include "PlayerCharacter.h"
#include "GameFramework/Actor.h"
#include "Kismet/KismetSystemLibrary.h" 
#include "Animation/AnimInstance.h"
#include "PlayerFPAnimInstance.h"
#include "ItemCharacterAnimationSet.h"
#include "Skinnable.h"
#include "SkinEffect.h"
#include "SkeletalMeshSkinEffect.h"

void AAnimatedItem::OnSkinChanged_Implementation(USkinEffect* Skin) {
    if (IsValid(Skin)) {
        USkeletalMeshSkinEffect* SkeletalSkinEffect = Cast<USkeletalMeshSkinEffect>(Skin);
        if (IsValid(SkeletalSkinEffect)) {
            USkeletalMesh* LoadedSkin = SkeletalSkinEffect->LoadMesh();
            if (IsValid(LoadedSkin)) {
                
                FPMesh->SetSkeletalMesh(LoadedSkin);
            }
        }
    }
}

void AAnimatedItem::UpdateSkin() {

}

FTransform AAnimatedItem::GetMuzzle() const {
    return FTransform{};
}

USkeletalMeshComponent* AAnimatedItem::GetItemMesh() const {
    return NULL;
}


void AAnimatedItem::RecieveEquipped_Implementation()
{
    UKismetSystemLibrary::PrintString(this, "[C++] AnimatedItem - RecieveEquipped", true, true, FColor::Cyan, 2.f);
    if (this->Character) {
        UPlayerFPAnimInstance* FPAnim = Character->GetFPAnimInstance();
        //FPAnim->UAnimInstance::Montage_Play();
        FPAnim->UAnimInstance::Montage_Play(FP_EquipAnimation);

        USkeletalMeshComponent* FPMeshDwarf = Cast<USkeletalMeshComponent>(Character->GetDefaultSubobjectByName(TEXT("FPMesh")));

        if (IsValid(FPMeshDwarf)) {
            this->FPMesh->AttachToComponent(FPMeshDwarf, FAttachmentTransformRules::SnapToTargetIncludingScale,TEXT("Dwarf_HandR_Attach"));
        }
    }
}

void AAnimatedItem::RecieveUnequipped_Implementation()
{
    UKismetSystemLibrary::PrintString(this, "[C++] AnimatedItem - RecieveUnequipped", true, true, FColor::Cyan, 2.f);
    this->AActor::DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
}

void AAnimatedItem::RecieveStartUsing_Implementation()
{
}

void AAnimatedItem::RecieveCycledItem_Implementation()
{
}

void AAnimatedItem::RecieveStopUsing_Implementation()
{
    UKismetSystemLibrary::PrintString(this, "[C++] AnimatedItem - RecieveStopUsing", true, true, FColor::Cyan, 2.f);
}

UItemCharacterAnimationSet* AAnimatedItem::GetCharacterAnimationSet_Implementation()
{
    return this->CharacterAnimationSet;
}


AAnimatedItem::AAnimatedItem() {
    this->Skinnable = CreateDefaultSubobject<USkinnableComponent>(TEXT("Skinnable"));
    this->FPAnimInstance = NULL;
    this->TPAnimInstance = NULL;
    this->FPMesh = CreateDefaultSubobject<UFirstPersonSkeletalMeshComponent>(TEXT("FPMesh"));
    this->TPMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("TPMesh"));
    this->FP_EquipAnimation = NULL;
    this->FP_IdleAnimation = NULL;
    this->TP_EquipAnimation = NULL;
    this->TP_IdleAnimation = NULL;
    this->EquipDuration = 0.25f;
    this->CharacterAnimationSet = NULL;




}

