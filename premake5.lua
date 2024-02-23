output_dir = "%{cfg.buildcfg}-%{cfg.system}"
include_dir = {}
lib_dir = {}
env = {}

include_dir["MoonlightVxl"] = "MoonlightVxl/include/"
MoonlightVxl_src = "MoonlightVxl/src/"

include_dir["Moonloit"] = "Moonloit/include/"
moonloit_src = "Moonloit/src/"

include_dir["submods"] = "MoonlightVxl/submods/"

include_dir["glad"] = "Moonloit/external/glad/include"
include_dir["spdlog"] = "Moonloit/submods/spdlog/include/"
include_dir["glm"] = "Moonloit/submods/glm/"

include_dir["glfw3"] = "MoonlightVxl/submods/glfw3/include/"
include_dir["imgui"] = "MoonlightVxl/submods/imgui/"

include "Moonloit"

project "MoonlightVxl"
    location "%{prj.name}"
    kind "StaticLib" -- dll

    staticruntime "off"

    language "C++"
    cppdialect "C++17"
      
    targetdir("bin/" ..  output_dir .. "/%{prj.name}/")
    objdir("bin-int/" ..  output_dir .. "/%{prj.name}/")

    pchheader "vxl_pch.hpp"
    pchsource "MoonlightVxl/src/MoonlightVxl/vxl_pch.cpp"

    files {
        "%{prj.name}/include/**.hpp",
        "%{prj.name}/include/**.h",
        "%{prj.name}/src/**.hpp",
        "%{prj.name}/src/**.cpp",
		"%{prj.name}/src/**.h",
        "%{prj.name}/src/**.c"
    }
    includedirs {
        "%{prj.name}/src/",
        "%{prj.name}/src/MoonlightVxl",
        "%{include_dir.MoonlightVxl}",
        "%{include_dir.MoonlightVxl}MoonlightVxl",
        "%{include_dir.Moonloit}",
        "%{include_dir.Moonloit}Moonloit",
        "%{moonloit_src}",
        "%{moonloit_src}Moonloit",
        "%{include_dir.spdlog}",
        "%{include_dir.glfw3}",
        "%{include_dir.glad}",
        "%{include_dir.glm}",
        "%{include_dir.imgui}",
		os.getenv("VULKAN_SDK") .. "/Include/",
        "%{include_dir.submods}"
    }
	libdirs {
		os.getenv("VULKAN_SDK") .. "/Lib/"
	}
	
    links {
        "Moonloit",
        "glfw3",
        "imgui",
		"vulkan-1"
    }
    defines {
        "VXL_STATIC_LIB",
        "GLAD_GLAPI_EXPORT"
    }

    filter "system:windows"
        systemversion "latest"
        buildoptions {
            "/Zc:__cplusplus"
        }
        
        defines {
            "MLT_PLATFORM_WINDOWS"
        }

    filter "system:linux"
        systemversion "latest"
        toolset "clang"

        defines {
            "MLT_PLATFORM_LINUX"
        }

    filter "configurations:dbg"
        symbols "On"
        defines {
            "MLT_DEBUG",
            "MLT_ASSERTIONS_ENABLED"
        }
    filter "configurations:rel"
        optimize "speed"
        symbols "off"
        defines {
            "MLT_RELEASE"
        }
    filter "configurations:dist"
        optimize "speed"
        symbols "off"
        defines {
            "MLT_DISTRIBUTION"
        }



project "glfw3"
    location "MoonlightVxl/submods/%{prj.name}"

    kind "StaticLib"
    language "C"
    staticruntime "off"
    warnings "off"

    targetdir ("bin/" .. output_dir .. "/%{prj.name}")
    objdir ("bin-int/" .. output_dir .. "/%{prj.name}")

    files {
        "%{prj.location}/include/GLFW/glfw3.h",
        "%{prj.location}/include/GLFW/glfw3native.h",
        "%{prj.location}/src/glfw_config.h",
        "%{prj.location}/src/context.c",
        "%{prj.location}/src/init.c",
        "%{prj.location}/src/input.c",
        "%{prj.location}/src/monitor.c",

        "%{prj.location}/src/null_init.c",
        "%{prj.location}/src/null_joystick.c",
        "%{prj.location}/src/null_monitor.c",
        "%{prj.location}/src/null_window.c",

        "%{prj.location}/src/platform.c",
        "%{prj.location}/src/vulkan.c",
        "%{prj.location}/src/window.c",
    }

    filter "system:linux"
        pic "On"
        systemversion "latest"
        
        files {
            "%{prj.location}/src/x11_init.c",
            "%{prj.location}/src/x11_monitor.c",
            "%{prj.location}/src/x11_window.c",
            "%{prj.location}/src/xkb_unicode.c",
            "%{prj.location}/src/posix_module.c",
            "%{prj.location}/src/posix_time.c",
            "%{prj.location}/src/posix_thread.c",
            "%{prj.location}/src/posix_module.c",
            "%{prj.location}/src/glx_context.c",
            "%{prj.location}/src/egl_context.c",
            "%{prj.location}/src/osmesa_context.c",
            "%{prj.location}/src/linux_joystick.c"
        }

        defines {
            "_GLFW_X11"
        }

    filter "system:macosx"
        pic "On"

        files {
            "%{prj.location}/src/cocoa_init.m",
            "%{prj.location}/src/cocoa_monitor.m",
            "%{prj.location}/src/cocoa_window.m",
            "%{prj.location}/src/cocoa_joystick.m",
            "%{prj.location}/src/cocoa_time.c",
            "%{prj.location}/src/nsgl_context.m",
            "%{prj.location}/src/posix_thread.c",
            "%{prj.location}/src/posix_module.c",
            "%{prj.location}/src/osmesa_context.c",
            "%{prj.location}/src/egl_context.c"
        }

        defines {
            "_GLFW_COCOA"
        }

    filter "system:windows"
        systemversion "latest"

        files {
            "%{prj.location}/src/win32_init.c",
            "%{prj.location}/src/win32_joystick.c",
            "%{prj.location}/src/win32_module.c",
            "%{prj.location}/src/win32_monitor.c",
            "%{prj.location}/src/win32_time.c",
            "%{prj.location}/src/win32_thread.c",
            "%{prj.location}/src/win32_window.c",
            "%{prj.location}/src/wgl_context.c",
            "%{prj.location}/src/egl_context.c",
            "%{prj.location}/src/osmesa_context.c"
        }

        defines  { 
            "_GLFW_WIN32",
            "_CRT_SECURE_NO_WARNINGS"
        }

    filter "configurations:dbg"
        runtime "Debug"
        symbols "on"

    filter "configurations:rel"
        runtime "Release"
        optimize "speed"
        symbols "off"

    filter "configurations:dist"
        runtime "Release"
        optimize "speed"
        symbols "off"

project "imgui" 
    location "MoonlightVxl/submods/%{prj.name}"

    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    
    staticruntime "off"
    systemversion "latest"

    targetdir ("bin/" .. output_dir .. "/%{prj.name}")
    objdir ("bin-int/" .. output_dir .. "/%{prj.name}")

    files {
        "%{prj.location}/imconfig.h",
        "%{prj.location}/imgui_demo.cpp",
        "%{prj.location}/imgui_draw.cpp",
        "%{prj.location}/imgui_internal.h",
        "%{prj.location}/imgui_tables.cpp",
        "%{prj.location}/imgui_widgets.cpp",
        "%{prj.location}/imgui.cpp",
        "%{prj.location}/imgui.h",
        "%{prj.location}/imstb_rectpack.h",
        "%{prj.location}/imstb_textedit.h",
        "%{prj.location}/imstb_truetype.h",
        "%{prj.location}/backends/imgui_impl_opengl3.cpp",
        "%{prj.location}/backends/imgui_impl_opengl3.h",
        "%{prj.location}/backends/imgui_impl_opengl3_loader.h",
        "%{prj.location}/backends/imgui_impl_glfw.cpp",
        "%{prj.location}/backends/imgui_impl_glfw.h",
    }

    includedirs {
        "%{include_dir.imgui}",
        "%{include_dir.glfw3}"
    }

    filter "system:linux"
        pic "On"

    filter "configurations:dbg"
        runtime "Debug"
        symbols "on"

    filter "configurations:rel"
        runtime "Release"
        optimize "speed"
        symbols "off"

    filter "configurations:dist"
        runtime "Release"
        optimize "speed"
        symbols "off"