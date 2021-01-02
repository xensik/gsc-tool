IW6 = { base = path.join(projects.base, "IW6") }

function IW6:include()
    includedirs { IW6.base }
end

function IW6:link()
    links { "IW6" }
    self:include()
end

function IW6:project()
    project "IW6"
    kind "StaticLib"
    language "C++"

    pchheader "IW6.hpp"
    pchsource(path.join(IW6.base, "IW6.cpp"))

    self:include()
    utils:include()

    files
    {
        path.join(IW6.base, "**.h"),
        path.join(IW6.base, "**.hpp"),
        path.join(IW6.base, "**.cpp")
    }
end
