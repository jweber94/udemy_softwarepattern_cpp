add_executable (factory_homework "factories_homework.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET factory_homework PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(factory_homework PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(factory_homework ${Boost_LIBRARIES})