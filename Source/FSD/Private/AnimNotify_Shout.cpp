#include "AnimNotify_Shout.h"
#include "DialogDataAsset.h"
#include "PlayerCharacter.h"
#include "InventoryComponent.h"
#include "Item.h"
#include "CommunicationComponent.h"

void UAnimNotify_Shout::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation){
    //Play Shout with notify event via Communication Component
    APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(MeshComp->GetOwner());

    if (IsValid(PlayerCharacter)) {
        UCommunicationComponent* CommunicationComp = PlayerCharacter->GetCommunicationComponent();

        if (IsValid(CommunicationComp) == false) {
            AItem* Item = Cast<AItem>(MeshComp->GetOwner());
            if (IsValid(Item)) {
                UCommunicationComponent* CommunicationComp = Cast<APlayerCharacter>(Item->GetOwner())->GetCommunicationComponent();
            }
        }

        if (IsValid(CommunicationComp)) {
            CommunicationComp->ShoutCustom(Shout);
        }
    }
}

UAnimNotify_Shout::UAnimNotify_Shout() {
    this->Shout = NULL;
    this->ShoutNetworked = true;
    this->LocalShoutVolumeMultiplier = 1.00f;
}

