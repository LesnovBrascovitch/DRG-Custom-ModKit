#include "DualAnimatedItem.h"
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

void ADualAnimatedItem::OnSkinChanged_Implementation(USkinEffect* Skin) {
    Super::OnSkinChanged_Implementation(Skin);

}

UItemCharacterAnimationSet* ADualAnimatedItem::GetCharacterAnimationSet_Implementation()
{
    return this->CharacterAnimationSet;
}

USkeletalMeshComponent* ADualAnimatedItem::GetRItemMesh() const {
    return NULL;
}

USkeletalMeshComponent* ADualAnimatedItem::GetLItemMesh() const {
    return NULL;
}
void ADualAnimatedItem::RecieveEquipped_Implementation()
{
    UKismetSystemLibrary::PrintString(this, "[C++] ADualAnimatedItem - RecieveEquipped", true, true, FColor::Cyan, 2.f);
    if (this->Character) {
        UPlayerFPAnimInstance* FPAnim = Character->GetFPAnimInstance();
        //FPAnim->UAnimInstance::Montage_Play();
        FPAnim->UAnimInstance::Montage_Play(FP_EquipAnimation);

        USkeletalMeshComponent* FPMeshDwarf = Cast<USkeletalMeshComponent>(Character->GetDefaultSubobjectByName(TEXT("FPMesh")));

        if (IsValid(FPMeshDwarf)) {
            this->FPRMesh->AttachToComponent(FPMeshDwarf, FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("Dwarf_HandR_Attach"));
            this->FPLMesh->AttachToComponent(FPMeshDwarf, FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("Dwarf_HandL_Attach"));
        }
    }
}

void ADualAnimatedItem::RecieveStopUsing()
{
}

void ADualAnimatedItem::RecieveStopUsing_Implementation()
{
}

void ADualAnimatedItem::RecieveUnequipped_Implementation()
{
    UKismetSystemLibrary::PrintString(this, "[C++] AnimatedItem - RecieveUnequipped", true, true, FColor::Cyan, 2.f);
    //this->AActor::DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
    this->FPRMesh->DetachFromParent(false, true);
    this->FPLMesh->DetachFromParent(false, true);
}

void ADualAnimatedItem::RecieveStartUsing_Implementation()
{
}

void ADualAnimatedItem::RecieveCycledItem_Implementation()
{
}

ADualAnimatedItem::ADualAnimatedItem() {
    this->FPAnimInstance = NULL;
    this->TPAnimInstance = NULL;
    this->FPRMesh = CreateDefaultSubobject<UFirstPersonSkeletalMeshComponent>(TEXT("FPRMesh"));
    this->FPLMesh = CreateDefaultSubobject<UFirstPersonSkeletalMeshComponent>(TEXT("FPLMesh"));
    this->TPRMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("TPRMesh"));
    this->TPLMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("TPLMesh"));
    this->FP_EquipAnimation = NULL;
    this->TP_EquipAnimation = NULL;
    this->EquipDuration = 0.25f;
    this->CharacterAnimationSet = NULL;
}


