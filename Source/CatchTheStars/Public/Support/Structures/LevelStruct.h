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
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MaxTime;

	FLevelStruct(): IsAvailable(false), MaxTime(20), MapName(NAME_None)
	{
	}
};
