IW8 = { base = path.join(projects.base, "IW8") }

function IW8:include()
    includedirs { IW8.base }
end

function IW8:link()
    links { "IW8" }
    self:include()
end

function IW8:project()
    project "IW8"
    kind "StaticLib"
    language "C++"

    self:include()
    utils:include()

    files
    {
        path.join(IW8.base, "**.h"),
        path.join(IW8.base, "**.hpp"),
        path.join(IW8.base, "**.cpp")
    }
end
