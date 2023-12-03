// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/SBBaseWidget.h"
#include "SBCoreTypes.h"
#include "SBInventoryWidget.generated.h"


class UButton;
class UTileView;
class USBInventoryComponent;
class ASBBasicItem;
class USBItemInfoWidget;

UCLASS()
class SB_API USBInventoryWidget : public USBBaseWidget
{
	GENERATED_BODY()

public:
	virtual void ToggleWidget() override;

protected:
	virtual void NativeOnInitialized() override;

	UFUNCTION(BlueprintCallable, Category = "UI")
	FText GetItemEffect() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
	FText GetItemDesc() const;

	UPROPERTY(meta = (BindWidget))
	UButton* CloseButton;

	UPROPERTY(meta = (BindWidget))
	UButton* UseButton;

	UPROPERTY(meta = (BindWidget))
	UButton* DeleteButton;

	UPROPERTY(meta = (BindWidget))
	UTileView* ItemTile;

private:
	void InventoryOpen();
	void InventoryClose();

	void InventorySetting();

	void ItemTileItemClicked(UObject* ClickedItem);

	USBInventoryComponent* GetInvenComp();

	UFUNCTION()
	void CloseButtonClick();
	UFUNCTION()
	void UseButtonClick();
	UFUNCTION()
	void DeleteButtonClick();

	void RemoveSelectedItem();

	bool bIsInventoryOpen = false;
	USBItemInfoWidget* BeforeWidget = nullptr;
};
