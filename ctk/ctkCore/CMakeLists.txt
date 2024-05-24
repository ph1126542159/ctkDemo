project(ctkCore)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(BUILD_SHARED_LIBS ON)


add_definitions(-DPluginFramework_CORE_LIBRARY)

# 设置包含目录
include_directories(include)
# 添加所有.h文件
file(GLOB HEADERS "include/*.h")
# 添加所有.tpp文件
file(GLOB TEMPLATES "include/*.tpp")
# 添加所有.cpp文件
file(GLOB SOURCES "src/*.cpp")

add_library(${PROJECT_NAME} ${HEADERS} ${TEMPLATES} ${SOURCES})

if(WIN32)
    # 查找 Dbghelp 库并链接到项目中
    find_library(DBGHELP_LIBRARY dbghelp)
    if(DBGHELP_LIBRARY)
        target_link_libraries(${PROJECT_NAME} ${DBGHELP_LIBRARY})
    endif()
endif()

find_package(Qt5 REQUIRED COMPONENTS Core)
target_link_libraries(${PROJECT_NAME} Qt5::Core)


# 针对多配置生成器，可以设置不同配置的输出目录
set_target_properties(${PROJECT_NAME} PROPERTIES
    DEBUG_POSTFIX "d"
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)