add_executable (fluent_builder "fluent_builder.cpp" )

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET fluent_builder PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(fluent_builder PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(fluent_builder ${Boost_LIBRARIES})