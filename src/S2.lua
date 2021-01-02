S2 = { base = path.join(projects.base, "S2") }

function S2:include()
    includedirs { S2.base }
end

function S2:link()
    links { "S2" }
    self:include()
end

function S2:project()
    project "S2"
    kind "StaticLib"
    language "C++"

    -- pchheader "S2.hpp"
    -- pchsource(path.join(S2.base, "S2.cpp"))

    self:include()
    utils:include()

    files
    {
        path.join(S2.base, "**.h"),
        path.join(S2.base, "**.hpp"),
        path.join(S2.base, "**.cpp")
    }
end
