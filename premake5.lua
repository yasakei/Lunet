workspace "Lunet"
    configurations {"debug", "release"}

project "Lunet"
    language "c++"
    kind "ConsoleApp"
    targetdir "build"
    location "build"

    files {"src/**.cpp", "src/**.h"}

    includedirs {"src", "src/include/fmt"}

    filter "configurations:debug"
        defines {"DEBUG"}
        symbols "On"

    filter "configurations:release"
        defines {"NDEBUG"}
        optimize "On"