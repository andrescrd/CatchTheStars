// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainCharacter.generated.h"

UCLASS()
class CATCHTHESTARS_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharacter();

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float AcceptanceRadius;
	
public:
	void MoveToDestination(FVector Destination) const;	
};
