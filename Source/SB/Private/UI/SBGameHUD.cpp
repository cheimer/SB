// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SBGameHUD.h"
#include "SBCoreTypes.h"
#include "UI/SBBaseWidget.h"
#include "SBGameModeBase.h"


void ASBGameHUD::BeginPlay() 
{
	Super::BeginPlay();

	Widgets.Add(EScreenMode::Field, CreateWidget<USBBaseWidget>(GetWorld(), FieldWidgetClass));
	Widgets.Add(EScreenMode::Inventory, CreateWidget<USBBaseWidget>(GetWorld(), InventoryWidgetClass));
	Widgets.Add(EScreenMode::Map, CreateWidget<USBBaseWidget>(GetWorld(), MapWidgetClass));
	Widgets.Add(EScreenMode::GamePause, CreateWidget<USBBaseWidget>(GetWorld(), GamePauseWidgetClass));

	for (auto WidgetPair : Widgets)
	{
		const auto WidgetMode = WidgetPair.Value;
		if (!WidgetMode) continue;

		WidgetMode->AddToViewport();
		WidgetMode->SetVisibility(ESlateVisibility::Hidden);
	}

	if (GetWorld())
	{
		const auto GameMode = Cast<ASBGameModeBase>(GetWorld()->GetAuthGameMode());
		if (GameMode)
		{
			GameMode->OnModeChangedSignature.AddUObject(this, &ASBGameHUD::ChangeMode);
		}
	}
	ChangeMode(EScreenMode::Field);

}

void ASBGameHUD::ChangeMode(EScreenMode NewMode)
{
	if (CurrentWidget)
	{
		CurrentWidget->SetVisibility(ESlateVisibility::Hidden);
	}
	if (Widgets.Contains(NewMode))
	{
		CurrentWidget = Widgets[NewMode];
	}
	if (CurrentWidget)
	{
		CurrentWidget->SetVisibility(ESlateVisibility::Visible);
		CurrentWidget->Show();
		CurrentWidget->BeginBase();
	}
}

USBBaseWidget* ASBGameHUD::GetWidget(EScreenMode GetMode)
{
	if (Widgets.Find(GetMode))
		return Widgets[GetMode];
	else
		return nullptr;
}
