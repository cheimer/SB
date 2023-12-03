// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/SBBasicItem.h"
#include "SBFoodItem.generated.h"


UCLASS()
class SB_API ASBFoodItem : public ASBBasicItem
{
	GENERATED_BODY()

public:
	ASBFoodItem();

	virtual bool UseItem() override;

private:
	UPROPERTY(EditAnywhere, Category = "Item")
	int32 EnergyCharge = 0;
};
