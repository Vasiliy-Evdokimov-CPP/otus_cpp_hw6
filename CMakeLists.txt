cmake_minimum_required(VERSION 3.14)

set(PROJECT_NAME matrix)
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(${PROJECT_NAME} VERSION ${PROJECT_VESRION})

configure_file(version.h.in version.h)

add_executable(${PROJECT_NAME} 
    ${SRC_DIR}/main.cpp
    ${SRC_DIR}/matrix.hpp
)

set_target_properties(
    ${PROJECT_NAME}
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
)

target_include_directories(
    ${PROJECT_NAME}
    PRIVATE "${CMAKE_BINARY_DIR}"
)

if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
        /W4
    )
    set(CPACK_GENERATOR ZIP)
else ()
    target_compile_options(${PROJECT_NAME} PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    set(CPACK_GENERATOR DEB)
endif()

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT vasiliyevdokimov84@gmail.com)

include(CPack)