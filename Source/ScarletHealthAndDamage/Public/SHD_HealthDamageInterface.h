// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "SHD_DamageType.h"
#include "SHD_HealthComponent.h"

#include "SHD_HealthDamageInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USHD_HealthDamageInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SCARLETHEALTHANDDAMAGE_API ISHD_HealthDamageInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	// Apply damage with Scarlet-Health-And-Damage type
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "ScarletHealthDamage|Interface")
	void SHD_ApplyDamage(float Damage, ESHD_DamageType Type, AActor* Initiator);
	virtual void SHD_ApplyDamage_Implementation(float Damage, ESHD_DamageType Type, AActor* Initiator) {}

	// Attempt to fetch Scarlet-Health-And-Damage health component
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "ScarletHealthDamage|Interface")
	USHD_HealthComponent* SHD_GetHealthComponent();
	virtual USHD_HealthComponent* SHD_GetHealthComponent_Implementation() { return nullptr; }
};
