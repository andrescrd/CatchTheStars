#pragma once
#include "LevelStruct.generated.h"

USTRUCT(BlueprintType)
struct FLevelStruct
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName LevelName;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool IsAvailable;
	UPROPERTY(BlueprintReadOnly)
	int MaxTime;

	FLevelStruct(): LevelName(NAME_None), IsAvailable(false), MaxTime(0)
	{
	}
};
