#  -*- mode: makefile -*-
# 
#  Copyright (c) 2013 Tweak Software.
#  All rights reserved. 
# 

PROJECT	= MesaGL
# LICENSE and VERSION defs located in Makefile.common
# This project builds OSMesa (but calls it MesaGL)

# mesa/.libs/libmesagallium.a 
# gallium/auxiliary/.libs/libgallium.a 
# gallium/winsys/sw/null/.libs/libws_null.a 
# gallium/drivers/trace/.libs/libtrace.a 
# gallium/drivers/softpipe/.libs/libsoftpipe.a 
# gallium/state_trackers/osmesa/.libs/libosmesa.a 
# mapi/glapi/.libs/libglapi.a 
# gallium/drivers/llvmpipe/.libs/libllvmpipe.a
# -> libOSMesa.so

#TYPE = SHARED_LIBRARY
TYPE = LIBRARY

ifdef LLVM_VERSION
LLVM_VERSION_WINDOWS = $(LLVM_VERSION)
LLVM_VERSION_LINUX   = $(LLVM_VERSION)
LLVM_VERSION_DARWIN  = $(LLVM_VERSION)
else
LLVM_VERSION_WINDOWS = 0x0304
LLVM_VERSION_LINUX   = 0x0303
LLVM_VERSION_DARWIN  = 0x0303
LLVM_VERSION = $(call vargroupnr,LLVM_VERSION)
endif


#----------------------------------------------------------------------
# all libs that go into libOSMesa.so

CFILES = $(LIBMESAGALLIUM_CFILES)		\
	 $(LIBGALLIUM_CFILES)			\
	 $(LIBWS_NULL_CFILES)			\
	 $(LIBTRACE_CFILES)			\
	 $(LIBSOFTPIPE_CFILES)			\
	 $(LIBOSMESA_CFILES)			\
	 $(LIBGLAPI_CFILES)			\
	 $(LIBLLVMPIPE_CFILES)		        \
	 gallium/targets/osmesa/target

CXXFILES = $(LIBMESAGALLIUM_CXXFILES)  \
	   $(LIBGALLIUM_CXXFILES)

ifneq (,$(findstring DEFINES,USE_X86_64_ASM))
SFILES = $(LIBGLAPI_SFILES)
endif

VSTUDIO_VERSION_VC10= vs2010
VSTUDIO_VERSION_VC12 = vs2013

IPATH_WINDOWS = $(SRC_ROOT)/../lib/windows/llvm64/$(LLVM_VERSION_WINDOWS)/release-$(VSTUDIO_VERSION_$(COMPILER))/include


ifeq (0x0304,$(LLVM_VERSION_LINUX))
LPATH_LINUX  += /usr/lib64/llvm 
else
LPATH_LINUX  += /usr/local/lib/llvm-2.3/lib 
endif

IPATH_LINUX  += /usr/local/include

LPATH_DARWIN += /usr/local/lib
IPATH_DARWIN += /usr/local/include /usr/local/include/llvm

CXXFLAGS_LINUX  = -fno-exceptions -fno-rtti
CXXFLAGS_DARWIN = -fno-exceptions -fno-rtti

LIBS_LINUX  = pthread rt dl m c
LIBS_DARWIN = pthread


LIBS_LLVM_0x0303 = LLVMMCJIT LLVMBitWriter LLVMX86Disassembler		\
		 LLVMX86AsmParser LLVMX86CodeGen LLVMSelectionDAG	\
		 LLVMAsmPrinter LLVMMCParser LLVMX86Desc LLVMX86Info	\
		 LLVMX86AsmPrinter LLVMX86Utils LLVMJIT LLVMRuntimeDyld	\
		 LLVMExecutionEngine LLVMCodeGen LLVMObjCARCOpts	\
		 LLVMScalarOpts LLVMInstCombine LLVMTransformUtils	\
		 LLVMipa LLVMAnalysis LLVMTarget LLVMMC LLVMObject	\
		 LLVMCore LLVMSupport

LIBS_LLVM_0x0303_WINDOWS = $(LIBS_LLVM_0x0303)
LIBS_LLVM_0x0303_LINUX = $(LIBS_LLVM_0x0303)
LIBS_LLVM_0x0303_DARWIN = $(LIBS_LLVM_0x0303)

LIBS_LLVM_0x0304_DYNAMIC = LLVM-3.4

LIBS_LLVM_0x0304_STATIC = LLVMMCJIT LLVMBitWriter LLVMX86Disassembler	\
		 LLVMX86AsmParser LLVMX86CodeGen LLVMSelectionDAG	\
		 LLVMAsmPrinter LLVMMCParser LLVMX86Desc LLVMX86Info	\
		 LLVMX86AsmPrinter LLVMX86Utils LLVMJIT LLVMRuntimeDyld	\
		 LLVMExecutionEngine LLVMCodeGen LLVMObjCARCOpts	\
		 LLVMScalarOpts LLVMInstCombine LLVMTransformUtils	\
		 LLVMipa LLVMAnalysis LLVMTarget LLVMMC LLVMObject	\
		 LLVMCore LLVMSupport

ifneq ($(wildcard /etc/os-release),)
DISTRO_ID := $(shell awk 'BEGIN {FS = "="}/^ID=/{print $$2}' /etc/os-release)
DISTRO_VERSION := $(shell awk 'BEGIN {FS = "="}/^VERSION_ID=/{print $$2}' /etc/os-release | sed 's/"//g' )
DISTRO_FAMILY := $(DISTRO_ID)$(basename $(basename $(DISTRO_VERSION)))
endif

ifeq ($(HOST),ubuntu14)
LIBS_LLVM_0x0304_LINUX = $(LIBS_LLVM_0x0304_STATIC) tinfo
else
LIBS_LLVM_0x0304_LINUX = $(LIBS_LLVM_0x0304_DYNAMIC)
endif

LIBS_LLVM_0x0304_WINDOWS = $(LIBS_LLVM_0x0304_STATIC)


LIBS_LINUX = $(call vargroupnr,LIBS_LLVM_$(LLVM_VERSION_LINUX))
LIBS_WINDOWS = $(call vargroupnr,LIBS_LLVM_$(LLVM_VERSION_WINDOWS))
LIBS_DARWIN = $(call vargroupnr,LIBS_LLVM_$(LLVM_VERSION_DARWIN))

include $(SRC_ROOT)/pub/MesaGL/Makefile.common
include $(SRC_ROOT)/build/Makefile.master

ifeq ($(BUILD_TYPE),DEBUG)
LPATH_WINDOWS  += $(SRC_ROOT)/../lib/windows/llvm64/$(LLVM_VERSION_WINDOWS)/debug-$(VSTUDIO_VERSION_$(COMPILER))/lib
else
LPATH_WINDOWS  += $(SRC_ROOT)/../lib/windows/llvm64/$(LLVM_VERSION_WINDOWS)/release-$(VSTUDIO_VERSION_$(COMPILER))/lib
endif

ifneq ($(filter GCC%,$(COMPILER)),)
#
#   -O3/-O2 causes segfault gcc 4.8.x, so limiting this lib to -O
#

OPTFLAGS := -g -O -fno-schedule-insns -fno-schedule-insns2 -msse -msse2 -mmmx -mfpmath=sse -DNDEBUG
endif

