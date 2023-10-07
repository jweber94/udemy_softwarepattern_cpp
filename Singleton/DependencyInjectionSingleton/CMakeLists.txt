add_executable (DependencyInjectionSingleton "DiSingleton.cpp")


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET DependencyInjectionSingleton PROPERTY CXX_STANDARD 20)
endif()
set(GTEST_INCLUDE_DIR "C:\\Program Files (x86)\\googletest-distribution\\include")

enable_testing()

target_include_directories(DependencyInjectionSingleton PUBLIC ${Boost_INCLUDE_DIRS} ${GTEST_INCLUDE_DIR})
target_link_libraries(DependencyInjectionSingleton ${Boost_LIBRARIES} gtest gtest_main pthread)