cxxopts = { base = path.join(dependencies.base, "cxxopts") }

function cxxopts:include()
    includedirs { path.join(cxxopts.base, "include") }
end

function cxxopts:link()
    self:include()
end

table.insert(dependencies, cxxopts)
