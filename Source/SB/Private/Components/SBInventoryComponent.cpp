// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/SBInventoryComponent.h"
#include "Items/SBBasicItem.h"

USBInventoryComponent::USBInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void USBInventoryComponent::BeginPlay()
{
	Super::BeginPlay();


}

void USBInventoryComponent::AddItem(ASBBasicItem* Item)
{
	if (Item->GetItemSize() + CurrentSize > MaxSize)
	{
		UE_LOG(LogTemp, Warning, TEXT("TEMP Inventory is Full"));
		return;
	}
	else
	{
		ASBBasicItem* NewItem = DuplicateObject<ASBBasicItem>(Item, Item->GetOuter());

		Inventory.Add(NewItem);
		CurrentSize += NewItem->GetItemSize();
		ItemNum++;

		Item->Destroy();
	}
}

void USBInventoryComponent::RemoveItem(ASBBasicItem* Item)
{
	Inventory.Remove(Item);
	CurrentSize -= Item->GetItemSize();
	ItemNum--;
}

void USBInventoryComponent::UseItem(int32 ItemIndex)
{
	const auto Item = Inventory[ItemIndex];
	Item->UseItem();
	CurrentSize -= Item->GetItemSize();
	ItemNum--;
}

ASBBasicItem* USBInventoryComponent::GetItem(int32 ItemIndex) const
{
	if (ItemIndex >= ItemNum)
	{
		return nullptr;
	}
	else
	{
		return Inventory[ItemIndex];
	}
}