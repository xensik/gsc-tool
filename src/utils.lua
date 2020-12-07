utils = {}

function utils:include()
    includedirs { path.join(project_folder(), "utils") }
end

function utils:link()
    self:include()
    links { "utils" }
end

function utils:project()
    local folder = project_folder();

    project "utils"
        kind "StaticLib"
        language "C++"
        
        pchheader "utils.hpp"
        pchsource(path.join(folder, "utils/utils.cpp"))

        files
        {
            path.join(folder, "utils/**.h"),
            path.join(folder, "utils/**.hpp"),
            path.join(folder, "utils/**.cpp")
        }
        
        self:include()
        zlib:include()
end
