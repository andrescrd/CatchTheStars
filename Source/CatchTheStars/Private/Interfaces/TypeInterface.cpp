// Fill out your copyright notice in the Description page of Project Settings.


#include "Interfaces/TypeInterface.h"

// Add default functionality here for any ICTypeInterface functions that are not pure virtual.
void ITypeInterface::SetType(CStarTypesEnum NewType)
{
}

CStarTypesEnum ITypeInterface::GetType()
{
	return CStarTypesEnum::A;
}
