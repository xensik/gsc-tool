H1 = { base = path.join(projects.base, "H1") }

function H1:include()
    includedirs { H1.base }
end

function H1:link()
    links { "H1" }
    self:include()
end

function H1:project()
    project "H1"
    kind "StaticLib"
    language "C++"

    -- pchheader "H1.hpp"
    -- pchsource(path.join(H1.base, "H1.cpp"))

    self:include()
    utils:include()

    files
    {
        path.join(H1.base, "**.h"),
        path.join(H1.base, "**.hpp"),
        path.join(H1.base, "**.cpp")
    }
end
