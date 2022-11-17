cmake_minimum_required(VERSION 3.21)

project(MySkseLibrary.ClientTwo VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(CommonLibSSE CONFIG REQUIRED)
find_package(MySkseLibraryExample CONFIG REQUIRED)

file(GLOB_RECURSE SOURCE_FILES src/*.cpp src/*.h include/*.h)

add_commonlibsse_plugin(${PROJECT_NAME} SOURCES ${SOURCE_FILES})
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)
include_directories(${PROJECT_NAME} include)
target_precompile_headers(${PROJECT_NAME} PUBLIC src/PCH.h)

# set(CMAKE_BUILD_TYPE "Debug")
target_link_libraries(${PROJECT_NAME} PRIVATE MySkseLibraryExample::MySkseLibraryExample)
# set_property(TARGET MySkseLibraryExample::MySkseLibraryExample PROPERTY IMPORTED_LOCATION "C:/Users/mrowr/Dropbox/Skyrim/Purrrect Modlist/Mods/Example - SKSE Library Client/build/debug-msvc/vcpkg_installed/x64-windows-static-md/bin/MySkseLibraryExample.dll")

add_custom_command(
	TARGET "${PROJECT_NAME}"
	POST_BUILD
	COMMAND "${CMAKE_COMMAND}" -E copy_if_different "$<TARGET_FILE:${PROJECT_NAME}>" "${PROJECT_SOURCE_DIR}/SKSE/Plugins/${PROJECT_NAME}.dll"
	COMMAND "${CMAKE_COMMAND}" -E copy_if_different "$<TARGET_PDB_FILE:${PROJECT_NAME}>" "${PROJECT_SOURCE_DIR}/SKSE/Plugins/${PROJECT_NAME}.pdb"
	VERBATIM
)
