set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_COMPILER "clang++")

project(slurper) # the name of your project

cmake_minimum_required(VERSION 2.8.0)

set(CMAKE_BUILD_TYPE Debug)
#get machine
EXECUTE_PROCESS(
    COMMAND ${CMAKE_C_COMPILER} -dumpmachine
    OUTPUT_VARIABLE MACHINE
    OUTPUT_STRIP_TRAILING_WHITESPACE
)
MESSAGE(STATUS  "Machine: ${MACHINE}, void pointer size: ${CMAKE_SIZEOF_VOID_P}")
STRING(REGEX MATCH "(i?86-*)|(athlon-*)|(pentium-*)" _machine_x86 "${MACHINE}")
IF (_machine_x86)
    MESSAGE(STATUS "Found target X86")
    SET(ARCH_X86 1)
ENDIF (_machine_x86)
IF (APPLE AND CMAKE_SIZEOF_VOID_P EQUAL 8 AND ARCH_X86 EQUAL 1)
  MESSAGE(STATUS "Found Snow Leopard Target: Apple, 64 bit, X86")
  UNSET(ARCH_X86)
  SET(ARCH_X86_64 1)
  SET(APPLE_10_6_X 1 CACHE TYPE BOOL)
ENDIF (APPLE AND CMAKE_SIZEOF_VOID_P EQUAL 8 AND ARCH_X86 EQUAL 1)

#######################################################################
if (APPLE)
 
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
  set(CMAKE_CSS_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall")

endif (APPLE)
######################################################################


# the variable "slurper_SRCS" contains all .cpp files of this project
set(slurper_SRCS slurper.c)

# Don't forget to include output directory, otherwise
# the UI file won't be wrapped!

include_directories(${CMAKE_CURRENT_BINARY_DIR})

#Now add these generated files to the ADD_EXECUTABLE step
# If this is NOT done, then the ui_*.h files will not be generated
add_executable(slurper ${slurper_SRCS})
# link the "slurper" target against the Qt libraries. which libraries exactly, is defined by the "include
target_link_libraries(slurper)

