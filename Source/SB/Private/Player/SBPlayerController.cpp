// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/SBPlayerController.h"
#include "Player/SBPlayerCharacter.h"
#include "SBGameModeBase.h"
#include "Items/SBBasicItem.h"
#include "Items/SBCreatableItem.h"
#include "NPC/SBNPCBase.h"
#include "UI/SBGameHUD.h"
#include "UI/SBBaseWidget.h"
#include "UI/SBBaseWidget.h"
#include "SBCoreTypes.h"
	
ASBPlayerController::ASBPlayerController()
{

}

void ASBPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("Click", IE_Pressed, this, &ASBPlayerController::ClickInput);
	InputComponent->BindAction("Pause", IE_Pressed, this, &ASBPlayerController::PauseGame).bExecuteWhenPaused = true;
	InputComponent->BindAction("Map", IE_Pressed, this, &ASBPlayerController::MapToggle);
	InputComponent->BindAction("Inventory", IE_Pressed, this, &ASBPlayerController::InventoryToggle);
	InputComponent->BindAction("Create", IE_Pressed, this, &ASBPlayerController::CreateItem);

	//bExecuteWhenPaused 안됨
}

void ASBPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool ASBPlayerController::InputKey(FKey Key, EInputEvent EventType, float AmountDepressed, bool bGamepad)
{
	const auto PlayerCharacter = Cast<ASBPlayerCharacter>(GetPawn());
	if (!PlayerCharacter) return false;

	if (PlayerCharacter->GetPlayerState() == EPlayerState::Normal)
	{
		Super::InputKey(Key, EventType, AmountDepressed, bGamepad);
		return true;
	}
	else if (PlayerCharacter->GetPlayerState() == EPlayerState::Creater)
	{
		FKey KeyI("I"), KeyM("M"), KeyLM("LeftMouseButton");
		TArray<FKey> KeyArray;
		KeyArray.Add(KeyI); KeyArray.Add(KeyM); KeyArray.Add(KeyLM);

		for (FKey KeyIndex : KeyArray)
		{
			if (Key.GetFName() == KeyIndex.GetFName())
				return true;
		}

		Super::InputKey(Key, EventType, AmountDepressed, bGamepad);
		return true;
	}

	return false;
}

void ASBPlayerController::ClickInput()
{
	const auto HitItem = GetItemViewportCenter();
	if (HitItem)
	{
		HitItem->Interact();
	}

	const auto HitNPC = GetNPCViewportCenter();
	if (HitNPC)
	{
		HitNPC->TalkNPC();
	}

}

void ASBPlayerController::CreateItem()
{
	const auto PlayerCharacter = Cast<ASBPlayerCharacter>(GetPawn());
	if (!PlayerCharacter) return;

	TArray<AActor*> AttachedArray;
	PlayerCharacter->GetAttachedActors(AttachedArray);

	for (AActor* AttachedIndex : AttachedArray)
	{
		ASBCreatableItem* Item = Cast<ASBCreatableItem>(AttachedIndex);
		if (Item)
		{
			Item->DropItem();
			return;
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("Create Item No Item"));
}

FText ASBPlayerController::GetNameViewportCenter()
{
	const auto HitItem = GetItemViewportCenter();
	if (HitItem)
	{
		return HitItem->GetItemName();
	}
	
	const auto HitNPC = GetNPCViewportCenter();
	if (HitNPC)
	{
		return HitNPC->GetNPCName();
	}

	return FText::GetEmpty();
}

ASBBasicItem* ASBPlayerController::GetItemViewportCenter()
{
	FHitResult Hit;
	FVector StartVec, EndVec;

	if (!ViewportCentor(StartVec, EndVec)) return nullptr;

	GetWorld()->LineTraceSingleByObjectType(Hit, StartVec, EndVec, ObjectQueries);

	return Cast<ASBBasicItem>(Hit.GetActor());
}

ASBNPCBase* ASBPlayerController::GetNPCViewportCenter()
{
	FHitResult Hit;
	FVector StartVec, EndVec;

	if (!ViewportCentor(StartVec, EndVec)) return nullptr;

	GetWorld()->LineTraceSingleByObjectType(Hit, StartVec, EndVec, ObjectQueries);

	return Cast<ASBNPCBase>(Hit.GetActor());
}

bool ASBPlayerController::ViewportCentor(FVector& Start, FVector& End)
{
	FVector2D ViewportSize;
	if (!GEngine || !GEngine->GameViewport) return false;

	GEngine->GameViewport->GetViewportSize(ViewportSize);
	FVector2D ScreenCenter = ViewportSize * 0.5f;

	FVector WorldLocation, WorldDirection;

	DeprojectScreenPositionToWorld(ScreenCenter.X, ScreenCenter.Y, WorldLocation, WorldDirection);

	const auto PlayerCharacter = Cast<ASBPlayerCharacter>(GetPawn());
	if (!PlayerCharacter) return false;
	
	Start = WorldLocation;
	End = WorldLocation + WorldDirection * PlayerCharacter->GetSearchLength();

	return true;
}

void ASBPlayerController::MapToggle()
{
	const auto GameHUD = Cast<ASBGameHUD>(GetHUD());
	if (!GameHUD) return;

	const auto MapWidget = GameHUD->GetWidget(EScreenMode::Map);
	if (!MapWidget) return;

	MapWidget->ToggleWidget();
}

void ASBPlayerController::InventoryToggle()
{
	const auto GameHUD = Cast<ASBGameHUD>(GetHUD());
	if (!GameHUD) return;

	const auto InventoryWidget = GameHUD->GetWidget(EScreenMode::Inventory);
	if (!InventoryWidget) return;

	InventoryWidget->ToggleWidget();
}

void ASBPlayerController::PauseGame()
{
	const auto GameMode = Cast<ASBGameModeBase>(GetWorld()->GetAuthGameMode());

	//executeWhenPaused -> 안됨
	GameMode->SetPause(this, false);
}
