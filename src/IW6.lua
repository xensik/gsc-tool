IW6 = {}

function IW6:include()
    includedirs { path.join(project_folder(), "IW6") }
end

function IW6:link()
    self:include()
    links { "IW6" }
end

function IW6:project()
    local folder = project_folder();

    project "IW6"
        kind "StaticLib"
        language "C++"

        files
        {
            path.join(folder, "IW6/**.h"),
            path.join(folder, "IW6/**.hpp"),
            path.join(folder, "IW6/**.cpp")
        }

        self:include()
        utils:include()
end
