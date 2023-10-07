add_executable (DiContainerSingleton "DiContainerSingleton.cpp")


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET DiContainerSingleton PROPERTY CXX_STANDARD 20)
endif()
set(GTEST_INCLUDE_DIR "C:\\Program Files (x86)\\googletest-distribution\\include")

enable_testing()

target_include_directories(DiContainerSingleton PUBLIC ${Boost_INCLUDE_DIRS} ${GTEST_INCLUDE_DIR})
target_link_libraries(DiContainerSingleton ${Boost_LIBRARIES})