cmake_minimum_required(VERSION 3.5)

project(CudaDemo LANGUAGES CXX CUDA)

find_package(CUDA REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/include 
                    ${CUDA_INCLUDE_DIRS})
                    
file(GLOB_RECURSE HEADER_FILES "${PROJECT_SOURCE_DIR}/include/*.h")
aux_source_directory(${PROJECT_SOURCE_DIR}/src DIR_SRCS)

add_executable(${PROJECT_NAME} ${DIR_SRCS} ${HEADER_FILES})

#set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)#LINKER_LANGUAGE
#target_link_libraries(${PROJECT_NAME} ${CUDA_LIBRARIES})