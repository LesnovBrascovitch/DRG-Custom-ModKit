#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_CycleItemComplete.generated.h"

UCLASS(Blueprintable, CollapseCategories)
class UAnimNotify_CycleItemComplete : public UAnimNotify {
    GENERATED_BODY()
public:
    UAnimNotify_CycleItemComplete();

protected:
    virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};

