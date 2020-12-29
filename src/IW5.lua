IW5 = { base = path.join(projects.base, "IW5") }

function IW5:include()
    includedirs { IW5.base }
end

function IW5:link()
    links { "IW5" }
    self:include()
end

function IW5:project()
    project "IW5"
    kind "StaticLib"
    language "C++"

    self:include()
    utils:include()

    files
    {
        path.join(IW5.base, "**.h"),
        path.join(IW5.base, "**.hpp"),
        path.join(IW5.base, "**.cpp")
    }
end
