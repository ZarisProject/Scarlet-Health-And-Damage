// Fill out your copyright notice in the Description page of Project Settings.


#include "SHD_HealthComponent.h"

// Sets default values for this component's properties
USHD_HealthComponent::USHD_HealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void USHD_HealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// Begin play with max health
	Health = MaxHealth;
}


// Called every frame
void USHD_HealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


// Reducts health points based on provided damage scaled according to it's type and DamageScalingMap
void USHD_HealthComponent::ApplyDamage(float Damage, ESHD_DamageType Type, AActor* Initiator)
{
	// No damage for the dead!
	if (!IsAlive()) return;

	// Resolving actual damage
	float ScalingFactor = 1.f;
	float* DamageScalingMapEntry = DamageScalingMap.Find(Type);
	if (DamageScalingMapEntry)
		ScalingFactor = *DamageScalingMapEntry;

	float ActualDamage = Damage * ScalingFactor;

	// Applying damage
	Health -= ActualDamage;

	// Clamping health + Death check
	if (Health <= 0.f)
	{
		Health = 0.0f;
		Alive = !CanDie;
	}

	// Delegate calls
	OnDamageTaken.Broadcast(Damage, Type, Initiator);
	OnHealthChanged.Broadcast(-1.f * ActualDamage);

	if (!Alive)
	{
		OnDeath.Broadcast();
	}
}

// Restors health points
void USHD_HealthComponent::RegenerateHealth(float Amount)
{
	float Delta = Amount;

	// Healing
	Health += Amount;

	// Clamp health to max health
	if (Health > MaxHealth)
	{
		Delta = Amount - (Health - MaxHealth); // Delta calculation for the delegate call
		Health = MaxHealth;
	}

	// Delegate calls
	OnHealthChanged.Broadcast(Delta);
}

// Revives the component, making it alive again
// Health is set to NewHealth
void USHD_HealthComponent::Revive(float NewHealth)
{
	// No revival for the living!
	if (IsAlive()) return;

	// Delta calculation (for the delegate)
	float Delta = NewHealth - Health;

	// Revivial logic
	Health = NewHealth;
	Alive = true;

	// Delegate calls
	OnRevived.Broadcast();
	OnHealthChanged.Broadcast(Delta);
}

