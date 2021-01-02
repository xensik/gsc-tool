IW7 = { base = path.join(projects.base, "IW7") }

function IW7:include()
    includedirs { IW7.base }
end

function IW7:link()
    links { "IW7" }
    self:include()
end

function IW7:project()
    project "IW7"
    kind "StaticLib"
    language "C++"

    pchheader "IW7.hpp"
    pchsource(path.join(IW7.base, "IW7.cpp"))

    self:include()
    utils:include()

    files
    {
        path.join(IW7.base, "**.h"),
        path.join(IW7.base, "**.hpp"),
        path.join(IW7.base, "**.cpp")
    }
end
