#include "SkeletalMeshSkinEffect.h"

USkeletalMeshSkinEffect::USkeletalMeshSkinEffect() {
}

USkeletalMesh* USkeletalMeshSkinEffect::LoadMesh() {
	USkeletalMesh* LoadedMesh = Cast<USkeletalMesh>(Mesh.LoadSynchronous());
	return LoadedMesh;
}
	

