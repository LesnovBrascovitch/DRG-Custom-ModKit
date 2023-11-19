#include "SimpleHealthComponent.h"
#include "Net/UnrealNetwork.h"
#include "HealthComponentBase.h"
#include "Math/UnrealMathUtility.h"

void USimpleHealthComponent::TakeDamageSimple(float damageAmount, AActor* DamageCauser, UDamageClass* DamageClass) {
    Damage = FMath::Clamp(Damage + damageAmount, 0.f, MaxHealth);
    OnHealthChanged.Broadcast(MaxHealth - Damage);
    OnDamageTaken.Broadcast(damageAmount);

    if (Damage == MaxHealth) {
        OnDeath.Broadcast(this);
    }
}

void USimpleHealthComponent::OnRep_Damage(float oldDamage) {
}

float USimpleHealthComponent::HealFromDeath(float Amount) {
    return 0.0f;
}

void USimpleHealthComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    
    DOREPLIFETIME(USimpleHealthComponent, Damage);
}

USimpleHealthComponent::USimpleHealthComponent() {
    this->Damage = 0.00f;
    this->MaxHealth = 100.00f;
    this->InvulnerableToNonDefinedResistances = false;
    this->EnvironmentalDamageResistance = 1.00f;
    this->bShowHealthBar = false;
    this->AutomaticFlushNetDormancy = false;
}

