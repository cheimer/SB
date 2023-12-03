// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/SBBasicItem.h"
#include "SBCreatableItem.generated.h"

/**
 * 
 */
UCLASS()
class SB_API ASBCreatableItem : public ASBBasicItem
{
	GENERATED_BODY()
	
public:
	ASBCreatableItem();

	virtual bool UseItem() override;

	void DropItem();
	void SetPhysicSimul(bool isSet) { CapsuleComponent->SetSimulatePhysics(isSet); }

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Spawn")
	bool isPhysicSimulate = true;

private:
	void CreateItemWorld();

	UPROPERTY(EditAnywhere, Category = "Item")
	int32 EnergyUse = 0;

	UPROPERTY(EditAnywhere, Category = "Spawn")
	float SpawnDistance = 200.0f;
};
