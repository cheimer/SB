// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/SkeletalMeshActor.h"
#include "SBNPCBase.generated.h"

class USBQuestComponent;

UCLASS()
class SB_API ASBNPCBase : public ASkeletalMeshActor
{
	GENERATED_BODY()
	
public:
	ASBNPCBase();

	FText GetNPCName() { return NPCName; }

	void TalkNPC();


protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	USBQuestComponent* SBQuestComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "NPC")
	FText NPCName;

private:
	bool CanTalk();
	void QuestStart();
	void QuestClear();
	void QuestEnd();
	void QuestNotClear();

	void SetUITalk(FText Talk);
	void ClearUITalk();

	FTimerHandle UITalkTimerHandle;
};
