cmake_minimum_required(VERSION 3.26)
project(webptopng)

set(CMAKE_CXX_STANDARD 23)

add_executable(${CMAKE_PROJECT_NAME}
		main.cc
		pngFormat.hh
		pngFormat.cc
		webpFormat.cc
		stringTools.cc
		stringTools.hh)

target_link_libraries(${CMAKE_PROJECT_NAME} -static gcc stdc++ winpthread png z webp)
