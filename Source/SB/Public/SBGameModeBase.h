// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UI/SBGameHUD.h"
#include "SBCoreTypes.h"
#include "SBGameModeBase.generated.h"

class ASBPlayerCharacter;
class ASBNPCBase;

UCLASS()
class SB_API ASBGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	FOnModeChangedSignature OnModeChangedSignature;

	ASBGameModeBase();

	void SetPlayerCharacter(AActor* SetPlayer);
	AActor* GetPlayerCharacter();
	void ChangeMode(EScreenMode NewMode);

	virtual bool SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate) override;
	virtual bool ClearPause() override;

	bool MapOpenPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate);
	bool InventoryOpenPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate);
	

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Map")
	FVector2D MapMinLocation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Map")
	FVector2D MapMaxLocation;

private:
	ASBPlayerCharacter* PlayerCharacter = nullptr;

};
