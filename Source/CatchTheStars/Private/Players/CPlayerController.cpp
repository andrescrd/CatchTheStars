// Fill out your copyright notice in the Description page of Project Settings.

#include "Players/CPlayerController.h"

#include "Actors/CNode.h"
#include "Actors/CStar.h"
#include "Actors/CTarget.h"
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
	InputComponent->BindAction(ActionName, IE_Pressed, this, &ACPlayerController::OnSelected);
}

ACCharacter* ACPlayerController::GetCurrentCharacter()
{
	if (!IsValid(CurrentCharacter))
	{
		if (AActor* Actor = UGameplayStatics::GetActorOfClass(GetWorld(), ACCharacter::StaticClass()))
			CurrentCharacter = Cast<ACCharacter>(Actor);
	}

	return CurrentCharacter;
}

void ACPlayerController::OnSelected()
{
	FHitResult HitResult;
	GetHitResultUnderCursorByChannel(ETraceTypeQuery::TraceTypeQuery1, false, HitResult);

	if (HitResult.GetActor() != nullptr && HitResult.GetActor()->IsA(ACStar::StaticClass()))
	{
		ACStar* Star = Cast<ACStar>(HitResult.GetActor());
		SetSelectedStar(Star);
	}
	else if (HitResult.GetActor() != nullptr && HitResult.GetActor()->IsA(ACTarget::StaticClass()) && SelectedStar != nullptr)
	{
		ACTarget* Target = Cast<ACTarget>(HitResult.GetActor());
		SetSelectedTarget(Target);
	}
	else
	{
		if (SelectedStar)
			SelectedStar->SetSelected(false);

		if (SelectedTarget)
			SelectedTarget->SetSelected(false);

		SelectedStar = nullptr;
		SelectedTarget = nullptr;
	}
}

void ACPlayerController::SetSelectedStar(ACStar* Star)
{
	GEngine->AddOnScreenDebugMessage(0, 3, FColor::Green, FString::Printf(TEXT("Star clicked")));

	if (SelectedStar != nullptr && SelectedStar != Star)
		SelectedStar->SetSelected(false);

	SelectedStar = Star;
	SelectedStar->SetSelected(true);

	MoveCharacterTo(SelectedStar->GetActorLocation());
}

void ACPlayerController::SetSelectedTarget(ACTarget* Target)
{
	GEngine->AddOnScreenDebugMessage(0, 3, FColor::Green, FString::Printf(TEXT("Target clicked")));

	if (SelectedTarget != nullptr && SelectedTarget != Target)
		SelectedTarget->SetSelected(false);

	SelectedTarget = Target;
	SelectedTarget->SetSelected(true);

	auto ParentTarget = Cast<ACNode>(SelectedTarget->GetAttachParentActor());
	auto ParentStar = Cast<ACNode>(SelectedStar->GetAttachParentActor());
	
	if (ParentTarget == ParentStar || ParentTarget->HasStar())
		return;

	ParentStar->RemoveStar();
	ParentTarget->SetStar(SelectedStar);
	
	// SelectedStar->SetSelected(false);
	SelectedStar->SetNewLocation(SelectedTarget->GetActorLocation());

	MoveCharacterTo(SelectedTarget->GetActorLocation());

	SelectedTarget = nullptr;
	SelectedStar = nullptr;
}

void ACPlayerController::MoveCharacterTo(const FVector Location) { GetCurrentCharacter()->MoveToDestination(Location); }
