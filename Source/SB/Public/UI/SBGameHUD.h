// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SBCoreTypes.h"
#include "SBGameHUD.generated.h"

class USBBaseWidget;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnModeChangedSignature, EScreenMode);

UCLASS()
class SB_API ASBGameHUD : public AHUD
{
	GENERATED_BODY()

public:
	USBBaseWidget* GetWidget(EScreenMode GetMode);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> FieldWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> InventoryWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> MapWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> GamePauseWidgetClass;

	virtual void BeginPlay() override;

private:
	UPROPERTY()
	TMap<EScreenMode, USBBaseWidget*> Widgets;

	UPROPERTY()
	USBBaseWidget* CurrentWidget = nullptr;

	void ChangeMode(EScreenMode NewMode);
};
