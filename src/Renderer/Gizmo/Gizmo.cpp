﻿#include "Gizmo.h"

#include <imgui_internal.h>

#include "Renderer/Camera/Camera.h"

MESH_EDITOR_NAMESPACE_BEGIN

void Gizmo::Begin() const
{
    using namespace ImGui;
    
    const auto ContentRegion = GetContentRegionAvail();
    const auto& WindowPos = GetWindowPos();
    ImGuizmo::BeginFrame();
    ImGuizmo::SetDrawlist();
    ImGuizmo::SetOrthographic(false);
    ImGuizmo::SetRect(WindowPos.x, WindowPos.y + GetTextLineHeightWithSpacing(), ContentRegion.x, ContentRegion.y);
}

void Gizmo::Render(Camera& Camera, bool& bIsViewChanged) const
{
    using namespace ImGui;

    static constexpr float ViewManipulateSize = 128;

    const auto& WindowPos = GetWindowPos();
    const auto ViewManipulatePos = ImVec2{GetWindowContentRegionMax().x - ViewManipulateSize + WindowPos.x, GetWindowContentRegionMin().y + WindowPos.y};
    auto CameraView = Camera.GetViewMatrix();
    const float CameraDistance = Camera.GetCurrentDistance();
    bIsViewChanged = ImGuizmo::ViewManipulate(&CameraView[0][0], CameraDistance, ViewManipulatePos, {ViewManipulateSize, ViewManipulateSize}, 0);
    if (bIsViewChanged)
    {
        Camera.SetPositionFromView(CameraView);
    }
}

void Gizmo::RenderDebug()
{
    using namespace ImGui;
    using namespace ImGuizmo;

    
}

MESH_EDITOR_NAMESPACE_END