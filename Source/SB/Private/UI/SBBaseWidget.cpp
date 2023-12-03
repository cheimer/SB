// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SBBaseWidget.h"

void USBBaseWidget::Show()
{

}

void USBBaseWidget::BeginBase()
{
	const auto PlayerController = GetWorld()->GetFirstPlayerController();
	if (!PlayerController) return;

	PlayerController->bShowMouseCursor = true;
	PlayerController->SetInputMode(FInputModeUIOnly::FInputModeUIOnly());
}

void USBBaseWidget::ToggleWidget()
{

}
