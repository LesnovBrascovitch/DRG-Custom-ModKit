#include "Item.h"
#include "Net/UnrealNetwork.h"
#include "Templates/SubclassOf.h"
#include "UpgradableItemComponent.h"
#include "PlayerCharacter.h"
#include "InventoryComponent.h"
#include "Engine/EngineTypes.h"
#include <Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h>
#include "Skinnable.h"
void AItem::OnSkinChanged_Implementation(USkinEffect* Skin) {

}

void AItem::UpdateSkin() {
}

UAudioComponent* AItem::SpawnSoundAttached(USoundBase* Sound, USceneComponent* AttachToComponent, float PriorityOverride, FName AttachPointName, FVector Location, FRotator Rotation, TEnumAsByte<EAttachLocation::Type> LocationType, bool bStopWhenAttachedToDestroyed, float VolumeMultiplier, float PitchMultiplier, float StartTime, USoundAttenuation* AttenuationSettings, USoundConcurrency* ConcurrencySettings, bool bAutoDestroy, bool SendVibration) {
    return NULL;
}

UAudioComponent* AItem::SpawnSoundAtLocation(USoundBase* Sound, FVector Location, FRotator Rotation, float VolumeMultiplier, float PitchMultiplier, float StartTime, USoundAttenuation* AttenuationSettings, USoundConcurrency* ConcurrencySettings, bool bAutoDestroy, bool SendVibration) {
    return NULL;
}

UAudioComponent* AItem::SpawnSound2D(USoundBase* Sound, float PriorityOverride, float VolumeMultiplier, float PitchMultiplier, float StartTime, USoundConcurrency* ConcurrencySettings, bool bPersistAcrossLevelTransition, bool bAutoDestroy, bool SendVibration) {
    return NULL;
}

void AItem::Server_StartUsing_Implementation(bool NewIsUsing) {
}

void AItem::Resupply(float percentage) {
}

UFirstPersonStaticMeshComponent* AItem::GetFPAnimationEventMesh()
{
    return Receive_GetFPAnimationEventMesh();
}



void AItem::OnRep_IsUsing(bool OldValue) {
}

void AItem::OnOwnerDestroyed(AActor* owningActor) {
}

bool AItem::IsLocallyControlled() const {
    return false;
}

bool AItem::IsFirstPerson() const {
    return false;
}

TSubclassOf<AActor> AItem::GetWeaponViewClass() const {
    return NULL;
}

FItemLoadoutAnimations AItem::GetLoadoutAnimations() const {
    return FItemLoadoutAnimations{};
}

FText AItem::GetItemName() const {
    return FText::GetEmpty();
}

UTexture2D* AItem::GetItemIconLine() const {
    return NULL;
}

UTexture2D* AItem::GetItemIconBG() const {
    return NULL;
}

AItem* AItem::GetItemDefaultObject(TSubclassOf<AItem> itemClass) {
    return NULL;
}

FText AItem::GetItemCategory() const {
    return FText::GetEmpty();
}

USceneComponent* AItem::GetHeatingAudioSceneComponent_Implementation() {
    return NULL;
}

/*UItemCharacterAnimationSet* AItem::GetCharacterAnimationSet() {
    return NULL;
} */

UItemCharacterAnimationSet* AItem::GetCharacterAnimationSet_Implementation() {
    return NULL;
}

FString AItem::GetAnalyticsItemName() const {
    return TEXT("");
}

FString AItem::GetAnalyticsItemCategory() const {
    return TEXT("");
}

void AItem::RecieveUnequipped_Implementation()
{
}

void AItem::RecieveStopUsing_Implementation()
{
}

void AItem::RecieveStartUsing_Implementation()
{
}

void AItem::RecieveEquipped_Implementation()
{
}

void AItem::RecieveCycledItem_Implementation()
{
}

void AItem::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    
    DOREPLIFETIME(AItem, overHeated);
    DOREPLIFETIME(AItem, IsUsing);
}

AItem::AItem() {
    this->EnableDangerousSaveGameIDEditing = false;
    this->ItemID = NULL;
    this->Character = NULL;
    this->UpgradableItem = CreateDefaultSubobject<UUpgradableItemComponent>(TEXT("Upgradable"));
    this->CameraShake = NULL;
    this->CameraShakeOnStartUsing = false;
    this->CameraShakeOnEquip = false;
    this->HeatCurve = NULL;
    this->ManualHeatPerUse = 0.00f;
    this->CooldownRate = 1.00f;
    this->ManualCooldownDelay = -1.00f;
    this->UnjamDuration = 8.00f;
    this->CurrentTemperature = 0.00f;
    this->AudioTemperature = NULL;
    this->AudioTemperatureFadeout = 0.00f;
    this->TemperatureFloatParam = TEXT("Temperature");
    this->TemperatureAudioComponent = NULL;
    this->overHeated = false;
    this->ShoutOverheated = NULL;
    this->bAimAssistEnabled = true;
    this->MovementRateWhileUsing = 1.00f;
    this->CanPlayLedgeClimbWhileUsing = true;
    this->CanInspectItem = true;
    this->CanSprintWithItem = true;
    this->CustomIconWidget = NULL;
    this->AdvancedVibrationSendLevel = 1.00f;
    this->IsEquipped = false;
    this->IsUsing = false;


}

void AItem::BeginPlay()
{
    Super::BeginPlay();

    Character = Cast<APlayerCharacter>(GetOwner());
    
    if(Character) {


    }
}

