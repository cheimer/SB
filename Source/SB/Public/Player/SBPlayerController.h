// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SBPlayerController.generated.h"

class ASBBasicItem;
class ASBNPCBase;

UCLASS()
class SB_API ASBPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ASBPlayerController();

	virtual void Tick(float DeltaTime) override;

	FText GetNameViewportCenter();
	
	virtual bool InputKey(FKey Key, EInputEvent EventType, float AmountDepressed, bool bGamepad) override;

protected:
	virtual void SetupInputComponent() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectQueries;

private:
	void ClickInput();
	void CreateItem();
	void MapToggle();
	void PauseGame();
	void InventoryToggle();

	ASBBasicItem* GetItemViewportCenter();
	ASBNPCBase* GetNPCViewportCenter();

	bool ViewportCentor(FVector& Start, FVector& End);
};
