cmake_minimum_required(VERSION 3.15)
project(libnbt++
    VERSION 2.5.1)

# supported configure options
option(NBT_BUILD_SHARED "Build shared libraries" OFF)
option(NBT_USE_ZLIB "Build additional zlib stream functionality" ON)
option(NBT_BUILD_TESTS "Build the unit tests. Requires CxxTest." ON)

set(CMAKE_CXX_STANDARD 11)

# hide this from includers.
set(BUILD_SHARED_LIBS ${NBT_BUILD_SHARED})

include(GenerateExportHeader)

set(NBT_SOURCES
    src/endian_str.cpp
    src/tag.cpp
    src/tag_array.cpp
    src/tag_compound.cpp
    src/tag_list.cpp
    src/tag_string.cpp
    src/value.cpp
    src/value_initializer.cpp

    src/io/stream_reader.cpp
    src/io/stream_writer.cpp

    src/text/json_formatter.cpp)

set(NBT_SOURCES_Z
    src/io/izlibstream.cpp
    src/io/ozlibstream.cpp)

if(NBT_USE_ZLIB)
    find_package(ZLIB REQUIRED)
    list(APPEND NBT_SOURCES ${NBT_SOURCES_Z})
endif()

add_library(NBT++ ${NBT_SOURCES})
target_include_directories(NBT++ PUBLIC $<BUILD_INTERFACE:include ${CMAKE_CURRENT_BINARY_DIR}>)

target_compile_definitions(NBT++ PRIVATE "-DNBT_BUILD_LIB")

if(NBT_USE_ZLIB)
    target_link_libraries(NBT++ ${ZLIB_LIBRARY})
    target_include_directories(NBT++ PUBLIC $<BUILD_INTERFACE:${ZLIB_INCLUDE_DIRS}>)
    target_compile_definitions(NBT++ PUBLIC "-DNBT_HAVE_ZLIB")
endif()
# target_compile_options(NBT++ PUBLIC -std=c++11)
generate_export_header(NBT++ BASE_NAME nbt)

if(${BUILD_SHARED_LIBS})
    set_target_properties(NBT++ PROPERTIES
        CXX_VISIBILITY_PRESET hidden
        VISIBILITY_INLINES_HIDDEN 1)
endif()

if(NBT_BUILD_TESTS)
    enable_testing()
    add_subdirectory(test)
endif()



# create and install a cmake package

target_include_directories(NBT++ PUBLIC INTERFACE $<INSTALL_INTERFACE:include>)

## alias
add_library(libNBT++::NBT++ ALIAS NBT++)

## install headers
file(GLOB libNBT++_install_headers ${CMAKE_SOURCE_DIR}/include/*.h)
install(FILES ${libNBT++_install_headers} ${CMAKE_BINARY_DIR}/nbt_export.h DESTINATION include/libNBT++)

### io headers
file(GLOB libNBT++_install_headers_io ${CMAKE_SOURCE_DIR}/include/io/*.h)
install(FILES ${libNBT++_install_headers_io} DESTINATION include/libNBT++/io)
### text headers
file(GLOB libNBT++_install_headers_text ${CMAKE_SOURCE_DIR}/include/text/*.h)
install(FILES ${libNBT++_install_headers_text} DESTINATION include/libNBT++/text)


## install core library
install( 
  TARGETS NBT++
  EXPORT libNBT++Targets
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES DESTINATION include
  )

## install export
install(
  EXPORT libNBT++Targets
  DESTINATION lib/cmake/libNBT++
  NAMESPACE libNBT++::
  FILE libNBT++Targets.cmake
  )

include(CMakePackageConfigHelpers)
configure_package_config_file( 
  ${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in

  ${CMAKE_CURRENT_BINARY_DIR}/libNBT++Config.cmake
  INSTALL_DESTINATION lib/cmake/libNBT++
  PATH_VARS
  NO_CHECK_REQUIRED_COMPONENTS_MACRO
  )

write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/libNBT++ConfigVersion.cmake
  VERSION 2.5.1
  COMPATIBILITY AnyNewerVersion
  )

### Install Config and ConfigVersion files
install(
  FILES "${CMAKE_CURRENT_BINARY_DIR}/libNBT++Config.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/libNBT++ConfigVersion.cmake"
  DESTINATION lib/cmake/libNBT++
  )