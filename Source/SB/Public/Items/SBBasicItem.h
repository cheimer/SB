// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/CapsuleComponent.h"
#include "SBCoreTypes.h"
#include "SBBasicItem.generated.h"

UCLASS()
class SB_API ASBBasicItem : public AActor
{
	GENERATED_BODY()
	
public:	
	ASBBasicItem();

	virtual void Tick(float DeltaTime) override;

	virtual void Interact();

	int32 GetItemSize() { return ItemData.ContainSize; }

	virtual bool UseItem();

	FText GetItemName() { return ItemData.ItemName; }
	FText GetItemEffect() { return ItemData.ItemEffect; }
	FText GetItemDesc() { return ItemData.ItemDesc; }

	bool IsCreate() { return ItemData.isCreate; }

	void SetVisible(bool isVisible);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	UCapsuleComponent* CapsuleComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Tick")
	float TickInterval = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FItemData ItemData;

	virtual void BeginPlay() override;

	bool CanInteract();

private:
	void Visible();
	void Invisible();
};
