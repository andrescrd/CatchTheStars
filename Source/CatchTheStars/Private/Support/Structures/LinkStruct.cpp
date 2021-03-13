
#include "Support/Structures/LinkStruct.h"

#include "Actors/NodeGraph.h"


FString FLinkStruct::GetId() const { return From->GetName() + To->GetName(); }

FString FLinkStruct::GetIdInverted() const { return To->GetName() + From->GetName(); }

bool FLinkStruct::HasKey() const{ return Key != nullptr; }

bool FLinkStruct::IsBlocked() const { return HasKey() && !Key->IsSuccessAttach(); }
