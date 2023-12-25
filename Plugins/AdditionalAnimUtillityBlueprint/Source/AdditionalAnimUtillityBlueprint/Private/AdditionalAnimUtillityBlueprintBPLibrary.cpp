// Copyright Epic Games, Inc. All Rights Reserved.

#include "AdditionalAnimUtillityBlueprintBPLibrary.h"
#include "AdditionalAnimUtillityBlueprint.h"
#include "Animation/AnimMontage.h"

UAdditionalAnimUtillityBlueprintBPLibrary::UAdditionalAnimUtillityBlueprintBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

float UAdditionalAnimUtillityBlueprintBPLibrary::AdditionalAnimUtillityBlueprintSampleFunction(float Param)
{
	return -1;
}

void UAdditionalAnimUtillityBlueprintBPLibrary::SetMontagePlayScale(UAnimMontage* montage, float playscale)
{
	if (IsValid(montage)) {
		montage->RateScale = playscale;
	}
}

