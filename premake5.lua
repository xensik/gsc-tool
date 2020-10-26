
local _project_dir = path.getabsolute("src")
function project_dir()
	return path.getrelative(os.getcwd(), _project_dir)
end

-- ========================
-- Workspace
-- ========================

workspace "gsc-tool"
	location "./build"
	objdir "%{wks.location}/obj/%{prj.name}"
	targetdir "%{wks.location}/bin/%{cfg.buildcfg}"
	targetname "%{prj.name}"

	language "C++"
	
	architecture "x86_64"

	configurations { "debug", "release", }

	buildoptions "/std:c++latest"
	systemversion "latest"
	symbols "On"
	editandcontinue "Off"

	flags {
		"NoIncrementalLink",
		"NoMinimalRebuild",
		"MultiProcessorCompile",
		"No64BitChecks"
	}

	configuration "windows"
		defines {
			"_WINDOWS",
			"WIN32",
		}
	configuration{}

	configuration "release"
		optimize "Full"
		defines {
			"NDEBUG",
		}
	configuration{}

	configuration "debug"
		optimize "Debug"
		defines {
			"DEBUG",
			"_DEBUG",
		}
	configuration {}

	startproject "gsc-tool"

-- ========================
-- Projects
-- ========================

	include "src/tool.lua"
	include "src/utils.lua"
	include "src/IW5.lua"
	include "src/IW6.lua"
	include "src/SH1.lua"

	tool:project()
	utils:project()
	IW5:project()
	IW6:project()
	SH1:project()
