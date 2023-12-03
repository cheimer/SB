// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SBItemInfoWidget.h"
#include "UI/SBInventoryWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Items/SBBasicItem.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "SBCoreTypes.h"

void USBItemInfoWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);
	
	ASBBasicItem* InputItem = Cast<ASBBasicItem>(ListItemObject);
	if (!InputItem) return;

	ItemName->SetText(InputItem->GetItemName());
	Item = InputItem;
}

void USBItemInfoWidget::ClickedWidget()
{
	ItemImage->SetColorAndOpacity(FLinearColor::Blue);
}

void USBItemInfoWidget::UnClickedWidget()
{
	ItemImage->SetColorAndOpacity(FLinearColor::White);
}