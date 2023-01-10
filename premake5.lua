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
    startproject "xsk-gsc-tool"
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

project "xsk-gsc-tool"
    kind "ConsoleApp"
    language "C++"
    targetname "gsc-tool"

    dependson "xsk-gsc-utils"
    dependson "xsk-gsc-h1"
    dependson "xsk-gsc-h2"
    dependson "xsk-gsc-iw5"
    dependson "xsk-gsc-iw6"
    dependson "xsk-gsc-iw7"
    dependson "xsk-gsc-iw8"
    dependson "xsk-gsc-iw9"
    dependson "xsk-gsc-s1"
    dependson "xsk-gsc-s2"
    dependson "xsk-gsc-s4"
    dependson "xsk-arc-t6"
    dependson "xsk-gsc-iw5c"
    dependson "xsk-gsc-iw6c"
    dependson "xsk-gsc-s1c"

    pchheader "stdafx.hpp"
    pchsource "src/tool/stdafx.cpp"

    files {
        "./src/tool/**.h",
        "./src/tool/**.hpp",
        "./src/tool/**.cpp"
    }

    links {
        "xsk-gsc-utils",
        "xsk-gsc-h1",
        "xsk-gsc-h2",
        "xsk-gsc-iw5",
        "xsk-gsc-iw6",
        "xsk-gsc-iw7",
        "xsk-gsc-iw8",
        "xsk-gsc-iw9",
        "xsk-gsc-s1",
        "xsk-gsc-s2",
        "xsk-gsc-s4",
        "xsk-arc-t6",
        "xsk-gsc-iw5c",
        "xsk-gsc-iw6c",
        "xsk-gsc-s1c"
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

project "xsk-gsc-iw9"
    kind "StaticLib"
    language "C++"

    pchheader "stdafx.hpp"
    pchsource "src/iw9/stdafx.cpp"

    files {
        "./src/iw9/**.h",
        "./src/iw9/**.hpp",
        "./src/iw9/**.cpp"
    }

    includedirs {
        "./src/iw9",
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

project "xsk-gsc-iw5c"
    kind "StaticLib"
    language "C++"

    pchheader "stdafx.hpp"
    pchsource "src/experimental/iw5c/stdafx.cpp"

    files {
        "./src/experimental/iw5c/**.h",
        "./src/experimental/iw5c/**.hpp",
        "./src/experimental/iw5c/**.cpp"
    }

    includedirs {
        "./src/experimental/iw5c",
        "./src"
    }

project "xsk-gsc-iw6c"
    kind "StaticLib"
    language "C++"

    pchheader "stdafx.hpp"
    pchsource "src/experimental/iw6c/stdafx.cpp"

    files {
        "./src/experimental/iw6c/**.h",
        "./src/experimental/iw6c/**.hpp",
        "./src/experimental/iw6c/**.cpp"
    }

    includedirs {
        "./src/experimental/iw6c",
        "./src"
    }

project "xsk-gsc-s1c"
    kind "StaticLib"
    language "C++"

    pchheader "stdafx.hpp"
    pchsource "src/experimental/s1c/stdafx.cpp"

    files {
        "./src/experimental/s1c/**.h",
        "./src/experimental/s1c/**.hpp",
        "./src/experimental/s1c/**.cpp"
    }

    includedirs {
        "./src/experimental/s1c",
        "./src"
    }

group "Dependencies"
    zlib:project()
