// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/SBBasicItem.h"
#include "SBGameModeBase.h"
#include "Player/SBPlayerCharacter.h"
#include "Components/SBInventoryComponent.h"

ASBBasicItem::ASBBasicItem()
{
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>("CapsuleComponent");
	RootComponent = CapsuleComponent;
	CapsuleComponent->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel1); // Item

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	StaticMeshComponent->SetupAttachment(CapsuleComponent);
	StaticMeshComponent->SetGenerateOverlapEvents(false);
}

void ASBBasicItem::BeginPlay()
{
	Super::BeginPlay();
	
	SetActorTickInterval(TickInterval);

	if (ItemData.ItemName.IsEmpty())
	{
		UE_LOG(LogTemp, Error, TEXT("%s IS NOT SETTING"), *(this->GetName()));
	}
}

void ASBBasicItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASBBasicItem::Interact()
{
	if (!CanInteract())
	{
		return;
	}
	else
	{
		const auto GameMode = Cast<ASBGameModeBase>(GetWorld()->GetAuthGameMode());
		if (!GameMode) return;

		const auto Player = Cast<ASBPlayerCharacter>(GameMode->GetPlayerCharacter());
		if (!Player) return;

		const auto InvenComp = Cast<USBInventoryComponent>(Player->GetComponentByClass(USBInventoryComponent::StaticClass()));
		if (!InvenComp) return;

		InvenComp->AddItem(this);
	}
}

bool ASBBasicItem::CanInteract()
{
	if (!ItemData.Interactable)
	{
		return false;
	}

	const auto GameMode = Cast<ASBGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!GameMode) return false;

	const auto Player = Cast<ASBPlayerCharacter>(GameMode->GetPlayerCharacter());
	if (!Player) return false;

	FVector PlayerLocation = Player->GetActorLocation();
	FVector ItemLocation = GetActorLocation();

	float Distance = FVector::Distance(PlayerLocation, ItemLocation);

	if (Distance > Player->GetInteractLength())
	{
		return false;
	}

	return true;
}

bool ASBBasicItem::UseItem()
{
	UE_LOG(LogTemp, Warning, TEXT("UseItem is Not Setting"));
	return true;
}

void ASBBasicItem::SetVisible(bool isVisible)
{
	if (isVisible)
	{
		Visible();
	}
	else
	{
		Invisible();
	}
}

void ASBBasicItem::Invisible()
{
	//NotWork

	UMaterialInstanceDynamic* MatInstanceDynamic = UMaterialInstanceDynamic::Create(StaticMeshComponent->GetMaterial(0), nullptr);
	if (!MatInstanceDynamic) return;

	MatInstanceDynamic->BlendMode = EBlendMode::BLEND_Translucent;
	MatInstanceDynamic->SetScalarParameterValue(TEXT("Opacity"), 0.2f);
	
	StaticMeshComponent->SetMaterial(0, MatInstanceDynamic);
	//StaticMeshComponent->SetScalarParameterValueOnMaterials(TEXT("Opacity"), 0.1f);
	
	//UE_LOG(LogTemp, Warning, TEXT("Invisible"));
}

void ASBBasicItem::Visible()
{
	//NotWork

	UMaterialInstanceDynamic* MatInstanceDynamic = UMaterialInstanceDynamic::Create(StaticMeshComponent->GetMaterial(0), nullptr);
	if (!MatInstanceDynamic) return;

	MatInstanceDynamic->BlendMode = EBlendMode::BLEND_Opaque;
	MatInstanceDynamic->SetScalarParameterValue(TEXT("Opacity"), 1.0f);

	StaticMeshComponent->SetMaterial(0, MatInstanceDynamic);

	//UE_LOG(LogTemp, Warning, TEXT("Visible"));
}
