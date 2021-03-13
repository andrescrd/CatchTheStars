#pragma once

#include "Support/Enums/StarTypesEnum.h"
#include "Support/Structures/LinkStruct.h"

#include "NodeGraph.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSuccessAttachSignature, const class ANodeGraph*, Node, const bool,
                                             Success);

UCLASS()
class CATCHTHESTARS_API ANodeGraph : public AActor

{
	GENERATED_BODY()

public:
	ANodeGraph();

protected:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category=Setup)
	class ATarget* Target;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category=Setup)
	class AStar* Star;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category=Setup)
	class USceneComponent* Root;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category=Setup)
	class UChildActorComponent* TargetChild;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category=Setup)
	class UChildActorComponent* StarChild;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category=Setup)
	class UNiagaraComponent* NiagaraBlocked;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category=Setup)
	class UNiagaraComponent* NiagaraSuccessAttach;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Setup)
	TSubclassOf<class ATarget> TargetClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Setup)
	TSubclassOf<class AStar> StarClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Setup)
	bool bHasStar;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Setup)
	EStarTypesEnum TargetType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Setup, meta=(EditCondition="bHasStar"))
	EStarTypesEnum StarType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Setup)
	TArray<FLinkStruct> Links;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Setup)
	class UNiagaraSystem* FXSuccessTemplate;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Setup)
	class UNiagaraSystem* FXBlockedTemplate;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Setup)
	class USoundBase* AttachSound;

	void RemoveChild(class UChildActorComponent* Child);
	void SetupType() const;
	void SetupTarget();
	void SetupStar();
	void SetupLinkStruct();

	void PlayAttachSound() const;
	void ActivateNiagaraSuccessAttach(const bool Activate) const;
	void NotifySuccessAttach(const bool WasSuccess) const;

public:
	FSuccessAttachSignature OnSuccessAttached;

	virtual void OnConstruction(const FTransform& Transform) override;

	class ATarget* GetTarget() const;
	class AStar* GetStar() const;
	TArray<FLinkStruct> GetLinks() const;
	FVector GetStarLocation() const;

	void SetIsKey(const bool IsKey) const;
	void SetStar(class AStar* NewStar);
	void RemoveStar();
	
	bool IsSuccessAttach() const;
	bool HasStar() const;	

	UFUNCTION(CallInEditor, Category=Setup)
	void ShowDebugLinks();
};
