// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "SHD_DamageType.h"

#include "SHD_HealthComponent.generated.h"


// Delegate declarations
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnDamageTaken, float, Damage, ESHD_DamageType, Type, AActor*, Initiator);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float, Delta);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRevived);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent, Blueprintable) )
class SCARLETHEALTHANDDAMAGE_API USHD_HealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USHD_HealthComponent();

protected:

	// Current amount of health "points"
	float Health = 0.0;

	// Whether actor (component) is still alive (health > 0.0) or not 
	bool Alive = true;

public:

	// Maximum amount of health "points"
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Default")
	float MaxHealth = 100.0f;

	// Whether this component stops being alive when it's health is depleted
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Default")
	bool CanDie = true;

	// Scaling factors for different types of damage
	// If damage type is not present in the map, then 1.0 scaling is assumed
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Default")
	TMap<ESHD_DamageType, float> DamageScalingMap;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Returns current amount of health "points"
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "ScarletHealthDamage|Health")
	float GetHealth() { return Health; }

	// Returns maximum amount of health "points"
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "ScarletHealthDamage|Health")
	float GetMaxHealth() { return MaxHealth; }

	// Returns whether actor (component) is still alive (health > 0.0) or not 
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "ScarletHealthDamage|Health")
	bool IsAlive() { return Alive; }

	
	// Reducts health points based on provided damage scaled according to it's type and DamageScalingMap
	UFUNCTION(BlueprintCallable, Category = "ScarletHealthDamage|Health")
	void ApplyDamage(float Damage, ESHD_DamageType Type, AActor* Initiator);

	// Restors health points
	UFUNCTION(BlueprintCallable, Category = "ScarletHealthDamage|Health")
	void RegenerateHealth(float Amount);

	// Revives the component, making it alive again
	// Health is set to NewHealth
	UFUNCTION(BlueprintCallable, Category = "ScarletHealthDamage|Health")
	void Revive(float NewHealth);

// Delegates
public:

	// Called when health reaches 0.0 (or goes below it)
	UPROPERTY(BlueprintAssignable, Category = "Delegates")
	FOnDeath OnDeath;

	// Called every time damage is taken
	UPROPERTY(BlueprintAssignable, Category = "Delegates")
	FOnDamageTaken OnDamageTaken;

	// Called every time health changes, Delta is the difference between the new health value and the old one
	// Delta = NewHealth - OldHealth
	UPROPERTY(BlueprintAssignable, Category = "Delegates")
	FOnHealthChanged OnHealthChanged;

	// Called when revived
	UPROPERTY(BlueprintAssignable, Category = "Delegates")
	FOnRevived OnRevived;
};
