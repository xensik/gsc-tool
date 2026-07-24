catch2 = { base = path.join(dependencies.base, "catch2") }

function catch2:include()
    externalincludedirs { path.join(catch2.base, "extras") }
end

function catch2:link()
    links { "catch2" }
    self:include()
end

function catch2:project()
    project "catch2"
    kind "StaticLib"
    language "C++"
    warnings "off"
    defines "CATCH_AMALGAMATED_CUSTOM_MAIN"

    self:include()

    files {
        path.join(catch2.base, "extras/catch_amalgamated.hpp"),
        path.join(catch2.base, "extras/catch_amalgamated.cpp"),
    }
end

table.insert(dependencies, catch2)
