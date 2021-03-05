// Fill out your copyright notice in the Description page of Project Settings.


#include "Interfaces/TypeInterface.h"
#include "Support/Enums/StarTypesEnum.h"

// Add default functionality here for any ICTypeInterface functions that are not pure virtual.
void ITypeInterface::SetType(StarTypesEnum NewType)
{
}

StarTypesEnum ITypeInterface::GetType()
{
	return StarTypesEnum::NONE;
}
