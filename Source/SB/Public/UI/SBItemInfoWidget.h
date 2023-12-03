// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/SBBaseWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "SBItemInfoWidget.generated.h"

class ASBBasicItem;
class UTextBlock;
class UImage;

UCLASS()
class SB_API USBItemInfoWidget : public USBBaseWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
	
public:
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

	void ClickedWidget();
	void UnClickedWidget();

protected:
	UPROPERTY(meta = (BindWidget))
	UImage* ItemImage;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ItemName;

private:
	ASBBasicItem* Item;

};
