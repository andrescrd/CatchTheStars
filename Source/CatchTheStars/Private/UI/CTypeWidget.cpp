// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/CTypeWidget.h"
#include "Support/Enums/CStarTypesEnum.h"

void UCTypeWidget::SetOwnParent(ITypeInterface*  NewParent)
{
	OwnParent = NewParent;
}

CStarTypesEnum UCTypeWidget::GetParentType() const
{
	 return OwnParent && IsValid(OwnParent->_getUObject()) ? OwnParent->GetType() : CStarTypesEnum::A;
}
