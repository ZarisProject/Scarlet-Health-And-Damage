// Fill out your copyright notice in the Description page of Project Settings.


#include "SHD_RegenHealthComponent.h"

// Called when the game starts
void USHD_RegenHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// Subscribing ResetTimer to OnDamageTaken and OnRevived
	FScriptDelegate Delegate;
	Delegate.BindUFunction(this, "ResetTimer");

	OnDamageTaken.Add(Delegate);
	OnRevived.Add(Delegate);
}

// Subscribed to OnDamageTaken
void USHD_RegenHealthComponent::ResetTimer(float Damage, ESHD_DamageType Type, AActor* Initiator)
{
	// Reset regeneration timer
	RegenerationTimer = RegenerationTimeout;
}

// Called every frame
void USHD_RegenHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Regenereration timer
	if (RegenerationTimer > 0.0)
		RegenerationTimer -= DeltaTime;

	// Regeneration logic
	if (IsRegenerationActive())
	{
		RegenerateHealth(RegenerationRate * DeltaTime);
	}
}

// Whether health is currently regenerating
bool USHD_RegenHealthComponent::IsRegenerationActive()
{ 
	return (RegenerationTimer <= 0.0f) && (Health < MaxHealth) && IsAlive(); 
}
