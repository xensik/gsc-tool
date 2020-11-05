
local _project_dir = path.getabsolute("src")
function project_dir()
	return path.getrelative(os.getcwd(), _project_dir)
end

-- ========================
-- Workspace
-- ========================

workspace "gsc-tool"
	location "./build"
	objdir "%{wks.location}/obj/%{cfg.buildcfg}/%{prj.name}"
	targetdir "%{wks.location}/bin/%{cfg.buildcfg}"
	targetname "%{prj.name}"

	language "C++"
	cppdialect "C++17"

	architecture "x86_64"
	
	-- microsoft shit
	filter "action:vs*"
		buildoptions "/Zc:__cplusplus"
	filter{}

	configurations { "debug", "release", }

	symbols "On"
	
	configuration "release"
		optimize "Full"
		defines { "NDEBUG", "YY_NO_UNISTD_H"}
	configuration{}

	configuration "debug"
		optimize "Debug"
		defines { "DEBUG", "_DEBUG", "YY_NO_UNISTD_H" }
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
