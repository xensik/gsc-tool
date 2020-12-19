local _deps_folder = path.getabsolute("deps")

function deps_folder()
	return path.getrelative(os.getcwd(), _deps_folder)
end

local _project_folder = path.getabsolute("src")

function project_folder()
    return path.getrelative(os.getcwd(), _project_folder)
end

dependencies = { basePath = path.getrelative(os.getcwd(), path.getabsolute("deps")) }

function dependencies.load()
	dir = path.join(dependencies.basePath, "*.lua")
	deps = os.matchfiles(dir)

	for i, dep in pairs(deps) do
		dep = dep:gsub(".lua", "")
		require(dep)
	end
end

function dependencies.link()
	for i, proj in pairs(dependencies) do
		if type(i) == 'number' then
			proj.link()
		end
	end
end

dependencies.load()
-------------------------------------------------
workspace "gsc-tool"
location "./build"
objdir "%{wks.location}/obj/%{cfg.buildcfg}/%{prj.name}"
targetdir "%{wks.location}/bin/%{cfg.buildcfg}"
targetname "%{prj.name}"

language "C++"
cppdialect "C++17"
architecture "x86_64"

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
-------------------------------------------------
group "Dependencies"

include "deps/zlib.lua"
zlib:project()

group ""

include "src/tool.lua"
include "src/utils.lua"
include "src/IW5.lua"
include "src/IW6.lua"
include "src/S1.lua"
tool:project()
utils:project()
IW5:project()
IW6:project()
S1:project()
