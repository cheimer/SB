// Fill out your copyright notice in the Description page of Project Settings.


#include "Trigger/SBPlayerTriggerBox.h"
#include "Components/ShapeComponent.h"
#include "Player/SBPlayerCharacter.h"

ASBPlayerTriggerBox::ASBPlayerTriggerBox()
{
	GetCollisionComponent()->OnComponentBeginOverlap.AddDynamic(this, &ASBPlayerTriggerBox::BeginOverlapItem);
	GetCollisionComponent()->OnComponentEndOverlap.AddDynamic(this, &ASBPlayerTriggerBox::EndOverlapItem);
}

void ASBPlayerTriggerBox::BeginOverlapItem(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	const auto Player = Cast<ASBPlayerCharacter>(OtherActor);
	if (Player)
	{
		isPlayer = true;
	}
}

void ASBPlayerTriggerBox::EndOverlapItem(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	const auto Player = Cast<ASBPlayerCharacter>(OtherActor);
	if (Player)
	{
		isPlayer = false;
	}
}
