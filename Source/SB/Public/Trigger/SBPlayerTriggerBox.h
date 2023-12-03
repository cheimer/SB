// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "SBPlayerTriggerBox.generated.h"


UCLASS()
class SB_API ASBPlayerTriggerBox : public ATriggerBox
{
	GENERATED_BODY()

public:
	ASBPlayerTriggerBox();

	UFUNCTION(BlueprintCallable)
	bool IsPlayerHere() { return isPlayer; }

private:
	UFUNCTION()
	void BeginOverlapItem(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void EndOverlapItem(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	bool isPlayer = false;
};
