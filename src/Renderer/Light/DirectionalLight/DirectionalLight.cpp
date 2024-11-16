﻿#include "DirectionalLight.h"

MESH_EDITOR_NAMESPACE_BEGIN

DirectionalLight::DirectionalLight()
{
    Intensity = 10.f;
    LightColor = glm::vec3(1.f, 1.f, 1.f);
    Direction = glm::vec3(1.f, 1.f, 1.f);
}

DirectionalLight::~DirectionalLight()
{
}

MESH_EDITOR_NAMESPACE_END
