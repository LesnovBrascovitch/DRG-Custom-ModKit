#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Item.h"
#include "PlayerFPAnimInstance.h"
#include "AnimatedItem.generated.h"

class UAnimMontage;
class UItemCharacterAnimationSet;
class UPlayerAnimInstance;
class USkeletalMeshComponent;
class USkinnableComponent;

UCLASS(Abstract, Blueprintable)
class AAnimatedItem : public AItem {
    GENERATED_BODY()
public:
    virtual void OnSkinChanged_Implementation(USkinEffect* Skin);

    virtual void UpdateSkin();

    UItemCharacterAnimationSet* GetCharacterAnimationSet();
    virtual UItemCharacterAnimationSet* AAnimatedItem::GetCharacterAnimationSet_Implementation() override;
protected:
    UPROPERTY(AssetRegistrySearchable, BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    USkinnableComponent* Skinnable;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    UPlayerAnimInstance* FPAnimInstance;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    UPlayerAnimInstance* TPAnimInstance;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    USkeletalMeshComponent* FPMesh;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    USkeletalMeshComponent* TPMesh;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UAnimMontage* FP_EquipAnimation;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UAnimMontage* FP_IdleAnimation;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UAnimMontage* TP_EquipAnimation;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UAnimMontage* TP_IdleAnimation;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float EquipDuration;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UItemCharacterAnimationSet* CharacterAnimationSet;

    void RecieveEquipped();
    virtual void RecieveEquipped_Implementation() override;

    void RecieveStopUsing();
    virtual void RecieveStopUsing_Implementation() override;

    void RecieveUnequipped();
    virtual void RecieveUnequipped_Implementation() override;

    void RecieveStartUsing();
    virtual void RecieveStartUsing_Implementation() override;

    void RecieveCycledItem();
    virtual void RecieveCycledItem_Implementation() override;
//    void RecieveEquipped() override;
    
public:
    AAnimatedItem();

protected:
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnReceiveEquippedFinished();
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    FTransform GetMuzzle() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    USkeletalMeshComponent* GetItemMesh() const;
    
};

