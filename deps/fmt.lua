fmt = { base = path.join(dependencies.base, "fmt") }

function fmt:include()
    includedirs { path.join(fmt.base, "include") }
end

function fmt:link()
    links { "fmt" }
    self:include()
end

function fmt:project()
    project "fmt"
    kind "StaticLib"
    language "C++"

    self:include()

    files
    {
        path.join(fmt.base, "include/fmt/*.h"),
        path.join(fmt.base, "src/*.cc")
    }

    removefiles
    {
        path.join(fmt.base, "src/fmt.cc")
    }
end

table.insert(dependencies, fmt)
