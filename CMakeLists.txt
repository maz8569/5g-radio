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
include_directories(${CMAKE_SOURCE_DIR}/include)
# Add source to this project's executable.
add_executable (5gradio   "src/main.cpp" "include/common/Types.h" "include/rlc/RlcSdu.h" "include/rlc/RlcPdu.h" "include/rlc/RlcSduFactory.h" "src/rlc/RlcSduFactory.cpp" "src/rlc/RlcPdu.cpp" "include/rlc/IRlcSegmenter.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET 5gradio PROPERTY CXX_STANDARD 20)
endif()

enable_testing()
