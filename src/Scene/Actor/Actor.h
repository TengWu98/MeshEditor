﻿#pragma once
#include "pch.h"
#include "entt.hpp"

MESH_EDITOR_NAMESPACE_BEGIN

class Actor
{
public:
    Actor() = default;
    virtual ~Actor() = default;

    Actor(const Actor& Other);
    bool operator==(const Actor& Other) const { return ActorHandle == Other.ActorHandle; }

protected:
    

private:
    entt::entity ActorHandle = entt::null;
};

MESH_EDITOR_NAMESPACE_END
