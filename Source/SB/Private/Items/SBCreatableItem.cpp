// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/SBCreatableItem.h"
#include "SBCoreTypes.h"
#include "SBGameModeBase.h"
#include "Components/SBEnergyComponent.h"
#include "Player/SBPlayerCharacter.h"


ASBCreatableItem::ASBCreatableItem()
{
	ItemData.ItemName = FText::FromString("Create TEMP");
	ItemData.ItemType = EItemTypes::Creatable;

	ItemData.Interactable = true;

	ItemData.ContainSize = 1;
	ItemData.Usable = true;
	ItemData.isCreate = true;

	if (isPhysicSimulate)
	{
		CapsuleComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		SetPhysicSimul(isPhysicSimulate);
	}
}

bool ASBCreatableItem::UseItem()
{
	if (!ItemData.Usable)
	{
		return false;
	}

	const auto GameMode = Cast<ASBGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!GameMode) return false;

	const auto Player = GameMode->GetPlayerCharacter();
	if (!Player) return false;

	const auto EnergyComp = Cast<USBEnergyComponent>(Player->GetComponentByClass(USBEnergyComponent::StaticClass()));
	if (!EnergyComp) return false;

	if (EnergyComp->GetCurrentEnergy() < EnergyUse)
	{
		UE_LOG(LogTemp, Warning, TEXT("Not Energy"));
		return false;
	}
	else
	{
		EnergyComp->SetEnergy(EnergyComp->GetCurrentEnergy() - EnergyUse);
		CreateItemWorld();

		return true;
	}

	return true;
}

void ASBCreatableItem::CreateItemWorld()
{
	const auto GameMode = Cast<ASBGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!GameMode) return;

	const auto Player = Cast<ASBPlayerCharacter>(GameMode->GetPlayerCharacter());
	if (!Player) return;

	const auto PlayerTransform = Player->GetTransform();
	FVector PlayerForward = PlayerTransform.GetLocation() + Player->GetActorForwardVector() * SpawnDistance;

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	AActor* SpawnedItem = GetWorld()->SpawnActor<AActor>(GetClass(), PlayerForward, PlayerTransform.GetRotation().Rotator(), SpawnParameters);
	if (SpawnedItem)
	{
		ASBCreatableItem* SpawnedBasic = Cast<ASBCreatableItem>(SpawnedItem);
		SpawnedBasic->SetVisible(false);

		if (SpawnedBasic->isPhysicSimulate)
		{
			SpawnedBasic->SetPhysicSimul(false);
		}
		SpawnedBasic->AttachToActor(Player, FAttachmentTransformRules::KeepWorldTransform);
		Player->SetPlayerState(EPlayerState::Creater);
	}
}

void ASBCreatableItem::DropItem()
{
	const auto GameMode = Cast<ASBGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!GameMode) return;

	const auto Player = Cast<ASBPlayerCharacter>(GameMode->GetPlayerCharacter());
	if (!Player) return;

	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	Player->SetPlayerState(EPlayerState::Normal);

	if (isPhysicSimulate)
	{
		SetPhysicSimul(true);
	}
}
