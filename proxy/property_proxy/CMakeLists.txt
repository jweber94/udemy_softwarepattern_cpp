add_executable (property_proxy "property_proxy.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET property_proxy PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(property_proxy PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(property_proxy ${Boost_LIBRARIES})