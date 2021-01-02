H2 = { base = path.join(projects.base, "H2") }

function H2:include()
    includedirs { H2.base }
end

function H2:link()
    links { "H2" }
    self:include()
end

function H2:project()
    project "H2"
    kind "StaticLib"
    language "C++"

    -- pchheader "H2.hpp"
    -- pchsource(path.join(H2.base, "H2.cpp"))

    self:include()
    utils:include()

    files
    {
        path.join(H2.base, "**.h"),
        path.join(H2.base, "**.hpp"),
        path.join(H2.base, "**.cpp")
    }
end
