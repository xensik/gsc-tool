workspace "gsc-tool"
	location "./build"
	objdir "%{wks.location}/obj"
	targetdir "%{wks.location}/bin"
	targetname "%{prj.name}-%{cfg.platform}-%{cfg.buildcfg}"
	warnings "Off"

	configurations {
		"debug",
		"release",
	}

	platforms { 
		"win32",
		"win64",
	}

	filter "platforms:win32"
		architecture "x86"
		defines "CPU_32BIT"
	filter {}

	filter "platforms:win64"
		architecture "x86_64"
		defines "CPU_64BIT"
	filter {}

	buildoptions "/std:c++latest"
	systemversion "latest"
	symbols "On"
	editandcontinue "Off"

	flags {
		"NoIncrementalLink",
		"NoMinimalRebuild",
		"MultiProcessorCompile",
		"No64BitChecks"
	}

	configuration "windows"
		defines {
			"_WINDOWS",
			"WIN32",
		}
	configuration{}

	configuration "release"
		optimize "Full"
		defines {
			"NDEBUG",
		}
	configuration{}

	configuration "debug"
		optimize "Debug"
		defines {
			"DEBUG",
			"_DEBUG",
		}
	configuration {}

	startproject "gsc-app"

	-- ========================
	-- Projects
	-- ========================

	project "gsc-lib"
		kind "StaticLib"
		language "C++"
		
		pchheader "stdinc.hpp"
		pchsource "stdinc.cpp"

		files {
			"./src/gsc-lib/**.h",
			"./src/gsc-lib/**.hpp",
			"./src/gsc-lib/**.cpp",
		}

		syslibdirs {
			"./build/bin",
		}

		includedirs {
			"./src/gsc-lib",
			"%{prj.location}/src/gsc-lib",
		}

	project "gsc-app"
		kind "ConsoleApp"
		language "C++"
		
		files {
			"./src/gsc-app/**.h",
			"./src/gsc-app/**.hpp",
			"./src/gsc-app/**.cpp",
		}

		links {
			"gsc-lib"
		}

		syslibdirs {
			"./build/bin",
		}

		includedirs {
			"./src/gsc-app",
			"./src/gsc-lib",
			"%{prj.location}/src",
		}
