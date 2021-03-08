// Fill out your copyright notice in the Description page of Project Settings.

#include "Assets/TypeDataAsset.h"

UStaticMesh* UTypeDataAsset::GetStarMesh(const StarTypesEnum Type)
{
	for (const auto Elem : AssetTypes)
	{
		if(Elem.Type == Type)
			return Elem.StartMesh;
	}

	return nullptr;
}