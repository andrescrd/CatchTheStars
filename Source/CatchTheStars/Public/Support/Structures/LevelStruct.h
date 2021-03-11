#pragma once
#include "LevelStruct.generated.h"

USTRUCT(BlueprintType)
struct FLevelStruct
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName MapName;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool IsAvailable;
	UPROPERTY(BlueprintReadOnly)
	float MaxTime;

	FLevelStruct(): MapName(NAME_None), IsAvailable(false), MaxTime(0)
	{
	}
};
