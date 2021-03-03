// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CCharacter.generated.h"

UCLASS()
class CATCHTHESTARS_API ACCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACCharacter();

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float AcceptanceRadius;
	
public:
	void MoveToDestination(FVector Destination) const;	
};
