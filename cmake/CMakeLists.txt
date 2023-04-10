cmake_minimum_required(VERSION 3.16)
project(FBX2glTF)

set(CMAKE_CXX_STANDARD 17)

set(THIRD_PARTY_DIR
	"${CMAKE_CURRENT_LIST_DIR}/../third_party")

set(SRC_DIR
	"${CMAKE_CURRENT_LIST_DIR}/../src")

set(MATHFU_INCLUDE_DIRS
	"${THIRD_PARTY_DIR}/mathfu/include/")

set(FIFO_MAP_INCLUDE_DIR
	"${THIRD_PARTY_DIR}/fifo_map/src")

set(CPPCODEC_INCLUDE_DIR
	"${THIRD_PARTY_DIR}/cppcodec")

add_subdirectory(${THIRD_PARTY_DIR}/fmt fmt)

set(LIB_SOURCE_FILES
	${SRC_DIR}/FBX2glTF.h
	${SRC_DIR}/fbx/materials/3dsMaxPhysicalMaterial.cpp
	${SRC_DIR}/fbx/materials/FbxMaterials.cpp
	${SRC_DIR}/fbx/materials/FbxMaterials.hpp
	${SRC_DIR}/fbx/materials/RoughnessMetallicMaterials.hpp
	${SRC_DIR}/fbx/materials/StingrayPBSMaterial.cpp
	${SRC_DIR}/fbx/materials/TraditionalMaterials.cpp
	${SRC_DIR}/fbx/materials/TraditionalMaterials.hpp
	${SRC_DIR}/fbx/Fbx2Raw.cpp
	${SRC_DIR}/fbx/Fbx2Raw.hpp
	${SRC_DIR}/fbx/FbxBlendShapesAccess.cpp
	${SRC_DIR}/fbx/FbxBlendShapesAccess.hpp
	${SRC_DIR}/fbx/FbxLayerElementAccess.hpp
	${SRC_DIR}/fbx/FbxSkinningAccess.cpp
	${SRC_DIR}/fbx/FbxSkinningAccess.hpp
	${SRC_DIR}/gltf/Raw2Gltf.cpp
	${SRC_DIR}/gltf/Raw2Gltf.hpp
	${SRC_DIR}/gltf/GltfModel.cpp
	${SRC_DIR}/gltf/GltfModel.hpp
	${SRC_DIR}/gltf/TextureBuilder.cpp
	${SRC_DIR}/gltf/TextureBuilder.hpp
	${SRC_DIR}/gltf/properties/AccessorData.cpp
	${SRC_DIR}/gltf/properties/AccessorData.hpp
	${SRC_DIR}/gltf/properties/AnimationData.cpp
	${SRC_DIR}/gltf/properties/AnimationData.hpp
	${SRC_DIR}/gltf/properties/BufferData.cpp
	${SRC_DIR}/gltf/properties/BufferData.hpp
	${SRC_DIR}/gltf/properties/BufferViewData.cpp
	${SRC_DIR}/gltf/properties/BufferViewData.hpp
	${SRC_DIR}/gltf/properties/CameraData.cpp
	${SRC_DIR}/gltf/properties/CameraData.hpp
	${SRC_DIR}/gltf/properties/ImageData.cpp
	${SRC_DIR}/gltf/properties/ImageData.hpp
	${SRC_DIR}/gltf/properties/LightData.cpp
	${SRC_DIR}/gltf/properties/LightData.hpp
	${SRC_DIR}/gltf/properties/MaterialData.cpp
	${SRC_DIR}/gltf/properties/MaterialData.hpp
	${SRC_DIR}/gltf/properties/MeshData.cpp
	${SRC_DIR}/gltf/properties/MeshData.hpp
	${SRC_DIR}/gltf/properties/NodeData.cpp
	${SRC_DIR}/gltf/properties/NodeData.hpp
	${SRC_DIR}/gltf/properties/PrimitiveData.cpp
	${SRC_DIR}/gltf/properties/PrimitiveData.hpp
	${SRC_DIR}/gltf/properties/SamplerData.hpp
	${SRC_DIR}/gltf/properties/SceneData.cpp
	${SRC_DIR}/gltf/properties/SceneData.hpp
	${SRC_DIR}/gltf/properties/SkinData.cpp
	${SRC_DIR}/gltf/properties/SkinData.hpp
	${SRC_DIR}/gltf/properties/TextureData.cpp
	${SRC_DIR}/gltf/properties/TextureData.hpp
	${SRC_DIR}/mathfu.hpp
	${SRC_DIR}/raw/RawModel.cpp
	${SRC_DIR}/raw/RawModel.hpp
	${SRC_DIR}/utils/File_Utils.cpp
	${SRC_DIR}/utils/File_Utils.hpp
	${SRC_DIR}/utils/Image_Utils.cpp
	${SRC_DIR}/utils/Image_Utils.hpp
	${SRC_DIR}/utils/String_Utils.hpp
	${THIRD_PARTY_DIR}/CLI11/CLI11.hpp
)

add_executable(FBX2glTF
	${CMAKE_CURRENT_LIST_DIR}/../src/FBX2glTF.cpp
	${LIB_SOURCE_FILES}
	${THIRD_PARTY_DIR}/mikktspace/mikktspace.h
	${THIRD_PARTY_DIR}/mikktspace/mikktspace.c
)
set_target_properties(FBX2glTF PROPERTIES UNITY_BUILD ON)
target_link_libraries(FBX2glTF PUBLIC fmt::fmt)

set(FBXSDK_DIR ${CMAKE_CURRENT_LIST_DIR}/../sdk/Windows/2020.3.2)
set(FBXSDK_LIB_DIR ${FBXSDK_DIR}/lib/vs2019/x64)
set(FBXSDK_INCLUDE ${FBXSDK_DIR}/include)
set(FBXSDK_DLL ${FBXSDK_LIB_DIR}/release/libfbxsdk.dll)

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
	optimized ${FBXSDK_LIB_DIR}/release/libfbxsdk.lib
	debug ${FBXSDK_LIB_DIR}/release/libfbxsdk.lib
)
target_compile_definitions(FBX2glTF PUBLIC FBXSDK_SHARED)

# copy the fbxsdk dynamic library to the output directory
ADD_CUSTOM_COMMAND(
    TARGET FBX2glTF POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${FBXSDK_DLL} $<TARGET_FILE_DIR:FBX2glTF>
)
