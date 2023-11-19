#include "AnimNotify_HideBone.h"
#include "Components/SkinnedMeshComponent.h"

//Show Bone
void UAnimNotify_HideBone::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	MeshComp->USkinnedMeshComponent::HideBoneByName(BoneName, EPhysBodyOp::PBO_None);
	
}

//Hide Bone
void UAnimNotify_HideBone::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	MeshComp->USkinnedMeshComponent::UnHideBoneByName(BoneName);
}

UAnimNotify_HideBone::UAnimNotify_HideBone() {
}

