#include "CommunicationComponent.h"
#include "Templates/SubclassOf.h"
#include <Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h>
#include "DialogDataAsset.h"
#include "Components/AudioComponent.h"
#include "Math/UnrealMathUtility.h"
#include "Sound/SoundBase.h"
#include <Runtime/Engine/Classes/Engine/StreamableManager.h>
#include "Engine/StreamableManager.h"
#include "Kismet/GameplayStatics.h"


void UCommunicationComponent::ShoutCustomOrDefault(UDialogDataAsset* CustomShout, EShoutType DefaultShout) {
}

void UCommunicationComponent::ShoutCustomLocalOnly(UDialogDataAsset* NewShout) {
}

void UCommunicationComponent::ShoutCustomClosestDwarf(UObject* WorldContext, UDialogDataAsset* NewShout, FVector TargetLocation) {
}

void UCommunicationComponent::ShoutCustom(UDialogDataAsset* NewShout) {
    ServerShout(NewShout);
}

void UCommunicationComponent::Shout(EShoutType NewShout) {
    if (true) {

    }
}

void UCommunicationComponent::SetMissionControlPaused(bool IsPaused) {
}




void UCommunicationComponent::ServerShout_Implementation(UDialogDataAsset* NewShout) {
    UKismetSystemLibrary::PrintString(this, "[C++] CommunicationComponent - Server_Shout", true, true, FColor::Cyan, 2.f);

    if (IsValid(NewShout)) {

        //FStreamableManager& Streamable = UGameGlobals::Get().StreamableManager;

        UKismetSystemLibrary::PrintString(this, "[C++] CommunicationComponent - Server_Shout - " + NewShout->GetName() + " is selected", true, true, FColor::Cyan, 2.f);


        int32 randomIndex = FMath::RandRange(0, NewShout->Entries.Num() - 1);

        USoundBase* ShoutSound = NewShout->Entries[randomIndex].audio.LoadSynchronous();

        if (IsValid(ShoutSound)) {
            ShoutAudioComponent->SetSound(ShoutSound);
            ShoutAudioComponent->Play();
        }
    }
}

void UCommunicationComponent::ServerMissionShout_Implementation(UDialogDataAsset* NewShout, int32 Index, bool bPriority) {
}

UAudioComponent* UCommunicationComponent::PlayPitchedByClass(UObject* WorldContextObject, TSubclassOf<APlayerCharacter> CharacterClass, USoundBase* Sound, UDialogDataAsset* NewShout, EShoutType ShoutType, UAudioComponent* AudioComponent) {
    return NULL;
}

void UCommunicationComponent::PlayPitchedAsync(UDialogDataAsset* NewShout, EShoutType ShoutType, bool IgnoreCoolDown, UAudioComponent* AudioComponent, UObject* WorldContextObject, float shoutVolumeMultiplier, EAsyncLoadPriority Priority) {
}

UAudioComponent* UCommunicationComponent::PlayPitched(USoundBase* Sound, UDialogDataAsset* NewShout, EShoutType ShoutType, bool IgnoreCoolDown, UAudioComponent* AudioComponent, UObject* WorldContextObject) {
    return NULL;
}

int32 UCommunicationComponent::MissionShoutLocally(UObject* WorldContext, UDialogDataAsset* NewShout) {
    return 0;
}

void UCommunicationComponent::MissionShout(UObject* WorldContext, UDialogDataAsset* NewShout, bool bPriority) {
}

bool UCommunicationComponent::IsMissionControlSpeaking() const {
    return false;
}

void UCommunicationComponent::ClientShout_Implementation(APlayerCharacter* Sender, UDialogDataAsset* NewShout, int32 Index) {
}

void UCommunicationComponent::ClientMissionShout_Implementation(UDialogDataAsset* NewShout, int32 Index, bool bPriority) {
}

UCommunicationComponent::UCommunicationComponent() {
    this->ShoutingEnabled = true;
    this->ShoutWidgetType = NULL;
    this->CharacterShouts = NULL;
    this->PitchMultiplier = 1.00f;
    this->MinShoutDelay = 1.00f;
    this->CloseRangeShoutDistance = 1500.00f;
    this->bMissionControlPaused = false;
    this->MissionControlAudioComponent = NULL;
    this->Character = NULL;
    this->LastShout = NULL;
    this->ShoutAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("CharacterShoutsAudioComponent"));
}

