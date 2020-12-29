tool = { base = path.join(projects.base, "tool") }

function tool:include()
    includedirs { tool.base }
end

function tool:link()
    links { "gsc-tool" }
    self:include()
end

function tool:project()
    project "gsc-tool"
    kind "ConsoleApp"
    language "C++"

    pchheader "stdinc.hpp"
    pchsource(path.join(tool.base, "stdinc.cpp"))

    self:include()
    utils:link()
    zlib:link()
    IW5:link()
    IW6:link()
    IW7:link()
    S1:link()
    S2:link()
    H1:link()
    H2:link()

    files
    {
        path.join(tool.base, "**.h"),
        path.join(tool.base, "**.hpp"),
        path.join(tool.base, "**.cpp")
    }
end
