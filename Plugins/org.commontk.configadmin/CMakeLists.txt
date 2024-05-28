project(configadmin)

string(REGEX REPLACE "(.*)/(.*)/(.*)" "\\1" PROJECT_CTK_DIR  ${PROJECT_SOURCE_DIR})

set(PLUGIN_NAME org.commontk.configadmin)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(BUILD_SHARED_LIBS ON)


find_package(Qt5 REQUIRED COMPONENTS Widgets Core Gui Concurrent REQUIRED)
add_definitions(-DHAVE_QT5)

macro(SEARCH_FILE list dir)
    file(GLOB_RECURSE children "${dir}/*.h" "${dir}/*.hpp" "${dir}/*.c" "${dir}/*.cpp" "${dir}/*.ui")
    set(${list} ${children})
endmacro()
SEARCH_FILE(PLUGIN_RES_LIST ${PROJECT_CTK_DIR}/Plugins/${PLUGIN_NAME})

file(GLOB_RECURSE QRC_SOURCE_FILES ${PROJECT_CTK_DIR}/Plugins/${PLUGIN_NAME}/*.qrc)
qt5_add_resources(QRC_FILES ${QRC_SOURCE_FILES})


include_directories(${PROJECT_CTK_DIR}/ctk/ctkCore/include ${PROJECT_CTK_DIR}/ctk/ctkPluginFramework ${PROJECT_CTK_DIR}/ctk/ctkPluginFramework/include)

add_library(${PROJECT_NAME} ${PLUGIN_RES_LIST} ${QRC_FILES})
add_dependencies(${PROJECT_NAME} ctkPluginFramework)
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Concurrent ctkPluginFramework)



set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin/Release/plugins
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin/Debug/plugins
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/lib/Release/plugins
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/lib/Debug/plugins
    LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/lib/Release/plugins
    LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/lib/Debug/plugins
)
