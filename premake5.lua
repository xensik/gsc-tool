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
    location "./build"
    objdir "%{wks.location}/obj/%{cfg.buildcfg}/%{prj.name}"
    targetdir "%{wks.location}/bin/%{cfg.buildcfg}"
    targetname "%{prj.name}"
    staticruntime "On"
    language "C++"
    cppdialect "C++20"
    architecture "x64"

    filter "action:vs*"
        buildoptions "/bigobj"
        buildoptions "/Zc:__cplusplus"
    filter {}

    configurations { "Debug", "Release" }

    symbols "On"
    warnings "Extra"

    filter "configurations:Release"
        optimize "Full"
        defines { "NDEBUG" }
        flags { "FatalCompileWarnings" }
    filter {}

    filter "configurations:Debug"
        optimize "Debug"
        defines { "DEBUG", "_DEBUG" }
    filter {}

    startproject "xsk-gsc-tool"

project "xsk-gsc-tool"
    kind "ConsoleApp"
    language "C++"
    targetname "gsc-tool"

    dependson "xsk-gsc-utils"
    dependson "xsk-gsc-iw5"
    dependson "xsk-gsc-iw6"
    dependson "xsk-gsc-iw7"
    dependson "xsk-gsc-iw8"
    dependson "xsk-gsc-s1"
    dependson "xsk-gsc-s2"
    dependson "xsk-gsc-s4"
    dependson "xsk-gsc-h1"
    dependson "xsk-gsc-h2"
    dependson "xsk-arc-t6"

    pchheader "stdafx.hpp"
    pchsource "src/tool/stdafx.cpp"

    files {
        "./src/tool/**.h",
        "./src/tool/**.hpp",
        "./src/tool/**.cpp"
    }

    links {
        "xsk-gsc-utils",
        "xsk-gsc-iw5",
        "xsk-gsc-iw6",
        "xsk-gsc-iw7",
        "xsk-gsc-iw8",
        "xsk-gsc-s1",
        "xsk-gsc-s2",
        "xsk-gsc-s4",
        "xsk-gsc-h1",
        "xsk-gsc-h2",
        "xsk-arc-t6"
    }

    includedirs {
        "./src/tool",
        "./src"
    }

    zlib:link()

project "xsk-gsc-utils"
    kind "StaticLib"
    language "C++"

    pchheader "stdafx.hpp"
    pchsource "src/utils/stdafx.cpp"

    files {
        "./src/utils/**.h",
        "./src/utils/**.hpp",
        "./src/utils/**.cpp"
    }

    includedirs {
        "./src/utils",
        "./src"
    }

    zlib:include()

project "xsk-gsc-iw5"
    kind "StaticLib"
    language "C++"

    pchheader "stdafx.hpp"
    pchsource "src/iw5/stdafx.cpp"

    files {
        "./src/iw5/**.h",
        "./src/iw5/**.hpp",
        "./src/iw5/**.cpp"
    }

    includedirs {
        "./src/iw5",
        "./src"
    }

project "xsk-gsc-iw6"
    kind "StaticLib"
    language "C++"

    pchheader "stdafx.hpp"
    pchsource "src/iw6/stdafx.cpp"

    files {
        "./src/iw6/**.h",
        "./src/iw6/**.hpp",
        "./src/iw6/**.cpp"
    }

    includedirs {
        "./src/iw6",
        "./src"
    }

project "xsk-gsc-iw7"
    kind "StaticLib"
    language "C++"

    pchheader "stdafx.hpp"
    pchsource "src/iw7/stdafx.cpp"

    files {
        "./src/iw7/**.h",
        "./src/iw7/**.hpp",
        "./src/iw7/**.cpp"
    }

    includedirs {
        "./src/iw7",
        "./src"
    }

project "xsk-gsc-iw8"
    kind "StaticLib"
    language "C++"

    pchheader "stdafx.hpp"
    pchsource "src/iw8/stdafx.cpp"

    files {
        "./src/iw8/**.h",
        "./src/iw8/**.hpp",
        "./src/iw8/**.cpp"
    }

    includedirs {
        "./src/iw8",
        "./src"
    }

project "xsk-gsc-s1"
    kind "StaticLib"
    language "C++"

    pchheader "stdafx.hpp"
    pchsource "src/s1/stdafx.cpp"

    files {
        "./src/s1/**.h",
        "./src/s1/**.hpp",
        "./src/s1/**.cpp"
    }

    includedirs {
        "./src/s1",
        "./src"
    }

project "xsk-gsc-s2"
    kind "StaticLib"
    language "C++"

    pchheader "stdafx.hpp"
    pchsource "src/s2/stdafx.cpp"

    files {
        "./src/s2/**.h",
        "./src/s2/**.hpp",
        "./src/s2/**.cpp"
    }

    includedirs {
        "./src/s2",
        "./src"
    }

project "xsk-gsc-s4"
    kind "StaticLib"
    language "C++"

    pchheader "stdafx.hpp"
    pchsource "src/s4/stdafx.cpp"

    files {
        "./src/s4/**.h",
        "./src/s4/**.hpp",
        "./src/s4/**.cpp"
    }

    includedirs {
        "./src/s4",
        "./src"
    }

project "xsk-gsc-h1"
    kind "StaticLib"
    language "C++"

    pchheader "stdafx.hpp"
    pchsource "src/h1/stdafx.cpp"

    files {
        "./src/h1/**.h",
        "./src/h1/**.hpp",
        "./src/h1/**.cpp"
    }

    includedirs {
        "./src/h1",
        "./src"
    }

project "xsk-gsc-h2"
    kind "StaticLib"
    language "C++"

    pchheader "stdafx.hpp"
    pchsource "src/h2/stdafx.cpp"

    files {
        "./src/h2/**.h",
        "./src/h2/**.hpp",
        "./src/h2/**.cpp"
    }

    includedirs {
        "./src/h2",
        "./src"
    }

project "xsk-arc-t6"
    kind "StaticLib"
    language "C++"

    pchheader "stdafx.hpp"
    pchsource "src/t6/stdafx.cpp"

    files {
        "./src/t6/**.h",
        "./src/t6/**.hpp",
        "./src/t6/**.cpp"
    }

    includedirs {
        "./src/t6",
        "./src"
    }

group "Dependencies"
    zlib:project()
