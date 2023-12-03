// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/SBShowItem.h"


ASBShowItem::ASBShowItem()
{
	ItemData.ItemName = FText::FromString("Show TEMP");
	ItemData.ItemType = EItemTypes::Show;

	ItemData.Interactable = false;
	ItemData.Usable = false;
}