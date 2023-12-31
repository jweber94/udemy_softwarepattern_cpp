﻿# CMakeList.txt: CMake-Projektdatei der obersten Ebene. Führen Sie hier die globale Konfiguration aus,
# und schließen Sie Unterprojekte ein.
#
cmake_minimum_required (VERSION 3.8)

# Aktivieren Sie Hot Reload für MSVC-Compiler, sofern unterstützt.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
  #(GTEST_ROOT "C:\\Program Files (x86)\\googletest-distribution")
  #set(GTEST_INCLUDE_DIR "C:\\Program Files (x86)\\googletest-distribution\\include")
endif()

project ("design_pattern_modern_cpp")

find_package(Boost REQUIRED)
find_package(Threads REQUIRED)
find_package(GTest REQUIRED)

# Basics
add_subdirectory ("solid_principles")		# chapter 1
## creational pattern
add_subdirectory ("builder")				# chapter 2
add_subdirectory ("factory")				# chapter 3
add_subdirectory ("prototype")				# chapter 4
add_subdirectory("Singleton")				# chapter 5
## structural pattern
add_subdirectory("adapter")					# chapter 6
add_subdirectory("bridge")					# chapter 7
add_subdirectory("composite")				# chapter 8
add_subdirectory("decorator")				# chapter 9
#("facade")				# chapter 10
add_subdirectory("flyweight")				# chapter 11
add_subdirectory("proxy")					# chapter 12
## behavioural pattern
add_subdirectory("chain_of_responsability") # chapter 13
add_subdirectory("command")					# chapter 14
add_subdirectory("interpreter")				# chapter 15
add_subdirectory("iterator")				# chapter 16
add_subdirectory("mediator")				# chapter 17
add_subdirectory("memento")					# chapter 18
add_subdirectory("observer")				# chapter 19 - Does not compile under windows due to a memory.h issue
add_subdirectory("state")					# chapter 20
add_subdirectory("strategy")				# chapter 21
add_subdirectory("template_pattern")		# chapter 22
add_subdirectory("visitor")					# chapter 23