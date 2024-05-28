project(App VERSION 0.1 LANGUAGES CXX)
string(REGEX REPLACE "(.*)/(.*)" "\\1" PROJECT_CTK_DIR  ${PROJECT_SOURCE_DIR})

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

include_directories(${PROJECT_CTK_DIR}/ctk/ctkCore/include ${PROJECT_CTK_DIR}/ctk/ctkPluginFramework ${PROJECT_CTK_DIR}/ctk/ctkPluginFramework/include)

find_package(Qt5 REQUIRED COMPONENTS Widgets Core Gui)

add_executable(${PROJECT_NAME} "main.cpp")

add_dependencies(${PROJECT_NAME} ctkPluginFramework)
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Gui Qt5::Widgets ctkPluginFramework)

set_target_properties(${PROJECT_NAME} PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)