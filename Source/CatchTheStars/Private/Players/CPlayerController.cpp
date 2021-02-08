// Fill out your copyright notice in the Description page of Project Settings.


#include "Players/CPlayerController.h"

#include <iostream>


#include "Actors/CStar.h"

const FName ActionName = "Selection";

ACPlayerController::ACPlayerController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
	bEnableTouchEvents = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void ACPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction(ActionName, IE_Pressed, this, &ACPlayerController::OnSelectionStart);
	InputComponent->BindAction(ActionName, IE_Released, this, &ACPlayerController::OnSelectionEnd);
}

void ACPlayerController::OnSelectionStart()
{
	FHitResult HitResult;
	GetHitResultUnderCursor(ECollisionChannel::ECC_WorldDynamic, false,HitResult);

	if (HitResult.GetActor() != nullptr && HitResult.GetActor()->IsA(ACStar::StaticClass()))
	{
		std::cout << "a star was selected";		
		SelectedStar =  Cast<ACStar>(HitResult.GetActor());
		SelectedStar->SetSelected(true);
	}
}

void ACPlayerController::OnSelectionEnd()
{
}
