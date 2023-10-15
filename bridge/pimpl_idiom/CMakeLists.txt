add_executable (pimpl_ideom "pimpl_ideom.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET pimpl_ideom PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(pimpl_ideom PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(pimpl_ideom ${Boost_LIBRARIES})