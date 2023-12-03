// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/SBPlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SBEnergyComponent.h"
#include "SBInventoryComponent.h"
#include "SBGameModeBase.h"

ASBPlayerCharacter::ASBPlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation = true;

	SpringArmComponent->TargetArmLength = 0.0f;
	SpringArmComponent->SocketOffset = FVector(-10.0f, 0.0f, 60.0f);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);

	CameraCollisionComponent = CreateDefaultSubobject<USphereComponent>("CameraCollisionComponent");
	CameraCollisionComponent->SetupAttachment(CameraComponent);
	CameraCollisionComponent->SetSphereRadius(10.0f);
	CameraCollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

	EnergyComponent = CreateDefaultSubobject<USBEnergyComponent>("EnergyComponent");

	InventoryComponent = CreateDefaultSubobject<USBInventoryComponent>("InventoryComponent");

	GetMesh()->bOwnerNoSee = true;

}

void ASBPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	check(EnergyComponent);

	//CameraCollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ASBPlayerCharacter::OnCameraCollisionBeginOverlap);
	//CameraCollisionComponent->OnComponentEndOverlap.AddDynamic(this, &ASBPlayerCharacter::OnCameraCollisionEndOverlap);
	
	const auto GameMode = Cast<ASBGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!GameMode) return;

	GameMode->SetPlayerCharacter(this);
}

void ASBPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASBPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASBPlayerCharacter::Jump);
	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ASBPlayerCharacter::StartRun);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &ASBPlayerCharacter::StopRun);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASBPlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASBPlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Lookup", this, &ASBPlayerCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookAround", this, &ASBPlayerCharacter::AddControllerYawInput);

}

void ASBPlayerCharacter::MoveForward(float Amount)
{
	AddMovementInput(GetActorForwardVector(), Amount);
}

void ASBPlayerCharacter::MoveRight(float Amount)
{
	AddMovementInput(GetActorRightVector(), Amount);
}

void ASBPlayerCharacter::StartRun()
{
	GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
}

void ASBPlayerCharacter::StopRun()
{
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void ASBPlayerCharacter::OnCameraCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("CameraCollision Begin Overlap"));
	// not use
}

void ASBPlayerCharacter::OnCameraCollisionEndOverlap(UPrimitiveComponent* OverlappedComponent,AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("CameraCollision End Overlap"));
	// not use
}
