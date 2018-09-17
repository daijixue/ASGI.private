#pragma once
#include <unordered_map>
#include <string>

namespace ASGI {  namespace VKGLSL {
		enum GLSLType {
			GLSL_TYPE_VOID = 0,
			//
			GLSL_TYPE_SCALAR_BEGIN,
			GLSL_TYPE_BOOL,
			GLSL_TYPE_INT,
			GLSL_TYPE_UINT,
			GLSL_TYPE_FLOAT,
			GLSL_TYPE_DOUBLE,
			GLSL_TYPE_SCALAR_END,
			//
			GLSL_TYPE_VEC_BEGIN,
			GLSL_TYPE_BVEC2,
			GLSL_TYPE_BVEC3,
			GLSL_TYPE_BVEC4,
			GLSL_TYPE_IVEC2,
			GLSL_TYPE_IVEC3,
			GLSL_TYPE_IVEC4,
			GLSL_TYPE_UVEC2,
			GLSL_TYPE_UVEC3,
			GLSL_TYPE_UVEC4,
			GLSL_TYPE_VEC2,
			GLSL_TYPE_VEC3,
			GLSL_TYPE_VEC4,
			GLSL_TYPE_DVEC2,
			GLSL_TYPE_DEVC3,
			GLSL_TYPE_DEVC4,
			GLSL_TYPE_VEC_END,
			//
			GLSL_TYPE_MAT_BEGIN,
			GLSL_TYPE_MAT2,
			GLSL_TYPE_MAT3,
			GLSL_TYPE_MAT4,
			GLSL_TYPE_MAT2X3,
			GLSL_TYPE_MAT2X4,
			GLSL_TYPE_MAT3X2,
			GLSL_TYPE_MAT4X2,
			GLSL_TYPE_MAT3X4,
			GLSL_TYPE_MAT4X3,
			GLSL_TYPE_MAT_END,
			//
			GLSL_TYPE_DMAT_BEGIN,
			GLSL_TYPE_DMAT2,
			GLSL_TYPE_DMAT3,
			GLSL_TYPE_DMAT4,
			GLSL_TYPE_DMAT2X3,
			GLSL_TYPE_DMAT2X4,
			GLSL_TYPE_DMAT3X2,
			GLSL_TYPE_DMAT4X2,
			GLSL_TYPE_DMAT3X4,
			GLSL_TYPE_DMAT4X3,
			GLSL_TYPE_DMAT_END,
			//
			GLSL_TYPE_OPAQUE_BEGIN,
			GLSL_TYPE_SAMPLER1D,
			GLSL_TYPE_ISAMPLER1D,
			GLSL_TYPE_USAMPLER1D,
			GLSL_TYPE_IMAGE1D,
			GLSL_TYPE_IIMAGE1D,
			GLSL_TYPE_UIMAGE1D,
			GLSL_TYPE_SAMPLER1D_ARRAY,
			GLSL_TYPE_ISAMPLER1D_ARRAY,
			GLSL_TYPE_USAMPLER1D_ARRAY,
			GLSL_TYPE_IMAGE1D_ARRAY,
			GLSL_TYPE_IIMAGE1D_ARRAY,
			GLSL_TYPE_UIMAGE1D_ARRAY,
			GLSL_TYPE_SAMPLER2D,
			GLSL_TYPE_ISAMPLER2D,
			GLSL_TYPE_USAMPLER2D,
			GLSL_TYPE_IMAGE2D,
			GLSL_TYPE_IIMAGE2D,
			GLSL_TYPE_UIMAGE2D,
			GLSL_TYPE_SAMPLER2D_RECT,
			GLSL_TYPE_ISAMPLER2D_RECT,
			GLSL_TYPE_USAMPLER2D_RECT,
			GLSL_TYPE_IMAGE2D_RECT,
			GLSL_TYPE_IIMAGE2D_RECT,
			GLSL_TYPE_UIMAGE2D_RECT,
			GLSL_TYPE_SAMPLER2D_ARRAY,
			GLSL_TYPE_ISAMPLER2D_ARRAY,
			GLSL_TYPE_USAMPLER2D_ARRAY,
			GLSL_TYPE_IMAGE2D_ARRAY,
			GLSL_TYPE_IIMAGE2D_ARRAY,
			GLSL_TYPE_UIMAGE2D_ARRAY,
			GLSL_TYPE_SAMPLER3D,
			GLSL_TYPE_ISAMPLER3D,
			GLSL_TYPE_USAMPLER3D,
			GLSL_TYPE_IMAGE3D,
			GLSL_TYPE_IIMAGE3D,
			GLSL_TYPE_UIMAGE3D,
			GLSL_TYPE_SAMPLER_CUBE,
			GLSL_TYPE_ISAMPLER_CUBE,
			GLSL_TYPE_USAMPLER_CUBE,
			GLSL_TYPE_IMAGE_CUBE,
			GLSL_TYPE_IIMAGE_CUBE,
			GLSL_TYPE_UIMAGE_CUBE,
			GLSL_TYPE_SAMPLER_CUBE_ARRAY,
			GLSL_TYPE_ISAMPLER_CUBE_ARRAY,
			GLSL_TYPE_USAMPLER_CUBE_ARRAY,
			GLSL_TYPE_IMAGE_CUBE_ARRAY,
			GLSL_TYPE_IIMAGE_CUBE_ARRAY,
			GLSL_TYPE_UIMAGE_CUBE_ARRAY,
			GLSL_TYPE_SAMPLER_BUFFER,
			GLSL_TYPE_ISAMPLER_BUFFER,
			GLSL_TYPE_USAMPLER_BUFFER,
			GLSL_TYPE_IMAGE_BUFFER,
			GLSL_TYPE_IIMAGE_BUFFER,
			GLSL_TYPE_UIMAGE_BUFFER,
			GLSL_TYPE_SAMPLER_2DMS,
			GLSL_TYPE_ISAMPLER_2DMS,
			GLSL_TYPE_USAMPLER_2DMS,
			GLSL_TYPE_IMAGE_2DMS,
			GLSL_TYPE_IIMAGE_2DMS,
			GLSL_TYPE_UIMAGE_2DMS,
			GLSL_TYPE_SAMPLER_2DMS_ARRAY,
			GLSL_TYPE_ISAMPLER_2DMS_ARRAY,
			GLSL_TYPE_USAMPLER_2DMS_ARRAY,
			GLSL_TYPE_IMAGE_2DMS_ARRAY,
			GLSL_TYPE_IIMAGE_2DMS_ARRAY,
			GLSL_TYPE_UIMAGE_2DMS_ARRAY,
			GLSL_TYPE_SAMPLER1D_SHADOW,
			GLSL_TYPE_SAMPLER2D_SHADOW,
			GLSL_TYPE_SAMPLER_CUBE_SHADOW,
			GLSL_TYPE_SAMPLER2D_RECT_SHADOW,
			GLSL_TYPE_SAMPLER1D_ARRAY_SHADOW,
			GLSL_TYPE_SAMPLER2D_ARRAY_SHADOW,
			GLSL_TYPE_SAMPLER_CUBE_ARRAY_SHADOW,
			GLSL_TYPE_ATOMIC_UINT,
			GLSL_TYPE_OPAQUE_END
		};
		//
		extern std::unordered_map<GLSLType, std::string>  GLSLTypeStrMap;
		extern std::unordered_map<std::string, GLSLType>  GLSLStrTypeMap;

		enum GLSLStorageQualifier {
			GLSL_SQ_CONST = 0,
			GLSL_SQ_IN,
			GLSL_SQ_OUT,
			GLSL_SQ_ATTRIBUTE,
			GLSL_SQ_UNIFORM,
			GLSL_SQ_VARYING,
			GLSL_SQ_BUFFER,
			GLSL_SQ_SHARED
		};
		extern std::unordered_map<std::string, GLSLStorageQualifier> GLSLStrSQFMap;

		enum GLSLAuxiliaryStorageQualifier {
			GLSL_ASQ_CENTROID = 0,
			GLSL_ASQ_SAMPLE,
			GLSL_ASQ_PATCH
		};

		struct GLSLInputAttribute {
			std::string name;
			uint32_t location;
			GLSLType type;
		};

		struct GLSLStruct {
			std::string name;
			std::vector<std::pair<std::string, std::string> > defines;
		};

		struct GLSLUniformBuffer {
			std::string name;
			std::vector<std::pair<std::string, GLSLType> >defines;
			uint32_t setNumber;
			uint32_t binding;
			std::vector<std::string> instaninstance;
		};

		struct GLSLSampler {
			std::string name;
			GLSLType type;
			uint32_t setNumber;
			uint32_t binding;
		};

		struct GLSLConstant {
			GLSLType type;
			std::string strValue;
			std::string name;
			int constant_id;
		};

		struct GLSLPushConstant {
			std::string name;
			std::vector<std::pair<std::string, GLSLType> >defines;
			uint32_t setNumber;
			uint32_t binding;
			std::vector<std::string> instaninstance;
		};

		struct GLSLLayout {
			std::unordered_map<std::string, GLSLStruct> structs;
			std::unordered_map<std::string, GLSLConstant> constants;
			std::vector<GLSLInputAttribute> inputAttributes;
			std::vector<GLSLUniformBuffer> uniformBuffers;
			std::vector<GLSLSampler> samplers;
			std::vector<GLSLPushConstant> pushConstants;
		};

		extern bool GLSLLayoutAnalyze(const char* pcode, GLSLLayout& layout);
}}