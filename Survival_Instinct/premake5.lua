workspace "Survival_Instinct"
    architecture "x64"
    
    configurations { "Debug",  "Release"}
    outputdir="%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Survival_Instinct"
    location "Survival_Instinct"
    kind "ConsoleApp"
    language "c"

    targetdir("bin/bin/" ..outputdir.."/%{prj.name}")
    objdir("bin/intermediates/" ..outputdir.."/%{prj.name}")
    
    files
    {
        "%{prj.name}/Game/**.h",
        "%{prj.name}/Game/**.c",
        "%{prj.name}/source/**.h",
        "%{prj.name}/source/**.c"      
    }

    includedirs
    {
        "%{prj.name}/Game",
        "%{prj.name}/source"
    }

    defines
    {
        "_CRT_SECURE_NO_WARNINGS"
    }

    filter "system:windows"
        cdialect "C11"
        systemversion "latest"

    filter "configurations:Debug"
        defines {"DEBUG"}
        symbols "on"

    filter "configurations:Release"
        defines {"NDEBUG"}
        optimize "on"
            