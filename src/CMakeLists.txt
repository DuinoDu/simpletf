file(GLOB CPP_SOURCES "*.cpp")
add_library(simpletf ${CPP_SOURCES})

target_link_libraries(simpletf PUBLIC absl::status absl::log)

target_include_directories(simpletf PUBLIC
  $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include/>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
