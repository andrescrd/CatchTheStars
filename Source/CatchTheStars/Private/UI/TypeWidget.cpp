// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/TypeWidget.h"
#include "Support/Enums/StarTypesEnum.h"

void UTypeWidget::SetOwnParent(ITypeInterface*  NewParent)
{
	OwnParent = NewParent;
}

StarTypesEnum UTypeWidget::GetParentType() const
{
	 return OwnParent && IsValid(OwnParent->_getUObject()) ? OwnParent->GetType() : StarTypesEnum::A;
}
