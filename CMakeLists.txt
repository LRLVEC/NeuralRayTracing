cmake_minimum_required(VERSION 3.18)
set(CMAKE_EXPORT_COMPILE_COMMANDS True)
project(neural-raytracing
	VERSION 0.01
	DESCRIPTION "Neural ray tracing"
	LANGUAGES C CXX CUDA
)

if (NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glframework/CMakeLists.txt")
	message(FATAL_ERROR
		"Some neural-raytracing dependencies are missing. "
		"If you forgot the \"--recursive\" flag when cloning this project, "
		"this can be fixed by calling \"git submodule update --init --recursive\"."
	)
endif()

if (MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /D_CRT_SECURE_NO_WARNINGS")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /32 /W4")
endif()
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CUDA_STANDARD 17)
set(CMAKE_CUDA_STANDARD_REQUIRED ON)
set(CMAKE_CUDA_EXTENSIONS OFF)
set(CUDA_LINK_LIBRARIES_KEYWORD PUBLIC)
set(CMAKE_CUDA_RUNTIME_LIBRARY Shared)
if (MSVC)
	list(APPEND CUDA_NVCC_FLAGS "-Xcompiler=-bigobj")
endif()

list(APPEND CUDA_NVCC_FLAGS "--extended-lambda")
list(APPEND CUDA_NVCC_FLAGS "--expt-relaxed-constexpr")

set(TCNN_BUILD_BENCHMARK OFF)
set(TCNN_BUILD_EXAMPLES OFF)
add_subdirectory(dependencies/tiny-cuda-nn)

set(CMAKE_CUDA_ARCHITECTURES ${TCNN_CUDA_ARCHITECTURES})

set(GLFRAMEWORK_BUILD_TESTS OFF CACHE BOOL " " FORCE)
add_subdirectory(dependencies/glframework)

list(APPEND NRT_SOURCES
	# nrt
	src/sdf.cu
	src/renderer.cu
	# stbi
	dependencies/stbi/stbi_wrapper.cpp
)

add_library(nrt STATIC ${NRT_SOURCES})
set_target_properties(nrt PROPERTIES CUDA_RESOLVE_DEVICE_SYMBOLS ON CUDA_SEPARABLE_COMPILATION ON)
get_target_property(TCNN_INCLUDE_DIRECTORIES tiny-cuda-nn INCLUDE_DIRECTORIES)
get_target_property(GLFRAMEWORK_INCLUDE_DIRECTORIES glframework INCLUDE_DIRECTORIES)
target_include_directories(nrt PUBLIC ${TCNN_INCLUDE_DIRECTORIES})
target_include_directories(nrt PUBLIC ${GLFRAMEWORK_INCLUDE_DIRECTORIES})
target_include_directories(nrt PUBLIC
	"include/"
	"dependencies/"
)
target_link_libraries(nrt PUBLIC tiny-cuda-nn)
target_link_libraries(nrt PUBLIC glframework)
target_link_libraries(nrt PUBLIC ${GLFRAMEWORK_LIBRARIES})

add_executable(main src/main.cu)
target_link_libraries(main PRIVATE nrt)