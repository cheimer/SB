// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SBBaseWidget.generated.h"

/**
 * 
 */
UCLASS()
class SB_API USBBaseWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void Show();
	virtual void BeginBase();
	virtual void ToggleWidget();
};
