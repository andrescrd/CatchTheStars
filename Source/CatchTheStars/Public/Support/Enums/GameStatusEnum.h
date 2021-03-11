// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameStatusEnum.generated.h"


UENUM(BlueprintType)
enum class EGameStatusEnum : uint8
{
	Waiting,
	Playing,
	Completed,
	GameOver,
	Unknown
};
