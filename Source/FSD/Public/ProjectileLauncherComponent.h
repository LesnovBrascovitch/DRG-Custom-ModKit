#pragma once
#include "CoreMinimal.h"
#include "ProjectileLauncherBaseComponent.h"
#include "Templates/SubclassOf.h"
#include "ProjectileLauncherComponent.generated.h"

class AProjectileBase;

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class UProjectileLauncherComponent : public UProjectileLauncherBaseComponent {
    GENERATED_BODY()
public:
    virtual void Fire(const FVector& Origin, const FVector_NetQuantizeNormal& Direction, bool playFireFX) override;
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TSubclassOf<AProjectileBase> ProjectileClass;
    
public:
    UProjectileLauncherComponent();
    UFUNCTION(BlueprintAuthorityOnly, BlueprintCallable)
    void SetProjectileClass(TSubclassOf<AProjectileBase> NewProjectileClass);
    
};

