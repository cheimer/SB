#pragma once
#include "SBCoreTypes.generated.h"


//Items

UENUM(BlueprintType)
enum class EItemTypes : uint8
{
	Show,
	Food,
	Creatable
};

USTRUCT(BlueprintType)
struct FItemData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	FText ItemName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	FText ItemEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	FText ItemDesc;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	EItemTypes ItemType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	bool Interactable;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta = (EditCondition = "Interactable"))
	int32 ContainSize;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta = (EditCondition = "Interactable"))
	bool Usable;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta = (EditCondition = "Usable"))
	bool isCreate;
};


// UI

UENUM(BlueprintType)
enum class EScreenMode : uint8
{
	Field = 0,
	Inventory,
	Map,
	GamePause
};

//DECLARE_MULTICAST_DELEGATE(FOnItemSettingSignature);


// Player

UENUM(BlueprintType)
enum class EPlayerState : uint8
{
	Normal = 0,
	Creater
};


//Quest

UENUM(BlueprintType)
enum class EQuestTypes : uint8
{
	ItemFind = 0,
	ItemRequire
};


USTRUCT(BlueprintType)
struct FQuestData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Quest")
	FText QuestName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Quest")
	FText QuestEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Quest")
	FText QuestText;

	bool isStart = false;
	bool isEnd = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Quest")
	bool isLoop = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Quest")
	EQuestTypes QuestType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Quest", meta = (EditCondition = "QuestType == EQuestTypes.ItemFind || QuestType == EQuestTypes.ItemRequire"))
	FText ItemName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Quest", meta = (EditCondition = "QuestType == EQuestTypes.ItemFind || QuestType == EQuestTypes.ItemRequire"))
	int32 ItemNum;
};
