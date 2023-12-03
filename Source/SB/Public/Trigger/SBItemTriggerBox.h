// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "SBItemTriggerBox.generated.h"

class ASBBasicItem;

UCLASS()
class SB_API ASBItemTriggerBox : public ATriggerBox
{
	GENERATED_BODY()
	
public:
	ASBItemTriggerBox();

	virtual void BeginPlay() override;

	TMap<FString, int32> ItemNum;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	TArray<FText> WantItemNames;

private:
	UFUNCTION()
	void BeginOverlapItem(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
		bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()	
	void EndOverlapItem(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
