# CMakeList.txt : CMake project for 5gradio, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("5gradio")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_library(RadioCore
			src/rlc/RlcEntity.cpp
			src/rlc/RlcPdu.cpp
			src/rlc/RlcSduFactory.cpp
			src/rlc/RlcSegmenter.cpp

			src/mac/BaseMacScheduler.cpp
			src/mac/FifoScheduler.cpp
			src/mac/MacEntity.cpp
			src/mac/PriorityScheduler.cpp

			src/channel/Channel.cpp)

target_include_directories(RadioCore
    PUBLIC ${CMAKE_SOURCE_DIR}/include)

# Add source to this project's executable.
add_executable (5gradio   "src/main.cpp")
target_link_libraries(5gradio PRIVATE RadioCore)

enable_testing()

file(GLOB TEST_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/test/*.cpp"
)

add_executable(UnitTests ${TEST_SOURCES})
target_link_libraries(UnitTests PRIVATE RadioCore gtest_main)

include(GoogleTest)
gtest_discover_tests(UnitTests)

add_custom_target(check
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
    DEPENDS UnitTests
)
