/**************************************************************************
 *
 * Copyright 2009 VMware, Inc.
 * All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sub license, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial portions
 * of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT.
 * IN NO EVENT SHALL VMWARE AND/OR ITS SUPPLIERS BE LIABLE FOR
 * ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 **************************************************************************/

/**
 * @file
 * Helper functions for calling intrinsics.
 *
 * @author Jose Fonseca <jfonseca@vmware.com>
 */


#ifndef LP_BLD_INTR_H
#define LP_BLD_INTR_H


#include "gallivm/lp_bld.h"
#include "gallivm/lp_bld_init.h"


/**
 * Max number of arguments in an intrinsic.
 */
#define LP_MAX_FUNC_ARGS 32

typedef enum {
    LLVMZExtAttribute       = 1<<0,
    LLVMSExtAttribute       = 1<<1,
    LLVMNoReturnAttribute   = 1<<2,
    LLVMInRegAttribute      = 1<<3,
    LLVMStructRetAttribute  = 1<<4,
    LLVMNoUnwindAttribute   = 1<<5,
    LLVMNoAliasAttribute    = 1<<6,
    LLVMByValAttribute      = 1<<7,
    LLVMNestAttribute       = 1<<8,
    LLVMReadNoneAttribute   = 1<<9,
    LLVMReadOnlyAttribute   = 1<<10,
    LLVMNoInlineAttribute   = 1<<11,
    LLVMAlwaysInlineAttribute    = 1<<12,
    LLVMOptimizeForSizeAttribute = 1<<13,
    LLVMStackProtectAttribute    = 1<<14,
    LLVMStackProtectReqAttribute = 1<<15,
    LLVMAlignment = 31<<16,
    LLVMNoCaptureAttribute  = 1<<21,
    LLVMNoRedZoneAttribute  = 1<<22,
    LLVMNoImplicitFloatAttribute = 1<<23,
    LLVMNakedAttribute      = 1<<24,
    LLVMInlineHintAttribute = 1<<25,
    LLVMStackAlignment = 7<<26,
    LLVMReturnsTwice = 1 << 29,
    LLVMUWTable = 1 << 30,
    LLVMNonLazyBind = 1 << 31

    /* FIXME: These attributes are currently not included in the C API as
       a temporary measure until the API/ABI impact to the C API is understood
       and the path forward agreed upon.
    LLVMAddressSafety = 1ULL << 32,
    LLVMStackProtectStrongAttribute = 1ULL<<33,
    LLVMCold = 1ULL << 34,
    LLVMOptimizeNone = 1ULL << 35
    */
} LLVMAttribute;


LLVMValueRef
lp_declare_intrinsic(LLVMModuleRef module,
                     const char *name,
                     LLVMTypeRef ret_type,
                     LLVMTypeRef *arg_types,
                     unsigned num_args);

LLVMValueRef
lp_build_intrinsic(LLVMBuilderRef builder,
                   const char *name,
                   LLVMTypeRef ret_type,
                   LLVMValueRef *args,
                   unsigned num_args);


LLVMValueRef
lp_build_intrinsic_unary(LLVMBuilderRef builder,
                         const char *name,
                         LLVMTypeRef ret_type,
                         LLVMValueRef a);


LLVMValueRef
lp_build_intrinsic_binary(LLVMBuilderRef builder,
                          const char *name,
                          LLVMTypeRef ret_type,
                          LLVMValueRef a,
                          LLVMValueRef b);


LLVMValueRef
lp_build_intrinsic_binary_anylength(struct gallivm_state *gallivm,
                                    const char *name,
                                    struct lp_type src_type,
                                    unsigned intr_size,
                                    LLVMValueRef a,
                                    LLVMValueRef b);


LLVMValueRef
lp_build_intrinsic_map(struct gallivm_state *gallivm,
                       const char *name,
                       LLVMTypeRef ret_type,
                       LLVMValueRef *args,
                       unsigned num_args);


LLVMValueRef
lp_build_intrinsic_map_unary(struct gallivm_state *gallivm,
                             const char *name,
                             LLVMTypeRef ret_type,
                             LLVMValueRef a);


LLVMValueRef
lp_build_intrinsic_map_binary(struct gallivm_state *gallivm,
                              const char *name,
                              LLVMTypeRef ret_type,
                              LLVMValueRef a,
                              LLVMValueRef b);


#endif /* !LP_BLD_INTR_H */
