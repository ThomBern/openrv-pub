#
# Copyright (C) 2023  Autodesk, Inc. All Rights Reserved.
#
# SPDX-License-Identifier: Apache-2.0
#

INCLUDE(cxx_defaults)

SET(_target
    "MesaGL"
)


# Mesa Gallium C Files

FILE(GLOB _mesaMainC mesa/main/*.c)
FILE(GLOB _mesaProgramC mesa/program/*.c)
FILE(GLOB _mesaVboC mesa/vbo/*.c)
FILE(GLOB _mesaMathC mesa/math/*.c)
FILE(GLOB _mesaX86_64C mesa/x86-64/*.c)
FILE(GLOB _glslC glsl/*.c)
FILE(GLOB _mesaStateTrackerC mesa/state_tracker/*.c)
FILE(GLOB _glslGlcppC glsl/glcpp/*.c)

set(_libMesaGalliumC
  ${_mesaMainC}
  ${_mesaProgramC}
  ${_mesaVboC}
  ${_mesaMathC}
  ${_mesaX86_64C}
  ${_glslC}
  ${_mesaStateTrackerC}
  ${_glslGlcppC}
)

# Gallium C Files

FILE(GLOB _galliumAuxCsoCacheC gallium/auxiliary/cso_cache/*.c)
FILE(GLOB _galliumAuxDrawC gallium/auxiliary/draw/*.c)
FILE(GLOB _galliumAuxGallivmC gallium/auxiliary/gallivm/*.c)
FILE(GLOB _galliumAuxIndicesC gallium/auxiliary/indices/*.c)
FILE(GLOB _galliumAuxOsC gallium/auxiliary/os/*.c)
FILE(GLOB _galliumAuxPipeBufferC gallium/auxiliary/pipebuffer/*.c)
FILE(GLOB _galliumAuxPostProcessC gallium/auxiliary/postprocess/*.c)
FILE(GLOB _galliumAuxRBugC gallium/auxiliary/rbug/*.c)
FILE(GLOB _galliumAuxTgsiC gallium/auxiliary/tgsi/*.c)
FILE(GLOB _galliumAuxTranslateC gallium/auxiliary/translate/*.c)
FILE(GLOB _galliumAuxUtilC gallium/auxiliary/util/*.c)
FILE(GLOB _galliumAuxRtasmC gallium/auxiliary/rtasm/*.c)
FILE(GLOB _galliumAuxVlC gallium/auxiliary/vl/*.c)

set(_libGalliumC 
  ${_galliumAuxCsoCacheC}
  ${_galliumAuxDrawC}
  ${_galliumAuxGallivmC}
  ${_galliumAuxIndicesC}
  ${_galliumAuxOsC}
  ${_galliumAuxPipeBufferC}
  ${_galliumAuxPostProcessC}
  ${_galliumAuxRBugC}
  ${_galliumAuxTgsiC}
  ${_galliumAuxTranslateC}
  ${_galliumAuxUtilC}
  ${_galliumAuxRtasmC}
  ${_galliumAuxVlC}
)

# Trace C Files

FILE(GLOB _galliumDriversTraceC gallium/drivers/trace/*.c)

set(_libTraceC ${_galliumDriversTraceC})

# SoftPipe C Files

FILE(GLOB _galliumDriversSoftpipeC gallium/drivers/softpipe/*.c)

set(_libSoftpipeC ${_galliumDriversSoftpipeC})

# OS Mesa C Files

FILE(GLOB _galliumStateTrackersOsMesaC gallium/state_trackers/osmesa/*.c)

set(_libOsMesaC ${_galliumStateTrackersOsMesaC})

# GL API C Files

FILE(GLOB _mApiC mapi/u_*.c)
FILE(GLOB _glApiC mapi/glapi/*.c)

set(_libGlApi ${_mApiC} ${_glApiC})


# LLVM Pipe C Files

FILE(GLOB _galliumDriversLlvmPipeC gallium/drivers/llvmpipe/*.c)

set(_llvmPipeC ${_galliumDriversLlvmPipeC})

# Mesa Gallium CXX Files

FILE(GLOB _mesaProgramCxx mesa/program/*.cpp)
FILE(GLOB _mesaMainCxx mesa/main/*.cpp)
FILE(GLOB _mesaStateTrackerCxx mesa/state_tracker/*.cpp)
FILE(GLOB _glslCxx glsl/*.cpp)

set(_libMesaGalliumCxx
  ${_mesaProgramCxx}
  ${_mesaMainCxx}
  ${_mesaStateTrackerCxx}
  ${_glslCxx}  
)

# Gallium CXX Files

FILE(GLOB _galliumAuxGallivmCxx gallium/auxiliary/gallivm/*.cpp)

set(_libGalliumCxx ${_galliumAuxGallivmCxx})

LIST(
  APPEND
  _sources

  # C libraries
  ${_libMesaGalliumC}
  ${_libGalliumC}
  ${_libTraceC}
  ${_libSoftpipeC}
  ${_libOsMesaC}
  ${_libGlApi}
  ${_llvmPipeC}
  gallium/targets/osmesa/target.c

  # CXX libraries
  ${_libMesaGalliumCxx}
  ${_galliumAuxGallivmCxx}
)

ADD_LIBRARY(
  ${_target} STATIC
  ${_sources}
)

TARGET_COMPILE_OPTIONS(
  ${_target}
  PRIVATE
	-DPACKAGE_NAME="Mesa"	
	-DPACKAGE_TARNAME="mesa"	
	-DPACKAGE_VERSION=\"10.1.1\"
	-DPACKAGE_STRING="Mesa 10.1.1"
	-DPACKAGE="mesa"		
	-DPACKAGE_BUGREPORT=\"http\"
	-DVERSION="10.1.1"
	-DSTDC_HEADERS=1		
	-DHAVE_SYS_TYPES_H=1	
	-DHAVE_SYS_STAT_H=1	
	-DHAVE_STDLIB_H=1		
	-DHAVE_STRING_H=1		
	-DHAVE_MEMORY_H=1		
	-DHAVE_STRINGS_H=1	
	-DHAVE_INTTYPES_H=1	
	-DHAVE_STDINT_H=1		
	-DHAVE_UNISTD_H=1		
	-DHAVE_DLFCN_H=1		
	-DYYTEXT_POINTER=1	
	-DHAVE_PTHREAD=1		
	-D_GNU_SOURCE		
	-DTEXTURE_FLOAT_ENABLED	
	-DHAVE_DLOPEN=1		
	-DHAVE_POSIX_MEMALIGN=1	
	-DHAVE_MINCORE=1		
	-DHAVE_LLVM=$(LLVM_VERSION_LINUX)
	-DMAPI_MODE_UTIL=1	
	-D__STDC_LIMIT_MACROS	
	-D__STDC_CONSTANT_MACROS	
	-DHAVE_NULL_BACKEND=1	
	-D_EGL_MAIN=_eglMain	
  -D_EGL_EXTERNAL_GL=1 
  -D_EGL_NATIVE_PLATFORM=_EGL_PLATFORM_NULL
	-DGALLIUM_LLVMPIPE=1	
	-DGALLIUM_SOFTPIPE=1	
	-DGALLIUM_TRACE=1		
	-DFEATURE_GL=1
)

TARGET_INCLUDE_DIRECTORIES(
  ${_target} PUBLIC 
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${CMAKE_CURRENT_SOURCE_DIR}/mapi
  ${CMAKE_CURRENT_SOURCE_DIR}/mesa
  ${CMAKE_CURRENT_SOURCE_DIR}/mapi/glapi
  ${CMAKE_CURRENT_SOURCE_DIR}/glsl
  ${CMAKE_CURRENT_SOURCE_DIR}/glsl/glcpp
  ${CMAKE_CURRENT_SOURCE_DIR}/gallium/include
  ${CMAKE_CURRENT_SOURCE_DIR}/gallium/include/pipe
  ${CMAKE_CURRENT_SOURCE_DIR}/gallium/auxiliary
  ${CMAKE_CURRENT_SOURCE_DIR}/gallium/state_trackers/egl
  ${CMAKE_CURRENT_SOURCE_DIR}/gallium/drivers
  ${CMAKE_CURRENT_SOURCE_DIR}/egl/main
)

IF(RV_TARGET_LINUX)
  SET(THREADS_PREFER_PTHREAD_FLAG
      TRUE
  )
  FIND_PACKAGE(Threads REQUIRED)
  TARGET_LINK_LIBRARIES(
    ${_target}
    PUBLIC Threads::Threads rt dl m c
  )
ENDIF()


RV_STAGE(TYPE "LIBRARY" TARGET ${_target})

