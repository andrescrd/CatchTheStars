// Fill out your copyright notice in the Description page of Project Settings.


#include "Players/CPlayerController.h"

#include <iostream>


#include "Actors/CStar.h"
#include "Characters/CCharacter.h"
#include "Kismet/GameplayStatics.h"

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

ACCharacter* ACPlayerController::GetCurrentCharacter()
{
	if(!IsValid(CurrentCharacter))
	{
		if( AActor * Actor = UGameplayStatics::GetActorOfClass(GetWorld(), ACCharacter::StaticClass()))
			CurrentCharacter = Cast<ACCharacter>(Actor);
	}

	return CurrentCharacter;
}

void ACPlayerController::OnSelectionStart()
{
	FHitResult HitResult;
	GetHitResultUnderCursorByChannel(ETraceTypeQuery::TraceTypeQuery1, false, HitResult);	

	if (HitResult.GetActor() != nullptr && HitResult.GetActor()->IsA(ACStar::StaticClass()))
	{
		std::cout << "a star was selected";		
		SelectedStar =  Cast<ACStar>(HitResult.GetActor());
		SelectedStar->SetSelected(true);

		GetCurrentCharacter()->MoveToDestination(SelectedStar->GetActorLocation());
	}
}

void ACPlayerController::OnSelectionEnd()
{
	if(SelectedStar)
	{
		SelectedStar->SetSelected(false);
		SelectedStar= nullptr;
	}
}
