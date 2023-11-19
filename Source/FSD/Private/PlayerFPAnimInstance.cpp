#include "PlayerFPAnimInstance.h"
#include "PlayerCharacter.h"
#include "UObject/Object.h"
#include "Animation/AnimInstance.h"
#include "GameFramework/Actor.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"
#include "InventoryComponent.h"
#include "Item.h"
#include "Kismet/KismetSystemLibrary.h" 
#include "ItemCharacterAnimationSet.h"

void UPlayerFPAnimInstance::BlueprintUpdateAnimation(float DeltaTimeX)
{

}

void UPlayerFPAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
    Super::NativeUpdateAnimation(DeltaTime);

    APlayerCharacter* Owner = Cast<APlayerCharacter>(GetOwningActor());

    if (IsValid(Owner)) {
        UInventoryComponent* Inv = Cast<UInventoryComponent>(Owner->GetComponentByClass(UInventoryComponent::StaticClass()));
        if (IsValid(Inv)) {
            //Inv->GetEquippedItem()->Get
            UKismetSystemLibrary::PrintString(this, "[C++] FPAnimInstance - NativeUpdateAnimation - ", true, true, FColor::Cyan, 0.f);

            AItem* EquippedItem = Inv->GetEquippedItem();
            if (IsValid(EquippedItem)) {
                
                UItemCharacterAnimationSet* CharacterAnimSet = EquippedItem->GetCharacterAnimationSet();
                if (IsValid(CharacterAnimSet)) {
                    AnimationSetA = CharacterAnimSet;
                }
            }
        }
        //AnimationSetA = 
    }


}

UPlayerFPAnimInstance::UPlayerFPAnimInstance() {
    this->HeadBobScale = 1.00f;
    this->WeaponSwayRecoverySpeed = 10.00f;
    this->WeaponSwayAlphaRecoverySpeed = 25.00f;
    this->WeaponSwayMaxAngle = 10.00f;
    this->WeaponSwayAlpha = 1.00f;
    this->WeaponSwayToApply = 0.00f;
    this->HeadOnlyMode = false;
    this->FP_Idle = NULL;
    this->FP_Walk = NULL;
    this->FP_Sprint = NULL;
    this->FP_JumpStart = NULL;
    this->FP_JumpLoop = NULL;
    this->FP_JumpLand = NULL;
    this->FP_JumpLand_Aim = NULL;
    this->FP_Downed = NULL;
}

