H1 = {}

function H1:include()
    includedirs { path.join(project_folder(), "H1") }
end

function H1:link()
    self:include()
    links { "H1" }
end

function H1:project()
    local folder = project_folder();

    project "H1"
        kind "StaticLib"
        language "C++"

        files
        {
            path.join(folder, "H1/**.h"),
            path.join(folder, "H1/**.hpp"),
            path.join(folder, "H1/**.cpp")
        }

        self:include()
        utils:include()
end
