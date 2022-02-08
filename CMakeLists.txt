cmake_minimum_required (VERSION 3.12)
project(calc LANGUAGES C)

if(NOT TYPE_LIB)
	set(TYPE_LIB STATIC)

set(CMAKE_BUILD_TYPE Release)
set(ROOT_DIR ${CMAKE_CURRENT_LIST_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${ROOT_DIR}/export)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${ROOT_DIR}/export)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${ROOT_DIR}/export)
set(DEP_NAME stack)

include(FetchContent)

FetchContent_Declare(  # fetch dependency from git 
    ${DEP_NAME}
    GIT_REPOSITORY  https://github.com/rostok2112/libstack
    GIT_TAG         origin/main
)

FetchContent_GetProperties(${DEP_NAME})
if (NOT ${DEP_NAME}_POPULATED)
    FetchContent_Populate(${DEP_NAME})
endif ()

execute_process(  #start shell script of build depend
    COMMAND sh build.sh 
    WORKING_DIRECTORY ${${DEP_NAME}_SOURCE_DIR}
)

file(MAKE_DIRECTORY ${ROOT_DIR}/lib) # make lib dir
configure_file(${${DEP_NAME}_SOURCE_DIR}/export/${DEP_NAME}.h ${ROOT_DIR}/include COPYONLY) #copy headers to include/ directory
configure_file(${${DEP_NAME}_SOURCE_DIR}/export/lib${DEP_NAME}.a ${ROOT_DIR}/lib COPYONLY) #copy lib to lib/ directory 

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/opened_archives)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/opened_archives/objs)
configure_file(${ROOT_DIR}/lib/lib${DEP_NAME}.a  ${CMAKE_CURRENT_BINARY_DIR}/opened_archives COPYONLY) 
 
execute_process(   #opening lib (archive) and extracting object files
    COMMAND ar -x lib${DEP_NAME}.a --output ./objs 
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/opened_archives
)

file(GLOB 
	OS "${CMAKE_CURRENT_BINARY_DIR}/opened_archives/objs/*") # Object files of libs
file(GLOB 
	CS "${ROOT_DIR}/src/*.c") #sources

include_directories("${ROOT_DIR}/include") 
link_directories("${ROOT_DIR}/lib")

add_library(${PROJECT_NAME} ${TYPE_LIB} ${CS} ${OS})

SET_SOURCE_FILES_PROPERTIES( # for importing object files to compile
  ${OS}
  PROPERTIES
  EXTERNAL_OBJECT true
  GENERATED true
)