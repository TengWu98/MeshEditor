include "Dependencies.lua"

workspace "MeshEditor"

    startproject "MeshEditor"

    configurations
    {
        "Debug",
        "Release",
    }

    platforms
    {
        'Win64'
    }

    flags
	{
		"MultiProcessorCompile"
	}

    filter "platforms:Win64"
        system "windows"
        architecture "x64"

    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

    group "Dependencies"
        include "lib/ImGui"
        include "lib/GLFW"
    group ""


project "MeshEditor"
    
    kind "ConsoleApp"

    language "C++"

    cppdialect "C++20"

    staticruntime "on"

    targetdir ("%{wks.location}/binaries/" .. outputdir .. "/%{prj.name}")

    objdir ("%{wks.location}/intermediate/" .. outputdir .. "/%{prj.name}")

    pchheader "pch.h"

    pchsource "src/pch.cpp"

    files
    {
        "src/**.h",
        "src/**.cpp",

        "%{IncludeDir.stb_image}/**.h",
        "%{IncludeDir.stb_image}/**.cpp",

        "%{IncludeDir.glm}/**.hpp",
        "%{IncludeDir.glm}/**.inl",

        "%{IncludeDir.ImGuizmo}/ImGuizmo.h",
		"%{IncludeDir.ImGuizmo}/ImGuizmo.cpp"
    }

    includedirs
    {
        "src",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.ImGuizmo}",
        "%{IncludeDir.stb_image}",
        "%{IncludeDir.entt}",
        "%{IncludeDir.OpenMesh}",
        "%{IncludeDir.nfd}",
    }

    links
    {
        "ImGui",
        "GLFW",
        "opengl32",
        "lib/nfd/lib/nfd.lib"
    }

    flags { "NoPCH" }

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "MESH_EDITOR_PLATFORM_WINDOWS",
            "MESH_EDITOR_ENABLE_ASSERTS",

            "_USE_MATH_DEFINES", -- OpenMesh
        }

    filter "configurations:Debug"
        defines
        {
            "MESH_EDITOR_DEBUG"
        }

        links
        {
            "lib/OpenMesh/lib/OpenMeshCored.lib",
            "lib/OpenMesh/lib/OpenMeshToolsd.lib",
        }

        staticruntime "off"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines
        {
            "MESH_EDITOR_RELEASE"
        }

        links
        {
            "lib/OpenMesh/lib/OpenMeshCore.lib",
            "lib/OpenMesh/lib/OpenMeshTools.lib",
        }

        staticruntime "off"
        runtime "Release"
        optimize "on"