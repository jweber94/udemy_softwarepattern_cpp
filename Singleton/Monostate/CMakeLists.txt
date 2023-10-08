add_executable (Monostate "monostate.cpp")


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Monostate PROPERTY CXX_STANDARD 20)
endif()
set(GTEST_INCLUDE_DIR "C:\\Program Files (x86)\\googletest-distribution\\include")

enable_testing()

target_include_directories(Monostate PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(Monostate ${Boost_LIBRARIES})