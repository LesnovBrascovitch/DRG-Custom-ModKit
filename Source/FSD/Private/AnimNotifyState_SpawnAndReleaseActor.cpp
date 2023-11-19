#include "AnimNotifyState_SpawnAndReleaseActor.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "Animation/AnimSequenceBase.h"
#include "Animation/AnimMontage.h"
#include "Animation/AnimInstance.h"
#include "Engine/SkeletalMesh.h"
#include "Engine/World.h"
#include <Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h>
#include "SpawnReleasedActor.h"


void UAnimNotifyState_SpawnAndReleaseActor::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
    UKismetSystemLibrary::PrintString(this, "[C++] UAnimNotifyState_SpawnAndReleaseActor - NotifyBegin", true, true, FColor::Cyan, 2.f);
    if (IsValid(Actor)) {
        UWorld* World = MeshComp->GetWorld();
        
        //handle, MeshComp, &UAnimNotifyState_SpawnAndReleaseActor::Detach/*Function*/, TotalDuration/*Duration*/, false/*InLoop*/
        //GetWorld()->GetTimerManager().SetTimer(handle, &UAnimNotifyState_SpawnAndReleaseActor::Detach, TotalDuration, false, -1.0f);
        if (IsValid(World)) {
            AActor* SpawnedActor = World->SpawnActor<AActor>(Actor);
            if (IsValid(SpawnedActor)) {

                SpawnedActor->AttachToComponent(MeshComp, FAttachmentTransformRules::SnapToTargetIncludingScale, SocketName);
                //if (SpawnedActor->GetClass()->ImplementsInterface(ISpawnReleasedActor)) {
                ISpawnReleasedActor::Execute_OnSpawnRelease_Attached(SpawnedActor, MeshComp->GetOwner());
                //}
                this->TimerDelegate.BindUFunction(this, FName("Detach"), SpawnedActor);
                World->GetTimerManager().SetTimer(handle, TimerDelegate, TotalDuration, false);
            }
        }
    }
    else 
    {
        UKismetSystemLibrary::PrintString(this, "[C++] UAnimNotifyState_SpawnAndReleaseActor - NotifyBegin - Invalid Actor Class", true, true, FColor::Red, 4.f);
    }
}

void UAnimNotifyState_SpawnAndReleaseActor::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{

}

void UAnimNotifyState_SpawnAndReleaseActor::Detach(AActor* SpawnedActor)
{
    //SpawnedActor->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
    ISpawnReleasedActor::Execute_OnSpawnRelease_Released(SpawnedActor);
}

UAnimNotifyState_SpawnAndReleaseActor::UAnimNotifyState_SpawnAndReleaseActor() {
    this->Actor = NULL;
    this->ManualDetach = false;

    //FTimerDelegate TimerDelegate;
    FTimerManager& timerManager = GetWorld()->GetTimerManager();
    //FTimerHandle handle;
    this->TimerDelegate.BindUFunction(this, FName("Detach"));
}

