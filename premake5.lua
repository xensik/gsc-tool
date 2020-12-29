dependencies = { base = path.getrelative(os.getcwd(), path.getabsolute("deps")) }
projects = { base = path.getrelative(os.getcwd(), path.getabsolute("src")) }

function dependencies.load()
    dir = path.join(dependencies.base, "*.lua")
    deps = os.matchfiles(dir)

    for i, dep in pairs(deps) do
        dep = dep:gsub(".lua", "")
        require(dep)
    end
end

function projects.load()
    dir = path.join(projects.base, "*.lua")
    deps = os.matchfiles(dir)

    for i, dep in pairs(deps) do
        dep = dep:gsub(".lua", "")
        require(dep)
    end
end

dependencies.load()
projects.load()
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
zlib:project()

group ""
tool:project()
utils:project()
IW5:project()
IW6:project()
IW7:project()
S1:project()
S2:project()
H1:project()
H2:project()
