project(ctkPluginFramework)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(BUILD_SHARED_LIBS ON)

string(REGEX REPLACE "(.*)/(.*)/(.*)" "\\1" PROJECT_CTK_DIR  ${PROJECT_SOURCE_DIR})

include_directories(include)

add_definitions(-DPLUGINFRAMEWORK_LIBRARY)

macro(SEARCH_FILE list dir)
    file(GLOB_RECURSE children "${dir}/*.h" "${dir}/*.hpp" "${dir}/*.c" "${dir}/*.cpp")
    set(${list} ${children})
endmacro()

SEARCH_FILE(PLUGIN_RES_LIST ${PROJECT_CTK_DIR}/ctk/${PROJECT_NAME})


add_library(${PROJECT_NAME} ${PLUGIN_RES_LIST})

include_directories(${PROJECT_CTK_DIR}/ctk/ctkCore/include)

find_package(Qt5 REQUIRED COMPONENTS Core Sql Concurrent)
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Sql Qt5::Concurrent ctkCore)


# 针对多配置生成器，可以设置不同配置的输出目录
set_target_properties(${PROJECT_NAME} PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)