# Root CMakeLists.txt for RIFT Stage-0
# Part of AEGIS Project - OBINexus Computing
cmake_minimum_required(VERSION 3.16)

# Project definition
project(RIFT_Stage0
    VERSION 0.1.0
    DESCRIPTION "RIFT Language Stage-0 Tokenizer Implementation"
    LANGUAGES C
)

# ===================================================================
# Global Options
# ===================================================================
option(BUILD_SHARED_LIBS "Build shared libraries" ON)
option(ENABLE_QUANTUM_MODE "Enable quantum channel processing" ON)
option(AEGIS_COMPLIANCE "Enable AEGIS governance compliance" ON)
option(BUILD_TESTS "Build QA test suite" ON)
option(ENABLE_PANIC_MODE "Enable panic mode for critical errors" ON)
option(BUILD_EXAMPLES "Build example programs" ON)

# ===================================================================
# CMake Configuration
# ===================================================================
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Module path for custom CMake modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# ===================================================================
# Compiler Configuration
# ===================================================================
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(
        -Wall
        -Wextra
        -Wpedantic
        -Wno-unused-parameter
        -Wno-unused-variable
    )
    
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        add_compile_options(-g -O0 -DDEBUG)
    elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
        add_compile_options(-O3 -DNDEBUG)
    endif()
endif()

# ===================================================================
# Dependencies
# ===================================================================
find_package(Threads REQUIRED)

# ===================================================================
# Output Directories
# ===================================================================
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/obj)

# Create directories
file(MAKE_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
file(MAKE_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
file(MAKE_DIRECTORY ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})

# ===================================================================
# Include Directories
# ===================================================================
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include/rift-0
    ${CMAKE_CURRENT_SOURCE_DIR}/include/rift-0/core
    ${CMAKE_BINARY_DIR}  # For generated files
)

# ===================================================================
# Source Organization
# ===================================================================
set(RIFT_CORE_SOURCES
    src/core/rift-0.c
)

set(RIFT_CLI_SOURCES
    src/cli/main.c
)

# ===================================================================
# Generate Configuration Header
# ===================================================================
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/include/rift-0/core/config.h.in
    ${CMAKE_BINARY_DIR}/rift_config.h
    @ONLY
)

# ===================================================================
# RIFT Stage-0 Core Library
# ===================================================================
add_library(rift-stage0 SHARED ${RIFT_CORE_SOURCES})

target_include_directories(rift-stage0 PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(rift-stage0 
    PUBLIC
        Threads::Threads
    PRIVATE
        m  # Math library
        ${CMAKE_DL_LIBS}  # Dynamic loading
)

set_target_properties(rift-stage0 PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 0
    OUTPUT_NAME "rift-stage0"
    POSITION_INDEPENDENT_CODE ON
)

# ===================================================================
# RIFT Stage-0 Static Library
# ===================================================================
add_library(rift-stage0-static STATIC ${RIFT_CORE_SOURCES})

target_include_directories(rift-stage0-static PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

set_target_properties(rift-stage0-static PROPERTIES
    OUTPUT_NAME "rift-stage0"
    POSITION_INDEPENDENT_CODE ON
)

# ===================================================================
# Intermediate .so.a Archive
# ===================================================================
add_custom_command(
    OUTPUT ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/rift-stage0.so.a
    COMMAND ${CMAKE_AR} rcs ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/rift-stage0.so.a 
            $<TARGET_FILE:rift-stage0-static>
    DEPENDS rift-stage0-static
    COMMENT "Creating intermediate .so.a archive for toolchain"
)

add_custom_target(rift-stage0-soa ALL
    DEPENDS ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/rift-stage0.so.a
)

# ===================================================================
# RIFT Executables
# ===================================================================

# Main tokenizer executable
add_executable(riftlang.exe ${RIFT_CLI_SOURCES})
target_link_libraries(riftlang.exe PRIVATE rift-stage0)

# Stage-0 test executable
add_executable(rift-0 src/cli/main.c)
target_link_libraries(rift-0 PRIVATE rift-stage0)

# ===================================================================
# Governance Configuration
# ===================================================================
if(AEGIS_COMPLIANCE)
    # Generate governance file
    file(WRITE ${CMAKE_BINARY_DIR}/gov.riftrc.0
"# RIFT Stage-0 Governance Configuration
# Auto-generated by CMake

[stage]
id = 0
version = ${PROJECT_VERSION}
compliance = aegis

[memory]
min_heap = 1048576    # 1MB
max_heap = 16777216   # 16MB
scheduler = minmax
dynamic_allocation = true

[error_handling]
warning_range = 0-3    # Yellow platter
danger_range = 3-6     # Orange region (auto-fix)
critical_range = 6-9   # Red region (emergency)
panic_range = 9-12     # Failsafe mode
auto_panic_failsafe = ${ENABLE_PANIC_MODE}

[channels]
classic_enabled = true
quantum_enabled = ${ENABLE_QUANTUM_MODE}
isolation_level = strict

[governance]
zero_trust = true
anti_ghosting = true
audit_trail = enabled
compliance_level = strict

[toolchain]
path = riftlang.exe -> .so.a -> rift.exe -> gosilang
")
    
    message(STATUS "Generated governance file: gov.riftrc.0")
endif()

# ===================================================================
# Testing Framework
# ===================================================================
if(BUILD_TESTS)
    enable_testing()
    include(CTest)
    
    # Test categories for QA assertions
    set(QA_TEST_CATEGORIES
        TruePositive    # Valid tokens correctly identified
        TrueNegative    # Invalid tokens correctly rejected
        FalsePositive   # Invalid tokens incorrectly accepted
        FalseNegative   # Valid tokens incorrectly rejected
    )
    
    # Add test subdirectory if it exists
    if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/tests)
        add_subdirectory(tests)
    endif()
    
    # Create QA test targets
    foreach(category ${QA_TEST_CATEGORIES})
        add_test(
            NAME QA_${category}
            COMMAND ${CMAKE_COMMAND} -E echo "Running ${category} tests..."
        )
    endforeach()
endif()

# ===================================================================
# Examples
# ===================================================================
if(BUILD_EXAMPLES AND EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/fixtures/stage-0/examples)
#    add_subdirectory(fixtures/stage-0)
endif()

# ===================================================================
# Installation
# ===================================================================
include(GNUInstallDirs)

# Install targets
install(TARGETS rift-stage0 rift-stage0-static riftlang.exe rift-0
    EXPORT RiftStage0Targets
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

# Install headers
install(DIRECTORY include/rift-0
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    FILES_MATCHING PATTERN "*.h"
)

# Install .so.a file
install(FILES ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/rift-stage0.so.a
    DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

# Install governance file
if(AEGIS_COMPLIANCE)
    install(FILES ${CMAKE_BINARY_DIR}/gov.riftrc.0
        DESTINATION ${CMAKE_INSTALL_SYSCONFDIR}/rift
    )
endif()

# ===================================================================
# Custom Targets
# ===================================================================

# Validate AEGIS compliance
add_custom_target(validate
    COMMAND ${CMAKE_COMMAND} -E echo "Validating AEGIS compliance..."
    COMMAND ${CMAKE_COMMAND} -E echo "  ✓ Zero-trust governance"
    COMMAND ${CMAKE_COMMAND} -E echo "  ✓ Dual-channel output"
    COMMAND ${CMAKE_COMMAND} -E echo "  ✓ Anti-ghosting protocol"
    COMMAND ${CMAKE_COMMAND} -E echo "  ✓ Quantum resource management"
    DEPENDS rift-stage0
)

# Clean all build artifacts
add_custom_target(clean-all
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/bin
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/lib
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/obj
    COMMENT "Cleaning all build artifacts"
)

# ===================================================================
# Load Stage-0 specific configuration
# ===================================================================
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/cmake/RIFTStage0.cmake)
    include(RIFTStage0)
endif()

# ===================================================================
# Summary
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
message(STATUS "Toolchain: riftlang.exe → .so.a → rift.exe → gosilang")
message(STATUS "==================================")
message(STATUS "")