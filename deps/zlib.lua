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

    if os.istarget("linux") or os.istarget("macosx") then
        defines {
            "HAVE_UNISTD_H"
        }
    elseif os.istarget("windows") then
        defines {
            "_CRT_SECURE_NO_WARNINGS",
            "_CRT_NONSTDC_NO_DEPRECATE",
            "_CRT_SECURE_NO_DEPRECATE",
        }
    end

    self:include()

    files {
        path.join(zlib.base, "*.h"),
        path.join(zlib.base, "*.c")
    }
end

table.insert(dependencies, zlib)
