// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC/SBNPCBase.h"
#include "Components/SBQuestComponent.h"
#include "SBGameModeBase.h"
#include "Player/SBPlayerCharacter.h"
#include "SBCoreTypes.h"
#include "UI/SBFieldWidget.h"

ASBNPCBase::ASBNPCBase()
{
	GetSkeletalMeshComponent()->SetAnimationMode(EAnimationMode::AnimationSingleNode);
	SBQuestComponent = CreateDefaultSubobject<USBQuestComponent>("QuestComponent");

	GetSkeletalMeshComponent()->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel2); // NPC

}

void ASBNPCBase::BeginPlay()
{
	Super::BeginPlay();

	if (NPCName.EqualTo(FText::GetEmpty()))
	{
		UE_LOG(LogTemp, Warning, TEXT("NPC Name is Empty"));
	}
}

void ASBNPCBase::TalkNPC()
{
	if (!CanTalk())
	{
		return;
	}
	else
	{
		if (!SBQuestComponent->QuestData.isStart) // 시작 안함
		{
			QuestStart();
		}
		else if (!SBQuestComponent->QuestData.isEnd) // 끝나지 않음
		{
			if (SBQuestComponent->IsClearQuest()) // 퀘스트 깸
			{
				QuestClear();
			}
			else // 퀘스트 못깸
			{
				QuestNotClear();
			}
		}
		else if (SBQuestComponent->QuestData.isEnd) // 퀘스트 끝
		{
			QuestEnd();
		}

	}
}

void ASBNPCBase::QuestStart()
{
	SBQuestComponent->QuestData.isStart = true;
	FText QuestText = SBQuestComponent->GetQuestText();
	SetUITalk(QuestText);
}

void ASBNPCBase::QuestClear()
{
	SBQuestComponent->QuestData.isEnd = true;
	SBQuestComponent->QuestReward();
	SetUITalk(FText::FromString("Quest Clear"));

}

void ASBNPCBase::QuestNotClear()
{
	FText QuestProgress = SBQuestComponent->GetQuestProgress();
	SetUITalk(QuestProgress);
}

void ASBNPCBase::QuestEnd()
{
	if (SBQuestComponent->QuestData.isLoop)
	{
		SBQuestComponent->QuestData.isStart = false;
		SBQuestComponent->QuestData.isEnd = false;

		SetUITalk(FText::FromString("Quest Restart"));
	}
	else
	{
		SetUITalk(FText::FromString("Quest Clear"));

	}

}

bool ASBNPCBase::CanTalk()
{
	const auto GameMode = Cast<ASBGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!GameMode) return false;

	const auto Player = Cast<ASBPlayerCharacter>(GameMode->GetPlayerCharacter());
	if (!Player) return false;

	FVector PlayerLocation = Player->GetActorLocation();
	FVector NPCLocation = GetActorLocation();

	float Distance = FVector::Distance(PlayerLocation, NPCLocation);

	if (Distance > Player->GetInteractLength())
	{
		return false;
	}
	else
	{
		return true;
	}
}

void ASBNPCBase::SetUITalk(FText Talk)
{
	const auto PlayerController = GetWorld()->GetFirstPlayerController();
	if (!PlayerController) return;

	const auto GameHUD = Cast<ASBGameHUD>(PlayerController->GetHUD());
	if (!GameHUD) return;

	const auto FieldWidget = Cast<USBFieldWidget>(GameHUD->GetWidget(EScreenMode::Field));
	if (!FieldWidget) return;

	FieldWidget->SetNPCTalk(Talk);

	GetWorldTimerManager().SetTimer(UITalkTimerHandle, this, &ASBNPCBase::ClearUITalk, 2.5f, false);
}

void ASBNPCBase::ClearUITalk()
{
	const auto PlayerController = GetWorld()->GetFirstPlayerController();
	if (!PlayerController) return;

	const auto GameHUD = Cast<ASBGameHUD>(PlayerController->GetHUD());
	if (!GameHUD) return;

	const auto FieldWidget = Cast<USBFieldWidget>(GameHUD->GetWidget(EScreenMode::Field));
	if (!FieldWidget) return;

	FieldWidget->SetNPCTalk(FText::GetEmpty());

	GetWorldTimerManager().ClearTimer(UITalkTimerHandle);
}