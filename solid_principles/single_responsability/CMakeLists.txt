# CMakeList.txt: CMake-Projekt für "design_pattern_modern_cpp". Schließen Sie die Quelle ein, und definieren Sie
# projektspezifische Logik hier.
#

# Fügen Sie der ausführbaren Datei dieses Projekts eine Quelle hinzu.
add_executable (single_responsability "single_responsability_example.cpp" )

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET single_responsability PROPERTY CXX_STANDARD 20)
endif()

# TODO: Fügen Sie bei Bedarf Tests hinzu, und installieren Sie Ziele.
target_include_directories(single_responsability PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(single_responsability ${Boost_LIBRARIES})