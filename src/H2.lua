H2 = {}

function H2:include()
    includedirs { path.join(project_folder(), "H2") }
end

function H2:link()
    self:include()
    links { "H2" }
end

function H2:project()
    local folder = project_folder();

    project "H2"
        kind "StaticLib"
        language "C++"

        files
        {
            path.join(folder, "H2/**.h"),
            path.join(folder, "H2/**.hpp"),
            path.join(folder, "H2/**.cpp")
        }

        self:include()
        utils:include()
end
