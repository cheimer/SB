// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/SBEnergyComponent.h"

USBEnergyComponent::USBEnergyComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void USBEnergyComponent::BeginPlay()
{
	Super::BeginPlay();

	SetEnergy(MaxEnergy - 50);
}

void USBEnergyComponent::SetEnergy(int32 NewEnergy)
{
	CurrentEnergy = FMath::Clamp(NewEnergy, 0, 100);
}
