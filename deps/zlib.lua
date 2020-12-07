zlib = { source = path.join(dependencies.basePath, "zlib") }

function zlib:include()
    includedirs { zlib.source }
end

function zlib:link()
    zlib.include()
    links { "zlib" }
end

function zlib:project()
    project "zlib"
        kind "StaticLib"
        language "C"
        
        zlib.include()

        files
        { 
            path.join(zlib.source, "*.h"),
            path.join(zlib.source, "*.c")
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
