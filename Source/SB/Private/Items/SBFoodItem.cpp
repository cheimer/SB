// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/SBFoodItem.h"
#include "SBCoreTypes.h"
#include "Components/SBEnergyComponent.h"
#include "SBGameModeBase.h"


ASBFoodItem::ASBFoodItem()
{
	ItemData.ItemName = FText::FromString("Food TEMP");
	ItemData.ItemType = EItemTypes::Food;
	
	ItemData.Interactable = true;

	ItemData.ContainSize = 5;
	ItemData.Usable = true;
	ItemData.isCreate = false;
}

bool ASBFoodItem::UseItem()
{
	if (!ItemData.Usable)
	{
		return false;
	}

	const auto GameMode = Cast<ASBGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!GameMode) return false;

	const auto Player = GameMode->GetPlayerCharacter();
	if (!Player) return false;

	const auto EnergyComp = Cast<USBEnergyComponent>(Player->GetComponentByClass(USBEnergyComponent::StaticClass()));
	if (!EnergyComp) return false;

	if (EnergyComp->GetCurrentEnergy() == EnergyComp->GetMaxEnergy())
	{
		UE_LOG(LogTemp, Warning, TEXT("Energy FULL"));
		return false;
	}
	else
	{
		EnergyComp->SetEnergy(EnergyComp->GetCurrentEnergy() + EnergyCharge);
		return true;
	}

	return true;
}
