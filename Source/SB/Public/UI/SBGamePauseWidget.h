// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/SBBaseWidget.h"
#include "SBGamePauseWidget.generated.h"

class UButton;
class UWidgetAnimation;

UCLASS()
class SB_API USBGamePauseWidget : public USBBaseWidget
{
	GENERATED_BODY()
	
public:
	virtual void Show() override;

protected:
	virtual void NativeOnInitialized() override;

	UPROPERTY(meta = (BindWidget))
	UButton* ResumeButton;

	UPROPERTY(meta = (BindWidget))
	UButton* QuitButton;

	UPROPERTY(meta = (BindWidgetAnim), transient)
	UWidgetAnimation* ShowAnimation;

private:
	UFUNCTION()
	void ResumeButtonClick();

	UFUNCTION()
	void QuitButtonClick();

};
