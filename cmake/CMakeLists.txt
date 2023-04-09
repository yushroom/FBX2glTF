cmake_minimum_required(VERSION 3.5)
project(FBX2glTF)

set(CMAKE_CXX_STANDARD 17)

set(THIRD_PARTY_DIR
	"${CMAKE_CURRENT_LIST_DIR}/../third_party")

set(MATHFU_INCLUDE_DIRS
	"${THIRD_PARTY_DIR}/mathfu/include/")

set(FIFO_MAP_INCLUDE_DIR
	"${THIRD_PARTY_DIR}/fifo_map/src")

set(CPPCODEC_INCLUDE_DIR
	"${THIRD_PARTY_DIR}/cppcodec")

add_subdirectory(${THIRD_PARTY_DIR}/fmt fmt)

add_executable(FBX2glTF
	${CMAKE_CURRENT_LIST_DIR}/../src/FBX2glTF.cpp
	${CMAKE_CURRENT_LIST_DIR}/../src/FBX2glTF_all.cpp
	${THIRD_PARTY_DIR}/mikktspace/mikktspace.h
	${THIRD_PARTY_DIR}/mikktspace/mikktspace.c
)
target_link_libraries(FBX2glTF PUBLIC fmt::fmt)

set(FBXSDK_DIR ${CMAKE_CURRENT_LIST_DIR}/../sdk/Windows/2020.3.1)
set(FBXSDK_LIB_DIR ${FBXSDK_DIR}/lib/vs2019/x64)
set(FBXSDK_INCLUDE ${FBXSDK_DIR}/include)

target_include_directories(FBX2glTF PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/../src
	${THIRD_PARTY_DIR}/CLI11
	${THIRD_PARTY_DIR}/stb
	${THIRD_PARTY_DIR}/json
	${THIRD_PARTY_DIR}/mikktspace
	${MATHFU_INCLUDE_DIRS}
	${FIFO_MAP_INCLUDE_DIR}
	${CPPCODEC_INCLUDE_DIR}
	${FBXSDK_INCLUDE}
)
target_link_libraries(FBX2glTF PUBLIC
	optimized ${FBXSDK_LIB_DIR}/release/libfbxsdk-md.lib
	optimized ${FBXSDK_LIB_DIR}/release/libxml2-md.lib
	optimized ${FBXSDK_LIB_DIR}/release/zlib-md.lib
	debug ${FBXSDK_LIB_DIR}/debug/libfbxsdk-md.lib
	debug ${FBXSDK_LIB_DIR}/debug/libxml2-md.lib
	debug ${FBXSDK_LIB_DIR}/debug/zlib-md.lib
)
