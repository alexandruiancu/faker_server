cmake_minimum_required( VERSION 3.20 )
project( transaction-generator )

include(GNUInstallDirs)

# Place CXX flags here or later ?
set( CMAKE_CXX_STANDARD 23 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_CXX_EXTENSIONS OFF )


set(DUKTAPE_VERSION "2.7.0")
#set(DUKTAPE_URL "https://github.com/svaarala/duktape/releases/download/v${DUKTAPE_VERSION}/duktape-${DUKTAPE_VERSION}.tar.xz")
set(DUKTAPE_URL "https://duktape.org/duktape-${DUKTAPE_VERSION}.tar.xz")
#set(DUKTAPE_INSTALL_DIR "${CMAKE_CURRENT_BINARY_DIR}/external/duktape")

#include(FetchContent)
#FetchContent_Declare(
#    Duktape
#    URL ${DUKTAPE_URL}
#)
#
#FetchContent_MakeAvailable(Duktape)
#
## Add include directories
#include_directories(${Duktape_SOURCE_DIR}/src)  # Adjust as needed

############################

#include(ExternalProject)
#
#set(DUKTAPE_VERSION "2.7.0")
#set(DUKTAPE_URL "https://github.com/svaarala/duktape/releases/download/v${DUKTAPE_VERSION}/duktape-${DUKTAPE_VERSION}.tar.xz")
#set(DUKTAPE_INSTALL_DIR "${CMAKE_CURRENT_BINARY_DIR}/external/duktape")
#
#ExternalProject_Add(
#    duktape
#    URL ${DUKTAPE_URL}
#    PREFIX ${DUKTAPE_INSTALL_DIR}
#    INSTALL_COMMAND ""
#)

############################

# add package manager
include(cmake/CPM.cmake)

# Add include directories for Duktape after it's downloaded
#include_directories(${DUKTAPE_INSTALL_DIR}/src)  # Adjust the path as necessary
#CPMAddPackage("gh:svaarala/duktape@2.7.0")
CPMAddPackage(
    NAME Duktape
    URL "${DUKTAPE_URL}"
    OPTIONS
        "CPM_SOURCE_DIR ${CMAKE_CURRENT_BINARY_DIR}/duktape-src/"
)

#set(include_DIR "${transaction-generator_SOURCE_DIR}/include")
include_directories("${Duktape_SOURCE_DIR}/src")
#target_include_directories (transaction-generator PRIVATE "${Duktape_SOURCE_DIR}")

add_executable(transaction-generator "driver.cpp" "${Duktape_SOURCE_DIR}/src/duktape.c")
#
#target_link_libraries(transaction-generator PRIVATE 
#    # duktape
#    Duktape
#)

add_custom_command(TARGET transaction-generator POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/fakerjs
    $<TARGET_FILE_DIR:transaction-generator>/fakerjs
    COMMENT "useful when running without install, from build directory"
)

# Set the install prefix
# use command line -DCMAKE_INSTALL_PREFIX=${workspaceFolder}/build/opt to set prefix

# Install the dependency's targets if they are exported
# Note: This assumes the dependency properly exports its targets
install(TARGETS 
    transaction-generator 

    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

# Optional: Install any additional files (configs, resources, etc.)
install(DIRECTORY 
    ${CMAKE_CURRENT_SOURCE_DIR}/fakerjs
    DESTINATION ${CMAKE_INSTALL_BINDIR}
)
