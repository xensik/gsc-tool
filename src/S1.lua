S1 = {}

function S1:include()
    includedirs { path.join(project_folder(), "S1") }
end

function S1:link()
    self:include()
    links { "S1" }
end

function S1:project()
    local folder = project_folder();

    project "S1"
        kind "StaticLib"
        language "C++"

        files
        {
            path.join(folder, "S1/**.h"),
            path.join(folder, "S1/**.hpp"),
            path.join(folder, "S1/**.cpp")
        }

        self:include()
        utils:include()
end
