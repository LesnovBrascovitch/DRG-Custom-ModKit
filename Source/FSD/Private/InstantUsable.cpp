#include "InstantUsable.h"
#include "PlayerCharacter.h"
#include "Net/UnrealNetwork.h"
#include "PlayerAnimInstance.h"
#include "PlayerFPAnimInstance.h"
#include "Animation/AnimInstance.h"
#include "CommunicationComponent.h"
#include "UseAnimationSetting.h"
#include "Animation/AnimMontage.h"
#include "DialogDataAsset.h"

void UInstantUsable::BeginUse(APlayerCharacter* User, EInputKeys Key) {
    if (IsValid(User)) {
        UCommunicationComponent* Communication = User->FindComponentByClass<UCommunicationComponent>();
        
        if (IsValid(Communication)) {
            if (IsValid(ShoutBegin)) {
                Communication->ShoutCustom(ShoutBegin);
            }
        }

        if (IsValid(AnimationSettings)) {
            UAnimMontage* FPBeginMontage = AnimationSettings->GetBeginFPMontage();
            if (IsValid(FPBeginMontage)) {
                User->GetFPAnimInstance()->Montage_Play(FPBeginMontage);
            }
        }

        

        OnUsedBy.Broadcast(User, Key);

        if (TurnOffAfterUse) {
            Usable = false;
        }
    }
}

void UInstantUsable::SetCanUse(bool CanUse) {
}

void UInstantUsable::OnRep_Usable() {
}

void UInstantUsable::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    
    DOREPLIFETIME(UInstantUsable, Usable);
}

UInstantUsable::UInstantUsable() {
    this->bShowUsingUI = true;
    this->AudioCompletedUse = NULL;
    this->UseDelayedAudio = false;
    this->AudioDelay = 0.00f;
    this->RefreshDelayOnNewUse = true;
    this->Usable = false;
    this->TurnOffAfterUse = false;
}

