#include "SimpleArmorDamageComponent.h"
#include "Net/UnrealNetwork.h"

void USimpleArmorDamageComponent::OnRep_ArmorDamageInfo(FArmorDamageInfo OldArmorDamageInfo) {
}

void USimpleArmorDamageComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    
    DOREPLIFETIME(USimpleArmorDamageComponent, ArmorDamageInfo);
}

bool USimpleArmorDamageComponent::CanBeDestroyed(FName BoneName)
{
    return PhysBoneToArmor.Contains(BoneName);
}

USimpleArmorDamageComponent::USimpleArmorDamageComponent() {
    this->ArmorStrength = 10.00f;
}

