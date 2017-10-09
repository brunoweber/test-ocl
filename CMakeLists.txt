cmake_minimum_required(VERSION 3.5.1)

project(ocl)

find_package(OpenCL REQUIRED)
if(OpenCL_FOUND)
  message(STATUS "OpenCL inc dirs: ${OpenCL_INCLUDE_DIRS}")
  message(STATUS "OpenCL libs: ${OpenCL_LIBRARIES}")

  # Force a lib
  #set(OpenCL_LIBRARIES "path/to/lib")
  
else()
  message(FATAL "OpenCL not found")
endif()

add_executable(test-ocl test.c)
target_link_libraries(test-ocl ${OpenCL_LIBRARIES})
