// Fill out your copyright notice in the Description page of Project Settings.


#include "Trigger/SBItemTriggerBox.h"
#include "Items/SBBasicItem.h"

ASBItemTriggerBox::ASBItemTriggerBox()
{
	GetCollisionComponent()->OnComponentBeginOverlap.AddDynamic(this, &ASBItemTriggerBox::BeginOverlapItem);
	GetCollisionComponent()->OnComponentEndOverlap.AddDynamic(this, &ASBItemTriggerBox::EndOverlapItem);
}

void ASBItemTriggerBox::BeginPlay()
{
	for (FText ItemNameIndex : WantItemNames)
	{
		ItemNum.Add(ItemNameIndex.ToString(), 0);
	}
}

void ASBItemTriggerBox::BeginOverlapItem(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	const auto Item = Cast<ASBBasicItem>(OtherActor);
	if (!Item) return;

	for (FText ItemNameIndex : WantItemNames)
	{
		if (Item->GetItemName().EqualTo(ItemNameIndex))
		{
			ItemNum[ItemNameIndex.ToString()]++;
			break;
		}
	}

}

void ASBItemTriggerBox::EndOverlapItem(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	const auto Item = Cast<ASBBasicItem>(OtherActor);
	if (!Item) return;

	for (FText ItemNameIndex : WantItemNames)
	{
		if (Item->GetItemName().EqualTo(ItemNameIndex))
		{
			ItemNum[ItemNameIndex.ToString()]--;
			break;
		}
	}

}
