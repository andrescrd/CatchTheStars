#pragma once

#include "NiagaraComponent.h"
#include "Support/Enums/CStarTypesEnum.h"

#include "CNode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSuccessAttachSignature, const class ACNode*, Node, const bool, Success);

UCLASS()
class CATCHTHESTARS_API ACNode : public AActor

{
	GENERATED_BODY()

public:
	ACNode();

protected:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category=Setup)
	class ACTarget* Target;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category=Setup)
	class ACStar* Star;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category=Setup)
	class USceneComponent* Root;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category=Setup)
	class UChildActorComponent* TargetChild;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category=Setup)
	class UChildActorComponent* StarChild;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Setup)
	TSubclassOf<class ACTarget> TargetClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Setup)
	TSubclassOf<class ACStar> StarClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Setup)
	bool bHasStar;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Setup)
	CStarTypesEnum TargetType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Setup)
	CStarTypesEnum StarType;

	void RemoveChild(UChildActorComponent* Child);
	void SetupChildren();
	void SetupType() const;
	
public:
	virtual void OnConstruction(const FTransform& Transform) override;
	
	class ACTarget* GetTarget() const;
	class ACStar* GetStar() const;
	void SetStar(class ACStar* NewStar);
	bool IsSuccessAttach() const;
	bool HasStar() const;
	void RemoveStar();

	FSuccessAttachSignature OnSuccessAttached;
};
