// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/SBQuestComponent.h"
#include "SBGameModeBase.h"
#include "Player/SBPlayerCharacter.h"
#include "Components/SBInventoryComponent.h"
#include "Items/SBBasicItem.h"
#include "Trigger/SBItemTriggerBox.h"
#include "Engine/World.h"

USBQuestComponent::USBQuestComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void USBQuestComponent::BeginPlay()
{
	Super::BeginPlay();

}

bool USBQuestComponent::IsClearQuest()
{
	if (CheckQuestProgress())
	{
		return true;
	}
	else
	{
		return false;
	}
}

FText USBQuestComponent::GetQuestProgress()
{ 
	if (QuestData.QuestType == EQuestTypes::ItemFind)
	{
		FString Str(QuestData.ItemName.ToString());
		Str.Append(" Not Find");

		return FText::FromString(Str);
	}
	else if (QuestData.QuestType == EQuestTypes::ItemRequire)
	{
		FString Str(QuestData.ItemName.ToString());
		Str.Append(" Not Enough");

		return FText::FromString(Str);
	}

	return FText::GetEmpty();
}

FText USBQuestComponent::GetQuestText()
{
	return QuestData.QuestText;
}

void USBQuestComponent::QuestReward()
{
	const auto GameMode = Cast<ASBGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!GameMode) return;

	const auto Player = Cast<ASBPlayerCharacter>(GameMode->GetPlayerCharacter());
	if (!Player) return;

	auto InvenComp = Cast<USBInventoryComponent>(Player->GetComponentByClass(USBInventoryComponent::StaticClass()));
	if (!InvenComp) return;

	InvenComp->InventorySizeUp(5);
}

bool USBQuestComponent::CheckQuestProgress()
{
	if (QuestData.QuestType == EQuestTypes::ItemFind)
	{
		return CheckItemFind();
	}
	else if (QuestData.QuestType == EQuestTypes::ItemRequire)
	{
		return CheckItemRquire();
	}

	return false;
}

bool USBQuestComponent::CheckItemFind()
{
	const auto GameMode = Cast<ASBGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!GameMode) return false;

	const auto Player = Cast<ASBPlayerCharacter>(GameMode->GetPlayerCharacter());
	if (!Player) return false;

	auto InvenComp = Cast<USBInventoryComponent>(Player->GetComponentByClass(USBInventoryComponent::StaticClass()));
	if (!InvenComp) return false;

	int ItemNum = 0;
	for (int i = 0; i < InvenComp->GetItemNum(); i++)
	{
		auto Item = InvenComp->GetItem(i);
		if (!Item) break;

		if (Item->GetItemName().EqualTo(QuestData.ItemName))
		{
			ItemNum++;
		}
	}

	if (ItemNum >= QuestData.ItemNum)
	{
		return true;
	}

	return false;
}

bool USBQuestComponent::CheckItemRquire()
{
	if (QuestItemTrigger->ItemNum.Find(QuestData.ItemName.ToString()))
	{
		if (QuestItemTrigger->ItemNum[QuestData.ItemName.ToString()] >= QuestData.ItemNum)
		{
			return true;
		}
	}

	return false;
}
