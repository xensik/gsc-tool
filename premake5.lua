-------------------------------------------------
-- DEPENDENCIES
-------------------------------------------------
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
-- VERSIONING
-------------------------------------------------
function version_split(version, revision)
    array = {}

    for num in string.gmatch(version or "", "%d+") do
        if #array < 3 then
            table.insert(array, tonumber(num))
        end
    end

    while #array < 3 do
        table.insert(array, 0)
    end

    table.insert(array, tonumber(revision))

    return array
end

function generate_version()
    -- get current version
    local proc1 = assert(io.popen("git describe --tags --abbrev=0", "r"))
    local version = assert(proc1:read('*a')):gsub("%s+", "")
    proc1:close()

    -- get current branch
    local proc2 = assert(io.popen("git symbolic-ref -q --short HEAD", "r"))
    local branch = assert(proc2:read('*a')):gsub("%s+", "")
    proc2:close()

    -- get revision number
    local proc3 = assert(io.popen("git rev-list --count HEAD", "r"))
    local revision = assert(proc3:read("*a")):gsub("%s+", "")
    proc3:close()

    local split = version_split(version, revision)
    local verstr = split[1] .. "." .. split[2] .. "." .. split[3] .. "." .. split[4]

    if branch ~= "" then
        verstr = verstr .. "-"  .. branch
    end

    local file = assert(io.open("include/xsk/version.hpp", "w"))
    file:write("// Generated by premake - do not edit\n\n")
    file:write("#define XSK_VERSION_MAJOR  " .. split[1] .. "\n")
    file:write("#define XSK_VERSION_MINOR  " .. split[2] .. "\n")
    file:write("#define XSK_VERSION_PATCH  " .. split[3] .. "\n")
    file:write("#define XSK_VERSION_BUILD  " .. split[4] .. "\n")
    file:write("#define XSK_VERSION_BRANCH \"" .. branch .. "\"\n")
    file:write("#define XSK_VERSION_STR    \"" .. verstr .. "\"\n")
    file:close()
end

generate_version()

-------------------------------------------------
-- PROJECTS
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
        platforms { "x86", "x64", "arm64" }
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

    symbols "On"
    staticruntime "On"
    warnings "Extra"

    if os.istarget("linux") or os.istarget("darwin") then
        buildoptions "-pthread"
        linkoptions "-pthread"
    end

    filter { "language:C++", "toolset:clang" }
        buildoptions "--target=aarch64-linux-gnu"
    filter {}

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
