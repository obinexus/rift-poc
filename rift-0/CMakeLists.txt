# RIFT Stage-0 Root CMake Configuration
# AEGIS Project - OBINexus Computing
# Build Flow: config/ → cmake/ → Makefile → build/obj → librift-0.{a,so} → bin/rift-N

cmake_minimum_required(VERSION 3.16)
project(RIFT_Stage0 
    VERSION 0.1.0
    DESCRIPTION "RIFT Language Stage-0 Tokenizer with Dual-Channel Output"
    LANGUAGES C
)

# ===================================================================
# Project Structure Configuration
# ===================================================================
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
set(RIFT_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(RIFT_INCLUDE_DIR ${RIFT_ROOT_DIR}/include)
set(RIFT_SOURCE_DIR ${RIFT_ROOT_DIR}/src)
set(RIFT_TEST_DIR ${RIFT_ROOT_DIR}/tests)
set(RIFT_CONFIG_DIR ${RIFT_ROOT_DIR}/config)

# Output directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_OBJECT_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/obj)

# ===================================================================
# Build Options
# ===================================================================
option(BUILD_SHARED_LIBS "Build shared libraries (.so)" ON)
option(BUILD_STATIC_LIBS "Build static libraries (.a)" ON)
option(BUILD_SOA_ARCHIVE "Build intermediate .so.a archive" ON)
option(ENABLE_QUANTUM_MODE "Enable quantum channel processing" ON)
option(AEGIS_COMPLIANCE "Enable AEGIS governance compliance" ON)
option(BUILD_TESTS "Build test suite" ON)
option(ENABLE_PANIC_MODE "Enable panic mode for critical errors" ON)
option(BUILD_EXAMPLES "Build example programs" OFF)

# ===================================================================
# Compiler Configuration
# ===================================================================
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Compiler flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wpedantic -fPIC")
set(CMAKE_C_FLAGS_DEBUG "-g -O0 -DDEBUG -DRIFT_DEBUG_MODE=1")
set(CMAKE_C_FLAGS_RELEASE "-O3 -DNDEBUG -DRIFT_RELEASE_MODE=1")

# Thread support
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

# ===================================================================
# Load CMake Modules
# ===================================================================
include(cmake/RIFTStage0.cmake)
include(cmake/rift_stage_macros.cmake)

# ===================================================================
# Configuration Processing
# ===================================================================
# Generate config header
configure_file(
    ${RIFT_INCLUDE_DIR}/rift-0/core/config.h.in
    ${CMAKE_BINARY_DIR}/rift_config.h
    @ONLY
)

# Generate governance files
generate_governance_file(0)

# ===================================================================
# Source File Organization
# ===================================================================
# Core library sources
set(RIFT_CORE_SOURCES
    ${RIFT_SOURCE_DIR}/core/rift-0.c
    ${RIFT_SOURCE_DIR}/core/gov/rift-gov.0.c
    ${RIFT_SOURCE_DIR}/core/gov/rift_sim.c
    ${RIFT_SOURCE_DIR}/core/gov/stage_queue.c
    ${RIFT_SOURCE_DIR}/core/lexer/lexer.c
    ${RIFT_SOURCE_DIR}/core/lexer/lexer_flag.c
    ${RIFT_SOURCE_DIR}/core/lexer/rift_tokenizer.c
    ${RIFT_SOURCE_DIR}/core/lexer/tokenizer.c
    ${RIFT_SOURCE_DIR}/core/lexer/tokenizer_match.c
    ${RIFT_SOURCE_DIR}/core/lexer/tokenizer_rules.c
    ${RIFT_SOURCE_DIR}/core/lexer/tokenizer_utilities.c
    ${RIFT_SOURCE_DIR}/core/ext/r_uml.c
)

# CLI sources
set(RIFT_CLI_SOURCES
    ${RIFT_SOURCE_DIR}/cli/main.c
    ${RIFT_SOURCE_DIR}/cli/commands/ext_command.c
    ${RIFT_SOURCE_DIR}/cli/commands/lexer_command.c
    ${RIFT_SOURCE_DIR}/cli/commands/r_command.c
    ${RIFT_SOURCE_DIR}/cli/commands/rift_gov_command.c
)

# ===================================================================
# Include Directories Configuration
# ===================================================================
# Set up include paths so files can be included as #include "rift-0/..."
include_directories(
    ${RIFT_INCLUDE_DIR}
    ${CMAKE_BINARY_DIR}  # For generated config headers
)

# ===================================================================
# Build Libraries
# ===================================================================
# Static library (.a)
if(BUILD_STATIC_LIBS)
    add_library(rift-stage0-static STATIC ${RIFT_CORE_SOURCES})
    set_target_properties(rift-stage0-static PROPERTIES
        OUTPUT_NAME "rift-0"
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}
        POSITION_INDEPENDENT_CODE ON
    )
    target_include_directories(rift-stage0-static PUBLIC
        $<BUILD_INTERFACE:${RIFT_INCLUDE_DIR}>
        $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}>
        $<INSTALL_INTERFACE:include>
    )
    configure_stage_target(rift-stage0-static 0)
endif()

# Shared library (.so)
if(BUILD_SHARED_LIBS)
    add_library(rift-stage0 SHARED ${RIFT_CORE_SOURCES})
    set_target_properties(rift-stage0 PROPERTIES
        OUTPUT_NAME "rift-0"
        VERSION ${PROJECT_VERSION}
        SOVERSION 0
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
    )
    target_include_directories(rift-stage0 PUBLIC
        $<BUILD_INTERFACE:${RIFT_INCLUDE_DIR}>
        $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}>
        $<INSTALL_INTERFACE:include>
    )
    configure_stage_target(rift-stage0 0)
endif()

# Intermediate .so.a archive (toolchain requirement)
if(BUILD_SOA_ARCHIVE AND BUILD_STATIC_LIBS)
    add_custom_target(rift-stage0-soa ALL
        COMMAND ${CMAKE_AR} rcs ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/librift-0.so.a 
                $<TARGET_OBJECTS:rift-stage0-static>
        DEPENDS rift-stage0-static
        COMMENT "Creating intermediate .so.a archive for toolchain"
    )
endif()

# ===================================================================
# Build Executables
# ===================================================================
# riftlang.exe - Stage-0 tokenizer executable
add_executable(riftlang.exe ${RIFT_CLI_SOURCES})
target_link_libraries(riftlang.exe PRIVATE
    $<IF:$<BOOL:${BUILD_SHARED_LIBS}>,rift-stage0,rift-stage0-static>
    Threads::Threads
)
set_target_properties(riftlang.exe PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
)

# rift-0 - CLI interface
add_executable(rift-0 ${RIFT_CLI_SOURCES})
target_link_libraries(rift-0 PRIVATE
    $<IF:$<BOOL:${BUILD_SHARED_LIBS}>,rift-stage0,rift-stage0-static>
    Threads::Threads
)
set_target_properties(rift-0 PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
)

# rift.exe - Final stage executable (symbolic)
add_custom_target(rift.exe ALL
    COMMAND ${CMAKE_COMMAND} -E create_symlink 
            $<TARGET_FILE:riftlang.exe> 
            ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/rift.exe
    DEPENDS riftlang.exe
    COMMENT "Creating rift.exe symlink"
)

# ===================================================================
# Object File Management
# ===================================================================
# Custom target to organize object files
add_custom_target(organize_objects ALL
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/obj/core
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/obj/cli
    COMMENT "Organizing object files"
)

# Move object files to obj/ directory after compilation
if(BUILD_STATIC_LIBS)
    add_custom_command(TARGET rift-stage0-static POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
                $<TARGET_OBJECTS:rift-stage0-static>
                ${CMAKE_BINARY_DIR}/obj/core/
        COMMENT "Moving core object files to obj/core/"
    )
endif()

# ===================================================================
# Build Validation
# ===================================================================
add_custom_target(validate ALL
    COMMAND ${CMAKE_COMMAND} -E echo "Validating RIFT Stage-0 build..."
    COMMAND test -f ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/librift-0.so || echo "Warning: librift-0.so not built"
    COMMAND test -f ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/librift-0.a || echo "Warning: librift-0.a not built"
    COMMAND test -f ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/riftlang.exe || echo "Error: riftlang.exe not built"
    DEPENDS riftlang.exe
    COMMENT "Build validation complete"
)

# ===================================================================
# Test Configuration
# ===================================================================
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

# ===================================================================
# Installation Rules
# ===================================================================
install(TARGETS rift-stage0 rift-stage0-static riftlang.exe rift-0
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

install(DIRECTORY ${RIFT_INCLUDE_DIR}/rift-0
    DESTINATION include
)

install(FILES ${CMAKE_BINARY_DIR}/rift_config.h
    DESTINATION include/rift-0
)

install(FILES ${CMAKE_BINARY_DIR}/gov.riftrc.0
    DESTINATION etc/rift
)

# ===================================================================
# Package Configuration
# ===================================================================
configure_file(
    ${RIFT_CONFIG_DIR}/rift-0.pc.in
    ${CMAKE_BINARY_DIR}/rift-0.pc
    @ONLY
)

install(FILES ${CMAKE_BINARY_DIR}/rift-0.pc
    DESTINATION lib/pkgconfig
)

# ===================================================================
# Clean Targets
# ===================================================================
add_custom_target(clean-all
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/bin
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/lib  
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/obj
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/CMakeFiles
    COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_BINARY_DIR}/CMakeCache.txt
    COMMENT "Deep clean of all build artifacts"
)

# ===================================================================
# Build Summary
# ===================================================================
message(STATUS "")
message(STATUS "RIFT Stage-0 Configuration Summary")
message(STATUS "==================================")
message(STATUS "Version:            ${PROJECT_VERSION}")
message(STATUS "Build type:         ${CMAKE_BUILD_TYPE}")
message(STATUS "Install prefix:     ${CMAKE_INSTALL_PREFIX}")
message(STATUS "")
message(STATUS "Features:")
message(STATUS "  Quantum mode:     ${ENABLE_QUANTUM_MODE}")
message(STATUS "  AEGIS compliant:  ${AEGIS_COMPLIANCE}")
message(STATUS "  Panic mode:       ${ENABLE_PANIC_MODE}")
message(STATUS "  Build tests:      ${BUILD_TESTS}")
message(STATUS "  Build examples:   ${BUILD_EXAMPLES}")
message(STATUS "")
message(STATUS "Libraries:")
message(STATUS "  Static (.a):      ${BUILD_STATIC_LIBS}")
message(STATUS "  Shared (.so):     ${BUILD_SHARED_LIBS}")
message(STATUS "  Archive (.so.a):  ${BUILD_SOA_ARCHIVE}")
message(STATUS "")
message(STATUS "Toolchain: rift-0 for RIFT")
message(STATUS "==================================")
message(STATUS "")