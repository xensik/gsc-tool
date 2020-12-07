zlib = {}

function zlib:include()
    includedirs { path.join(deps_folder(), "zlib") }
end

function zlib:link()
    zlib.include()
    links { "zlib" }
end

function zlib:project()
    local folder = path.join(deps_folder(), "zlib");

    project "zlib"
        kind "StaticLib"
        language "C"
        
        zlib.include()

        files
        { 
            path.join(folder, "*.h"),
            path.join(folder, "*.c")
        }
        
        defines
        {
            "_CRT_SECURE_NO_WARNINGS",
            "_CRT_NONSTDC_NO_DEPRECATE",
            "_CRT_SECURE_NO_DEPRECATE",
        }

        warnings "off"
end

table.insert(dependencies, zlib)
