// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SHD_HealthComponent.h"
#include "SHD_RegenHealthComponent.generated.h"

/**
 * 
 */
UCLASS( ClassGroup = (Custom), meta = (BlueprintSpawnableComponent, Blueprintable) )
class SCARLETHEALTHANDDAMAGE_API USHD_RegenHealthComponent : public USHD_HealthComponent
{
	GENERATED_BODY()
	
protected:

	// Current value of regeneration timer
	float RegenerationTimer = 0.0f;

public:

	// Time (in seconds) that has to pass after last damage application before regeneration starts
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Default")
	float RegenerationTimeout = 5.f;

	// Amount of health points that regenerate every second (when regeneration is active)
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Default")
	float RegenerationRate = 1.f;


protected:

	// Called when the game starts
	virtual void BeginPlay() override;

	// Subscribed to OnDamageTaken and OnRevived
	UFUNCTION()
	void ResetTimer(float Damage, ESHD_DamageType Type, AActor* Initiator);


public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Whether health is currently regenerating
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "ScarletHealthDamage|Health|Regeneration")
	bool IsRegenerationActive();
};
