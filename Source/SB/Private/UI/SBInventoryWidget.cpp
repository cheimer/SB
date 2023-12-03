// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SBInventoryWidget.h"
#include "Components/Button.h"
#include "Components/TileView.h"
#include "SBGameModeBase.h"
#include "Components/SBInventoryComponent.h"
#include "Items/SBBasicItem.h"
#include "UI/SBItemInfoWidget.h"

void USBInventoryWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (CloseButton)
	{
		CloseButton->OnClicked.AddDynamic(this, &USBInventoryWidget::CloseButtonClick);
	}
	if (UseButton)
	{
		UseButton->OnClicked.AddDynamic(this, &USBInventoryWidget::UseButtonClick);
	}
	if (DeleteButton)
	{
		DeleteButton->OnClicked.AddDynamic(this, &USBInventoryWidget::DeleteButtonClick);
	}

	ItemTile->OnItemClicked().AddUObject(this, &USBInventoryWidget::ItemTileItemClicked);
	//ItemTile->OnItemSelectionChanged().AddUObject(this, &USBInventoryWidget::ItemTileItemClicked);
}

void USBInventoryWidget::ToggleWidget()
{
	if (bIsInventoryOpen)
	{
		bIsInventoryOpen = false;
		InventoryClose();
	}
	else
	{
		bIsInventoryOpen = true;
		InventoryOpen();
	}
}

FText USBInventoryWidget::GetItemEffect() const
{
	const auto SelectedItem = Cast<ASBBasicItem>(ItemTile->GetSelectedItem());
	if (!SelectedItem)
	{
		return FText::GetEmpty();
	}
	else
	{
		return SelectedItem->GetItemEffect();
	}
}

FText USBInventoryWidget::GetItemDesc() const
{
	const auto SelectedItem = Cast<ASBBasicItem>(ItemTile->GetSelectedItem());
	if (!SelectedItem)
	{
		return FText::GetEmpty();
	}
	else
	{
		return SelectedItem->GetItemDesc();
	}
}

void USBInventoryWidget::InventoryOpen()
{
	const auto GameMode = Cast<ASBGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!GameMode) return;

	if (!GetWorld()->GetFirstPlayerController()) return;
	GameMode->InventoryOpenPause(GetWorld()->GetFirstPlayerController(), false);

	InventorySetting();
	
}

void USBInventoryWidget::InventoryClose()
{
	const auto GameMode = Cast<ASBGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!GameMode) return;

	GameMode->ClearPause();

	const auto ClickedItem = ItemTile->GetSelectedItem();
	if (ClickedItem)
	{
		const auto ItemWidget = Cast<USBItemInfoWidget>(ItemTile->GetEntryWidgetFromItem(ClickedItem));
		if (ItemWidget)
		{
			ItemWidget->UnClickedWidget();
		}
	}

	ItemTile->ClearSelection();
	ItemTile->ClearListItems();
}

void USBInventoryWidget::InventorySetting()
{
	const auto InvenComp = GetInvenComp();
	if (!InvenComp) return;

	for (int i = 0; InvenComp->GetItem(i); i++)
	{
		ASBBasicItem* Item = InvenComp->GetItem(i);

		ItemTile->AddItem(Item);
	}

	BeforeWidget = nullptr;
}

void USBInventoryWidget::ItemTileItemClicked(UObject* ClickedItem)
{
	if (!ClickedItem) return;

	const auto ItemWidget = Cast<USBItemInfoWidget>(ItemTile->GetEntryWidgetFromItem(ClickedItem));
	if (!ItemWidget) return;

	if (!BeforeWidget)
	{
		ItemWidget->ClickedWidget();
		BeforeWidget = ItemWidget;
	}
	else if (BeforeWidget != ItemWidget)
	{
		BeforeWidget->UnClickedWidget();
		ItemWidget->ClickedWidget();
		BeforeWidget = ItemWidget;
	}

}

void USBInventoryWidget::CloseButtonClick()
{
	bIsInventoryOpen = false;
	InventoryClose();
}

void USBInventoryWidget::UseButtonClick()
{
	const auto SelectedItem = Cast<ASBBasicItem>(ItemTile->GetSelectedItem());
	if (!SelectedItem) return;
	if (!SelectedItem->UseItem())
	{
		return; // UseItemFalse
	}
	RemoveSelectedItem();

	if (SelectedItem->IsCreate())
	{
		CloseButtonClick();
	}
	else
	{
		// empty
	}
}

void USBInventoryWidget::DeleteButtonClick()
{
	RemoveSelectedItem();
}

void USBInventoryWidget::RemoveSelectedItem()
{
	const auto SelectedItem = Cast<ASBBasicItem>(ItemTile->GetSelectedItem());
	if (!SelectedItem) return;

	const auto InvenComp = GetInvenComp();
	if (!InvenComp) return;

	ItemTile->RemoveItem(ItemTile->GetSelectedItem());

	InvenComp->RemoveItem(SelectedItem);
}

USBInventoryComponent* USBInventoryWidget::GetInvenComp()
{
	const auto GameMode = Cast<ASBGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!GameMode) return nullptr;

	const auto Player = GameMode->GetPlayerCharacter();
	if (!Player) return nullptr;

	const auto InvenComp = Cast<USBInventoryComponent>(Player->GetComponentByClass(USBInventoryComponent::StaticClass()));
	if (!InvenComp) return nullptr;

	return InvenComp;
}

