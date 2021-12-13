file(REAL_PATH ${CMAKE_SOURCE_DIR}/../.. COMMON_ROOT_DIR)
message("Common root is ${COMMON_ROOT_DIR}")

set(
    CMAKE_TOOLCHAIN_FILE
    ${COMMON_ROOT_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake
)

set( CMAKE_CXX_STANDARD 23 )