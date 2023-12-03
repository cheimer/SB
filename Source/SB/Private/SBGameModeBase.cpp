// Copyright Epic Games, Inc. All Rights Reserved.


#include "SBGameModeBase.h"
#include "SBPlayerCharacter.h"
#include "SBPlayerController.h"
#include "NPC/SBNPCBase.h"
#include "SBCoreTypes.h"

ASBGameModeBase::ASBGameModeBase()
{
	DefaultPawnClass = ASBPlayerCharacter::StaticClass();
	PlayerControllerClass = ASBPlayerController::StaticClass();
}

void ASBGameModeBase::SetPlayerCharacter(AActor* SetPlayer)
{
	const auto PlayerCasting = Cast<ASBPlayerCharacter>(SetPlayer);
	if (!PlayerCasting) return;
	PlayerCharacter = PlayerCasting;

}

AActor* ASBGameModeBase::GetPlayerCharacter()
{
	return PlayerCharacter;
}

void ASBGameModeBase::ChangeMode(EScreenMode NewMode)
{
	OnModeChangedSignature.Broadcast(NewMode);
}

bool ASBGameModeBase::SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate)
{
	bool IsPause = Super::SetPause(PC, CanUnpauseDelegate);

	if (IsPause)
	{
		ChangeMode(EScreenMode::GamePause);
	}

	return IsPause;
}

bool ASBGameModeBase::ClearPause()
{
	bool IsPause = Super::ClearPause();

	if (IsPause)
	{
		ChangeMode(EScreenMode::Field);
	}

	return IsPause;
}

bool ASBGameModeBase::MapOpenPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate)
{
	bool IsPause = SetPause(PC, CanUnpauseDelegate);

	if (IsPause)
	{
		ChangeMode(EScreenMode::Map);
	}

	return IsPause;
}

bool ASBGameModeBase::InventoryOpenPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate)
{
	bool IsPause = SetPause(PC, CanUnpauseDelegate);

	if (IsPause)
	{
		ChangeMode(EScreenMode::Inventory);
	}

	return IsPause;
}