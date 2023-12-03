// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/SBBaseWidget.h"
#include "SBMapWidget.generated.h"

class UImage;
class UButton;

UCLASS()
class SB_API USBMapWidget : public USBBaseWidget
{
	GENERATED_BODY()
	
public:
	virtual void ToggleWidget() override;

protected:
	virtual void NativeOnInitialized() override;

	UPROPERTY(meta = (BindWidget))
	UImage* MapImage;

	UPROPERTY(meta = (BindWidget))
	UUserWidget* PlayerMarker;

	UPROPERTY(meta = (BindWidget))
	UButton* CloseButton;

private:
	FVector GetPlayerLocation() const;
	FRotator GetPlayerRotator() const;

	void SetPlayerMarker();

	void MapToggle();
	void MapOpen();
	void MapClose();

	UFUNCTION()
	void CloseButtonClick();

	float MapLenghX;
	float MapLenghY;

	bool bIsMapOpen = false;
};
