// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SBInventoryComponent.generated.h"

class ASBBasicItem;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SB_API USBInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USBInventoryComponent();

	float GetCurrentSize() { return CurrentSize; }
	float GetMaxSize() { return MaxSize; }

	void AddItem(ASBBasicItem* Item);
	void RemoveItem(ASBBasicItem* Item);
	void UseItem(int32 ItemIndex);
	void InventorySizeUp(int32 AddSize) { MaxSize += AddSize; }

	ASBBasicItem* GetItem(int32 ItemIndex) const;
	int32 GetItemNum() { return ItemNum; }

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	int32 MaxSize = 20;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	int32 CurrentSize = 0;

private:
	TArray<ASBBasicItem*> Inventory;

	int32 ItemNum = 0;
	//TArray<ASBBasicItem*> ItemIndexStorage;
};
