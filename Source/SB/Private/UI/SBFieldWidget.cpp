// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SBFieldWidget.h"
#include "Components/SBInventoryComponent.h"
#include "Components/SBEnergyComponent.h"
#include "Components/TextBlock.h"
#include "Player/SBPlayerController.h"

void USBFieldWidget::BeginBase()
{
	const auto PlayerController = GetWorld()->GetFirstPlayerController();
	if (!PlayerController) return;

	PlayerController->bShowMouseCursor = false;
	PlayerController->SetInputMode(FInputModeGameOnly::FInputModeGameOnly());

	NPCTalk->SetText(FText::GetEmpty());
}

int32 USBFieldWidget::GetInventoryRemain() const
{
	const auto Player = GetOwningPlayerPawn();
	if (!Player) return -1;

	const auto InventoryComp = Player->FindComponentByClass<USBInventoryComponent>();
	if (!InventoryComp) return -1;

	return InventoryComp->GetCurrentSize();
}

int32 USBFieldWidget::GetInventoryMax() const
{
	const auto Player = GetOwningPlayerPawn();
	if (!Player) return -1;

	const auto InventoryComp = Player->FindComponentByClass<USBInventoryComponent>();
	if (!InventoryComp) return -1;

	return InventoryComp->GetMaxSize();
}

int32 USBFieldWidget::GetEnergyRemain() const
{
	const auto Player = GetOwningPlayerPawn();
	if (!Player) return -1;

	const auto EnergyComp = Player->FindComponentByClass<USBEnergyComponent>();
	if (!EnergyComp) return -1;

	return EnergyComp->GetCurrentEnergy();
}

int32 USBFieldWidget::GetEnergyMax() const
{
	const auto Player = GetOwningPlayerPawn();
	if (!Player) return -1;

	const auto EnergyComp = Player->FindComponentByClass<USBEnergyComponent>();
	if (!EnergyComp) return -1;

	return EnergyComp->GetMaxEnergy();
}

FText USBFieldWidget::GetItemName() const
{
	const auto Player = GetOwningPlayerPawn();
	if (!Player) return FText::GetEmpty();

	const auto PlayerController = Cast<ASBPlayerController>(Player->GetController());

	return PlayerController->GetNameViewportCenter();
}

void USBFieldWidget::SetNPCTalk(FText NewTalk)
{
	NPCTalk->SetText(NewTalk);
}
