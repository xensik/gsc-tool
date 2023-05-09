dependencies = { base = path.getrelative(os.getcwd(), path.getabsolute("deps")) }

function dependencies.load()
    dir = path.join(dependencies.base, "*.lua")
    deps = os.matchfiles(dir)

    for i, dep in pairs(deps) do
        dep = dep:gsub(".lua", "")
        require(dep)
    end
end

dependencies.load()
-------------------------------------------------
workspace "gsc-tool"
    startproject "xsk-tool"
    location "./build"
    objdir "%{wks.location}/obj/%{cfg.buildcfg}/%{prj.name}"
    targetdir "%{wks.location}/bin/%{cfg.platform}/%{cfg.buildcfg}"
    targetname "%{prj.name}"

    configurations { "debug", "release" }

    if os.istarget("darwin") then
        platforms { "x64", "arm64" }
    else
        platforms { "x86", "x64" }
    end

    filter "platforms:x86"
        architecture "x86"
    filter {}

    filter "platforms:x64"
        architecture "x86_64"
    filter {}

    filter "platforms:arm64"
        architecture "ARM64"
    filter {}

    filter { "language:C++", "toolset:not msc*" }
	    buildoptions "-std=c++20"
    filter {}

    filter "toolset:msc*"
        buildoptions "/bigobj"
        buildoptions "/Zc:__cplusplus"
        buildoptions "/std:c++20"
    filter {}

    filter { "system:windows" }
	    systemversion "latest"
    filter {}

    filter { "system:macosx" }
	    systemversion "12.0"
    filter {}

    symbols "On"
    staticruntime "On"
    warnings "Extra"

    if os.istarget("linux") or os.istarget("darwin") then
        buildoptions "-pthread"
        linkoptions "-pthread"
    end

    filter "configurations:release"
        optimize "Full"
        defines { "NDEBUG" }
        flags { "FatalCompileWarnings" }
    filter {}

    filter "configurations:debug"
        optimize "Debug"
        defines { "DEBUG", "_DEBUG" }
    filter {}

project "xsk-tool"
    kind "ConsoleApp"
    language "C++"
    targetname "gsc-tool"

    dependson "xsk-utils"
    dependson "xsk-arc"
    dependson "xsk-gsc"

    files {
        "./src/tool/**.h",
        "./src/tool/**.hpp",
        "./src/tool/**.cpp"
    }

    links {
        "xsk-utils",
        "xsk-arc",
        "xsk-gsc",
    }

    includedirs {
        "./include",
    }

    fmt:link()
    zlib:link()

project "xsk-utils"
    kind "StaticLib"
    language "C++"

    files {
        "./src/utils/**.h",
        "./src/utils/**.hpp",
        "./src/utils/**.cpp"
    }

    includedirs {
        "./include",
    }

    fmt:include()
    zlib:include()

project "xsk-arc"
    kind "StaticLib"
    language "C++"

    files {
        "./src/arc/**.h",
        "./src/arc/**.hpp",
        "./src/arc/**.cpp"
    }

    includedirs {
        "./include",
    }

    fmt:include()

project "xsk-gsc"
    kind "StaticLib"
    language "C++"

    files {
        "./src/gsc/**.h",
        "./src/gsc/**.hpp",
        "./src/gsc/**.cpp"
    }

    includedirs {
        "./include",
    }

    fmt:include()

group "Dependencies"
    zlib:project()
    fmt:project()
