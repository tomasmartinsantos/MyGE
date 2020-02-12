workspace "MyGE"
	architecture "x86_64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories realtive to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "MyGE/vendor/GLFW/include"
IncludeDir["Glad"] = "MyGE/vendor/Glad/include"
IncludeDir["ImGui"] = "MyGE/vendor/imgui"
IncludeDir["glm"] = "MyGE/vendor/glm"

group "Dependencies"
	include "MyGE/vendor/GLFW"
	include "MyGE/vendor/Glad"
	include "MyGE/vendor/imgui"

group ""

project "MyGE"
	location "MyGE"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "mgpch.h"
	pchsource "MyGE/src/mgpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"MG_PLATFORM_WINDOWS",
			"MG_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "MG_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "MG_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Release"
		defines "MG_DIST"
		runtime "Release"
		optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs
	{
		"MyGE/vendor/spdlog/include",
		"MyGE/src",
		"MyGE/vendor",
		"%{IncludeDir.glm}"
	}

	links
	{
		"MyGE"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"MG_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "MG_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "MG_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Release"
		defines "MG_DIST"
		runtime "Release"
		optimize "on"