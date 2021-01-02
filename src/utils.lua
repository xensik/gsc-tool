utils = { base = path.join(projects.base, "utils") }

function utils:include()
    includedirs { utils.base }
end

function utils:link()
    links { "utils" }
    self:include()
end

function utils:project()
    project "utils"
    kind "StaticLib"
    language "C++"

    pchheader "utils.hpp"
    pchsource(path.join(utils.base, "utils.cpp"))

    self:include()
    zlib:include()

    files
    {
        path.join(utils.base, "**.h"),
        path.join(utils.base, "**.hpp"),
        path.join(utils.base, "**.cpp")
    }
end
