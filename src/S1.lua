S1 = { base = path.join(projects.base, "S1") }

function S1:include()
    includedirs { S1.base }
end

function S1:link()
    links { "S1" }
    self:include()
end

function S1:project()
    project "S1"
    kind "StaticLib"
    language "C++"

    -- pchheader "S1.hpp"
    -- pchsource(path.join(S1.base, "S1.cpp"))

    self:include()
    utils:include()

    files
    {
        path.join(S1.base, "**.h"),
        path.join(S1.base, "**.hpp"),
        path.join(S1.base, "**.cpp")
    }
end
