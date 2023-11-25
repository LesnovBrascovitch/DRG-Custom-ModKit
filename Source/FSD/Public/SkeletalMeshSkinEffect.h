#pragma once
#include "CoreMinimal.h"
#include "SkinEffect.h"
#include "SkeletalMeshSkinEffect.generated.h"

class USkeletalMesh;

UCLASS(Blueprintable, EditInlineNew)
class USkeletalMeshSkinEffect : public USkinEffect {
    GENERATED_BODY()
public:
    USkeletalMesh* LoadMesh();
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TSoftObjectPtr<USkeletalMesh> Mesh;
    
public:
    USkeletalMeshSkinEffect();
};

