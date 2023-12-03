// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/SBBaseWidget.h"
#include "SBFieldWidget.generated.h"

class UTextBlock;

UCLASS()
class SB_API USBFieldWidget : public USBBaseWidget
{
	GENERATED_BODY()
	
public:
	virtual void BeginBase() override;

	UFUNCTION(BlueprintCallable, Category = "UI")
	int32 GetInventoryRemain() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
	int32 GetInventoryMax() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
	int32 GetEnergyRemain() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
	int32 GetEnergyMax() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
	FText GetItemName() const;

	void SetNPCTalk(FText NewTalk);

protected:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* NPCTalk;
};
