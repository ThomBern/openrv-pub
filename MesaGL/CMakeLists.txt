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

message(${_libGalliumCxx})

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

TARGET_INCLUDE_DIRECTORIES(
  ${_target} PUBLIC 
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${CMAKE_CURRENT_SOURCE_DIR}/mesa
  ${CMAKE_CURRENT_SOURCE_DIR}/mapi
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

