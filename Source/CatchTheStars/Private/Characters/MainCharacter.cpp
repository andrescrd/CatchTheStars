// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/MainCharacter.h"


#include "AIController.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
	AcceptanceRadius = 50;

	GetCapsuleComponent()->InitCapsuleSize(56.0f, 56.0f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;
}

void AMainCharacter::MoveToDestination(const FVector Destination) const
{
	if (AAIController* AI = Cast<AAIController>(GetController()))
		AI->MoveToLocation(Destination, AcceptanceRadius, false);
}
