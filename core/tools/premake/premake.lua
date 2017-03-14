solution "encoding"
  configurations { "Debug", "Release" } 
  location "../../code"

  includedirs {
    "../../code/Server/inc",
    "../../code/Server/ServerCore",
  }

  defines{"_DEBUG","_SERVER","WIN32","_WINDOWS","_LIB","MY_CMD","_STANDALONE","_OPENALLFUNCTION","NO_DIRECT_X","_USE_32BIT_TIME_T"}
  language "C++"

  project "main"
    location "../../code/main"
    kind "ConsoleApp"
    files { "../../code/main/**.h", "../../code/main/**.cpp"}
    links {"libmysql"}
    libdirs{"../../code/share/library/Debug"}
    targetdir "../../bin"
    debugdir "../../bin"
      configuration "Debug"
        defines { "DEBUG" }
        flags { "Symbols" }
      configuration "Release"
        defines { "NDEBUG" }
        flags { "Optimize" }

  project "detection"
    location "../../code/detection"
    kind "StaticLib"
    files { "../../code/detection/**.h", "../../code/detection/**.cpp"}
    targetdir "code/Share/Lib/Debug"
    targetname "detection"
      configuration "Debug"
        flags { "Symbols","FatalWarnings" }
      configuration "Release"
        defines { "NDEBUG" }
        flags { "Optimize", "FatalWarnings"}

  project "Share"
    location "../../code/share"
    kind "StaticLib"
    files { "code/share/**.h"}
    targetdir "code/Share/library/Debug"
    targetname "share"
      configuration "Debug"
        flags { "Symbols" }
      configuration "Release"
        defines { "NDEBUG" }
        flags { "Optimize" }

