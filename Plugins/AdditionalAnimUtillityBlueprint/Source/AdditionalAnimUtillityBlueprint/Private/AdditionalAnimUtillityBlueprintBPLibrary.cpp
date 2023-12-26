// Copyright Epic Games, Inc. All Rights Reserved.

#include "AdditionalAnimUtillityBlueprintBPLibrary.h"
#include "AdditionalAnimUtillityBlueprint.h"
#include "Animation/AnimMontage.h"
#include "ContentBrowserModule.h"
#include "IContentBrowserSingleton.h"

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
TArray<FString> UAdditionalAnimUtillityBlueprintBPLibrary::GetSelectedFolders()
{
	TArray<FString> Folders;
	FContentBrowserModule& ContentBrowserModule = FModuleManager::LoadModuleChecked<FContentBrowserModule>("ContentBrowser");
	ContentBrowserModule.Get().GetSelectedFolders(Folders);
	//IContentBrowserSingleton& ContentBrowserSingleton = ContentBrowserModule.Get();

	return Folders;
}

