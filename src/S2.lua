S2 = {}

function S2:include()
    includedirs { path.join(project_folder(), "S2") }
end

function S2:link()
    self:include()
    links { "S2" }
end

function S2:project()
    local folder = project_folder();

    project "S2"
        kind "StaticLib"
        language "C++"

        files
        {
            path.join(folder, "S2/**.h"),
            path.join(folder, "S2/**.hpp"),
            path.join(folder, "S2/**.cpp")
        }

        self:include()
        utils:include()
end
