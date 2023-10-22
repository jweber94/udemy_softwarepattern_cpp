add_executable (neuron_example "neuron_example.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET neuron_example PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(neuron_example PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(neuron_example ${Boost_LIBRARIES})
