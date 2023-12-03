// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SBEnergyComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SB_API USBEnergyComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	USBEnergyComponent();

	void SetEnergy(int32 NewEnergy);
	int32 GetCurrentEnergy() { return CurrentEnergy; }
	int32 GetMaxEnergy() { return MaxEnergy; }

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	int32 MaxEnergy = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	int32 CurrentEnergy;

};
