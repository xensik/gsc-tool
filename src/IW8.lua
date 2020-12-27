IW8 = {}

function IW8:include()
    includedirs { path.join(project_folder(), "IW8") }
end

function IW8:link()
    self:include()
    links { "IW8" }
end

function IW8:project()
    local folder = project_folder();

    project "IW8"
        kind "StaticLib"
        language "C++"

        files
        {
            path.join(folder, "IW8/**.h"),
            path.join(folder, "IW8/**.hpp"),
            path.join(folder, "IW8/**.cpp")
        }

        self:include()
        utils:include()
end
