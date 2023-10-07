add_executable (singleton "Singleton.cpp")


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET singleton PROPERTY CXX_STANDARD 20)
endif()
set(GTEST_INCLUDE_DIR "C:\\Program Files (x86)\\googletest-distribution\\include")

target_include_directories(singleton PUBLIC ${Boost_INCLUDE_DIRS} ${GTEST_INCLUDE_DIR})
target_link_libraries(singleton ${Boost_LIBRARIES} gtest gtest_main)