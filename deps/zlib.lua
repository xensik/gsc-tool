zlib = { base = path.join(dependencies.base, "zlib") }

function zlib:include()
    includedirs { zlib.base }
end

function zlib:link()
    links { "zlib" }
    self:include()
end

function zlib:project()
    project "zlib"
    kind "StaticLib"
    language "C"
    warnings "off"

    self:include()

    files
    {
        path.join(zlib.base, "*.h"),
        path.join(zlib.base, "*.c")
    }

    defines
    {
        "_CRT_SECURE_NO_WARNINGS",
        "_CRT_NONSTDC_NO_DEPRECATE",
        "_CRT_SECURE_NO_DEPRECATE",
    }
end

table.insert(dependencies, zlib)
