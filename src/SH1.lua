SH1 = {}

function SH1:include()
    includedirs { path.join(project_folder(), "SH1") }
end

function SH1:link()
    self:include()
    links { "SH1" }
end

function SH1:project()
    local folder = project_folder();

    project "SH1"
        kind "StaticLib"
        language "C++"

        files
        {
            path.join(folder, "SH1/**.h"),
            path.join(folder, "SH1/**.hpp"),
            path.join(folder, "SH1/**.cpp")
        }

        self:include()
        utils:include()
end
