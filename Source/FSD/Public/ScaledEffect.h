#pragma once
#include "CoreMinimal.h"
#include "ScaledEffect.generated.h"

class UFXSystemAsset;

USTRUCT(BlueprintType)
struct FScaledEffect {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true))
    UFXSystemAsset* ParticleSystem;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true))
    float Scale;

protected:

    
public:
    FSD_API FScaledEffect();
};

