// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SBCoreTypes.h"
#include "SBQuestComponent.generated.h"

class ASBItemTriggerBox;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SB_API USBQuestComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USBQuestComponent();

	bool IsClearQuest();
	FText GetQuestProgress();
	FText GetQuestText();
	void QuestReward();

	UPROPERTY(EditAnywhere, Category = "Quest")
	FQuestData QuestData;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Quest")
	ASBItemTriggerBox* QuestItemTrigger;

private:
	bool CheckQuestProgress();
	bool CheckItemFind();
	bool CheckItemRquire();

};
