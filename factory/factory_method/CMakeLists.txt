add_executable (factory_method "factory_method.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET factory_method PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(factory_method PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(factory_method ${Boost_LIBRARIES})