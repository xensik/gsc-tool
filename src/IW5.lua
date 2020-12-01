IW5 = {}

function IW5:include()
    includedirs
    {
        path.join(project_dir(), "IW5")
    }
end

function IW5:link()
    self:include()
    links
    {
        "IW5"
    }
end

function IW5:project()
    local folder = project_dir();

    project "IW5"
        kind "StaticLib"
        language "C++"

        files
        {
            path.join(folder, "IW5/**.h"),
            path.join(folder, "IW5/**.hpp"),
            path.join(folder, "IW5/**.cpp")
        }

        self:include()
        utils:include()
end