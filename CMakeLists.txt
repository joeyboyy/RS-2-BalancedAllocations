cmake_minimum_required(VERSION 3.22)
project(GaltonBoardSim LANGUAGES CXX)

### setting up compilation variables ###
set(COMMON_FLAGS)
set(RELEASE_FLAGS)
set(SANITIZER_FLAGS)

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    list(APPEND COMMON_FLAGS -Wall -Wextra -Wpedantic)
    List(APPEND RELEASE_FLAGS -O3 -Ofast -march=native)
    list(APPEND SANITIZER_FLAGS -fsanitize=address,undefined,leak -static-libasan -g)
else()
    message(WARNING "Unexpected compiler (ID=${CMAKE_CXX_COMPILER_ID}) used. No flags set.")
endif()

add_compile_options(
    ${COMMON_FLAGS}
	"$<$<CONFIG:Release>:${RELEASE_FLAGS}>"
    "$<$<CONFIG:Debug>:${SANITIZER_FLAGS}>"
)
# add all compile options to link options as well just to make sure
add_link_options(
    ${COMMON_FLAGS}
    "$<$<CONFIG:Release>:${RELEASE_FLAGS}>"
    "$<$<CONFIG:Debug>:${SANITIZER_FLAGS}>"
)

# note that the pre-defined cache variables are always used for libraries and executables
#####################################

add_executable(BalancedAllocOnline balanced_alloc_online.cpp)
add_executable(BalancedAllocBatched balanced_alloc_batched.cpp)
add_executable(BalancedAllocOnlinePartialInfo balanced_alloc_online.cpp)
target_compile_definitions(BalancedAllocOnlinePartialInfo PUBLIC "-DPARTIAL_INFO")
add_executable(BalancedAllocBatchedPartialInfo balanced_alloc_batched.cpp)
target_compile_definitions(BalancedAllocBatchedPartialInfo PUBLIC "-DPARTIAL_INFO")
