// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SBMapWidget.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "SBGameModeBase.h"
#include "SBCoreTypes.h"


void USBMapWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	const auto GameMode = Cast<ASBGameModeBase>(GetWorld()->GetAuthGameMode());
	MapLenghX = GameMode->MapMaxLocation.X - GameMode->MapMinLocation.X;
	MapLenghY = GameMode->MapMaxLocation.Y - GameMode->MapMinLocation.Y;

	if (CloseButton)
	{
		CloseButton->OnClicked.AddDynamic(this, &USBMapWidget::CloseButtonClick);
	}
}

void USBMapWidget::ToggleWidget()
{
	MapToggle();
}

void USBMapWidget::MapToggle()
{
	if (bIsMapOpen)
	{
		bIsMapOpen = false;
		MapClose();
	}
	else
	{
		bIsMapOpen = true;
		MapOpen();
	}
}

void USBMapWidget::MapOpen()
{
	const auto GameMode = Cast<ASBGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!GameMode) return;

	SetPlayerMarker();
	
	if (!GetWorld()->GetFirstPlayerController()) return;
	GameMode->MapOpenPause(GetWorld()->GetFirstPlayerController(), false);
}

void USBMapWidget::MapClose()
{
	const auto GameMode = Cast<ASBGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!GameMode) return;

	GameMode->ClearPause();
}

void USBMapWidget::CloseButtonClick()
{
	bIsMapOpen = false;
	MapClose();
}

FVector USBMapWidget::GetPlayerLocation() const
{
	const auto PlayerController = GetWorld()->GetFirstPlayerController();
	if (!PlayerController) return FVector::ZeroVector;

	const auto PlayerPawn = PlayerController->GetPawn();
	if (!PlayerPawn) return FVector::ZeroVector;

	return PlayerPawn->GetActorLocation();
}

FRotator USBMapWidget::GetPlayerRotator() const
{
	const auto PlayerController = GetWorld()->GetFirstPlayerController();
	if (!PlayerController) return FRotator::ZeroRotator;

	const auto PlayerPawn = PlayerController->GetPawn();
	if (!PlayerPawn) return FRotator::ZeroRotator;

	return PlayerPawn->GetActorRotation();
}

void USBMapWidget::SetPlayerMarker()
{
	const auto GameMode = Cast<ASBGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!GameMode) return;
	const auto PlayerLocation = GetPlayerLocation();

	float FarFromStartX = -PlayerLocation.X + GameMode->MapMaxLocation.X;
	float FarFromStartY = PlayerLocation.Y - GameMode->MapMinLocation.Y;

	float LenghRateX = FarFromStartX / MapLenghX;
	float LenghRateY = FarFromStartY / MapLenghY;

	float MapXPos = MapImage->Brush.GetImageSize().X * LenghRateX;
	float MapYPos = MapImage->Brush.GetImageSize().Y * LenghRateY;

	const auto PlayerRotator = GetPlayerRotator();
	float PlayerAngle = PlayerRotator.Yaw;

	PlayerMarker->SetPositionInViewport(FVector2D(MapYPos, MapXPos));
	PlayerMarker->SetRenderTranslation(FVector2D(MapYPos, MapXPos));
	PlayerMarker->SetRenderTransformAngle(PlayerAngle);
}
