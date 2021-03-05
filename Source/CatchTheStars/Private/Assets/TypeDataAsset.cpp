// Fill out your copyright notice in the Description page of Project Settings.


#include "Assets/TypeDataAsset.h"

UStaticMesh* UTypeDataAsset::GetMesh(const StarTypesEnum Type)
{
	return (Type!= StarTypesEnum::NONE) ? Meshes[Type] : nullptr;
}
