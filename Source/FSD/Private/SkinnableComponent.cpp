#include "SkinnableComponent.h"
#include "FSDPlayerState.h"
#include "PlayerCharacter.h"
#include "Item.h"
#include "InventoryComponent.h"
#include "ItemID.h"
#include "ItemSkin.h"
#include "SkinEffect.h"

void USkinnableComponent::UpdateSkin(AFSDPlayerState* Player) {
}

void USkinnableComponent::OnLoadoutChanged() {
}

TArray<UItemSkin*> USkinnableComponent::GetSkinsForItem(UItemID* ItemID, EItemSkinType skinType) {
    return TArray<UItemSkin*>();
}

UItemSkin* USkinnableComponent::GetEquippedSkinMesh(UItemID* ItemID, AFSDPlayerState* Player) {
    return NULL;
}

UItemSkin* USkinnableComponent::GetEquippedSkinColor(UItemID* ItemID, AFSDPlayerState* Player) {
    return NULL;
}

UItemSkin* USkinnableComponent::GetEquippedSkin(UItemID* ItemID, EItemSkinType skinType, AFSDPlayerState* Player) {
    return NULL;
}

TArray<UItemSkin*> USkinnableComponent::GetEquippableColorSkins(UItemID* ItemID, AFSDPlayerState* Player) {
    return TArray<UItemSkin*>();
}

UItemSkin* USkinnableComponent::GetDefaultItemSkin(UItemID* ItemID, EItemSkinType itemSkinType) {
    return NULL;
}

UItemSkin* USkinnableComponent::GetBaseColorSkinForMeshSkin(UItemID* ItemID, UItemSkin* meshSkin) {
    return NULL;
}

void USkinnableComponent::EquipSkin(UItemSkin* Skin, UItemID* ItemID, AFSDPlayerState* Player) {
    UE_LOG(LogTemp, Log, TEXT("EquipSkin - Started Logic"));
    
    if (IsValid(Player) && IsValid(Skin) && IsValid(ItemID)) {
        APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(Player->GetPawn());
        if (IsValid(PlayerCharacter)) {
            UInventoryComponent* InvComp = PlayerCharacter->FindComponentByClass<UInventoryComponent>();
            if (IsValid(InvComp)) {
                TArray<AActor*> AllItems = InvComp->GetAllItems();

                for (AActor* item : AllItems) {
                    if (IsValid(item)) {
                        AItem* CastedItem = Cast<AItem>(item);
                        if (IsValid(CastedItem)) {
                            if (CastedItem->GetClass() == ItemID->GetItemClass()) {
                                CastedItem->OnSkinChanged(Cast<USkinEffect>(Skin->GetSkinEffect()));
                                UE_LOG(LogTemp, Log, TEXT("EquipSkin - OnSkinChanged to %s"), *CastedItem->GetName());
                            }
                        }

                    }

                }
            }
            else {
                UE_LOG(LogTemp, Error, TEXT("EquipSkin - Finding for InventoryComponent failed"));
            }
        }
        else {
            UE_LOG(LogTemp, Error, TEXT("EquipSkin - Cast to APlayerCharacter from Player failed"));
        }

    }
    else {
            UE_LOG(LogTemp, Error, TEXT("EquipSkin - Player, Skin, ItemID Invalid"));
    }
    
}

USkinnableComponent::USkinnableComponent() {
    this->EquippedSkinColor = NULL;
    this->EquippedSkinMesh = NULL;
}

