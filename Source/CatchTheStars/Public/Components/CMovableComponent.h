// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/TimelineComponent.h"

#include "CMovableComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CATCHTHESTARS_API UCMovableComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCMovableComponent();

protected:
	FVector InitialLocation;
	FVector StartLocation;
	FVector EndLocation;
	
	UPROPERTY(BlueprintReadOnly)
	class UTimelineComponent* TimelineComponent;	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UCurveFloat* Curve;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float OffsetZ;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FFloatRange Time;
	
	virtual void BeginPlay() override;
	void SetupTimeline();
	void GetNewLocation();
	void PlayTimeline();
	
	UFUNCTION()
	void OnTimelineHandler(float Value);
	UFUNCTION()	
	void OnFinishHandler();

public:
	virtual  void Activate(bool bReset) override;
	virtual  void Deactivate() override;
};
