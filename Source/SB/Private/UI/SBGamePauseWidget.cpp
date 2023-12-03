// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SBGamePauseWidget.h"
#include "Components/Button.h"
#include "SBGameModeBase.h"
#include "Kismet/GamePlayStatics.h"

void USBGamePauseWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (ResumeButton)
	{
		ResumeButton->OnClicked.AddDynamic(this, &USBGamePauseWidget::ResumeButtonClick);
	}

	if (QuitButton)
	{
		QuitButton->OnClicked.AddDynamic(this, &USBGamePauseWidget::QuitButtonClick);
	}
}

void USBGamePauseWidget::Show()
{
	PlayAnimation(ShowAnimation);
}

void USBGamePauseWidget::ResumeButtonClick()
{
	const auto GameMode = Cast<ASBGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!GameMode) return;

	GameMode->ClearPause();
}

void USBGamePauseWidget::QuitButtonClick()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
}
