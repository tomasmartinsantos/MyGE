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
IncludeDir["GLFW"] = "MyGE/Vendor/GLFW/include"
IncludeDir["Glad"] = "MyGE/Vendor/Glad/include"
IncludeDir["ImGui"] = "MyGE/Vendor/imgui"

group "Dependencies"
	include "MyGE/vendor/GLFW"
	include "MyGE/vendor/Glad"
	include "MyGE/vendor/imgui"

group ""

project "MyGE"
	location "MyGE"
	kind "SharedLib"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "mgpch.h"
	pchsource "MyGE/src/mgpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"MG_PLATFORM_WINDOWS",
			"MG_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
		}

	filter "configurations:Debug"
		defines "MG_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "MG_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Release"
		defines "MG_DIST"
		runtime "Release"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"

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
		"MyGE/src"
	}

	links
	{
		"MyGE"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"MG_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "MG_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "MG_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Release"
		defines "MG_DIST"
		runtime "Release"
		optimize "On"