IW7 = {}

function IW7:include()
    includedirs { path.join(project_folder(), "IW7") }
end

function IW7:link()
    self:include()
    links { "IW7" }
end

function IW7:project()
    local folder = project_folder();

    project "IW7"
        kind "StaticLib"
        language "C++"

        files
        {
            path.join(folder, "IW7/**.h"),
            path.join(folder, "IW7/**.hpp"),
            path.join(folder, "IW7/**.cpp")
        }

        self:include()
        utils:include()
end
