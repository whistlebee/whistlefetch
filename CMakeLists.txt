cmake_minimum_required(VERSION 3.16)

project(Whistlefetch
  VERSION 1.0
  DESCRIPTION "Whistlefetch!"
  LANGUAGES C)

add_executable(whistlefetch whistlefetch.c os.c)

set_target_properties(
  whistlefetch PROPERTIES
  CMAKE_CSTANDARD 11
  CMAKE_C_STANDARD_REQUIRED True)

target_compile_options(whistlefetch PUBLIC -Wall -Werror -Wmissing-declarations -Wextra)
target_include_directories(whistlefetch PUBLIC "os.h")

include(CheckSymbolExists)

check_symbol_exists(CLOCK_UPTIME_RAW_APPROX "time.h" HAVE_CLOCK_UPTIME_RAW_APPROX)

install(TARGETS whistlefetch)
