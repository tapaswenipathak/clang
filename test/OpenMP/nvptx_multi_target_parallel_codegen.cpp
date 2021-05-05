// NOTE: Assertions have been autogenerated by utils/update_cc_test_checks.py UTC_ARGS: --function-signature --include-generated-funcs --replace-value-regex "__omp_offloading_[0-9a-z]+_[0-9a-z]+"
// Test target codegen - host bc file has to be created first.
// RUN: %clang_cc1 -verify -fopenmp -fopenmp-cuda-mode -x c++ -triple powerpc64le-unknown-unknown -fopenmp-targets=nvptx64-nvidia-cuda -emit-llvm-bc %s -o %t-ppc-host.bc
// RUN: %clang_cc1 -verify -fopenmp -fopenmp-cuda-mode -x c++ -triple nvptx64-unknown-unknown -fopenmp-targets=nvptx64-nvidia-cuda -emit-llvm %s -fopenmp-is-device -fopenmp-host-ir-file-path %t-ppc-host.bc -o - -disable-llvm-optzns | FileCheck %s --check-prefix CHECK1
// RUN: %clang_cc1 -verify -fopenmp -fopenmp-cuda-mode -x c++ -triple i386-unknown-unknown -fopenmp-targets=nvptx-nvidia-cuda -emit-llvm-bc %s -o %t-x86-host.bc
// RUN: %clang_cc1 -verify -fopenmp -fopenmp-cuda-mode -x c++ -triple nvptx-unknown-unknown -fopenmp-targets=nvptx-nvidia-cuda -emit-llvm %s -fopenmp-is-device -fopenmp-host-ir-file-path %t-x86-host.bc -o - -disable-llvm-optzns | FileCheck %s --check-prefix CHECK2
// RUN: %clang_cc1 -verify -fopenmp -fopenmp-cuda-mode -fexceptions -fcxx-exceptions -x c++ -triple nvptx-unknown-unknown -fopenmp-targets=nvptx-nvidia-cuda -emit-llvm %s -fopenmp-is-device -fopenmp-host-ir-file-path %t-x86-host.bc -o - -disable-llvm-optzns | FileCheck %s --check-prefix CHECK3

// expected-no-diagnostics
#ifndef HEADER
#define HEADER

void work();

void use() {
      #pragma omp parallel
      work();
}

int main() {
      #pragma omp target parallel
      {  use(); }
        #pragma omp target
        {  use(); }
}

#endif
// CHECK1-LABEL: define {{[^@]+}}@{{__omp_offloading_[0-9a-z]+_[0-9a-z]+}}_main_l21
// CHECK1-SAME: () #[[ATTR0:[0-9]+]] {
// CHECK1-NEXT:  entry:
// CHECK1-NEXT:    [[CAPTURED_VARS_ADDRS:%.*]] = alloca [0 x i8*], align 8
// CHECK1-NEXT:    [[NVPTX_NUM_THREADS:%.*]] = call i32 @llvm.nvvm.read.ptx.sreg.ntid.x()
// CHECK1-NEXT:    call void @__kmpc_spmd_kernel_init(i32 [[NVPTX_NUM_THREADS]], i16 1)
// CHECK1-NEXT:    call void @__kmpc_data_sharing_init_stack_spmd()
// CHECK1-NEXT:    br label [[DOTEXECUTE:%.*]]
// CHECK1:       .execute:
// CHECK1-NEXT:    [[TMP0:%.*]] = call i32 @__kmpc_global_thread_num(%struct.ident_t* @[[GLOB1:[0-9]+]])
// CHECK1-NEXT:    [[TMP1:%.*]] = bitcast [0 x i8*]* [[CAPTURED_VARS_ADDRS]] to i8**
// CHECK1-NEXT:    call void @__kmpc_parallel_51(%struct.ident_t* @[[GLOB1]], i32 [[TMP0]], i32 1, i32 -1, i32 -1, i8* bitcast (void (i32*, i32*)* @__omp_outlined__ to i8*), i8* null, i8** [[TMP1]], i64 0)
// CHECK1-NEXT:    br label [[DOTOMP_DEINIT:%.*]]
// CHECK1:       .omp.deinit:
// CHECK1-NEXT:    call void @__kmpc_spmd_kernel_deinit_v2(i16 1)
// CHECK1-NEXT:    br label [[DOTEXIT:%.*]]
// CHECK1:       .exit:
// CHECK1-NEXT:    ret void
//
//
// CHECK1-LABEL: define {{[^@]+}}@__omp_outlined__
// CHECK1-SAME: (i32* noalias [[DOTGLOBAL_TID_:%.*]], i32* noalias [[DOTBOUND_TID_:%.*]]) #[[ATTR0]] {
// CHECK1-NEXT:  entry:
// CHECK1-NEXT:    [[DOTGLOBAL_TID__ADDR:%.*]] = alloca i32*, align 8
// CHECK1-NEXT:    [[DOTBOUND_TID__ADDR:%.*]] = alloca i32*, align 8
// CHECK1-NEXT:    store i32* [[DOTGLOBAL_TID_]], i32** [[DOTGLOBAL_TID__ADDR]], align 8
// CHECK1-NEXT:    store i32* [[DOTBOUND_TID_]], i32** [[DOTBOUND_TID__ADDR]], align 8
// CHECK1-NEXT:    call void @_Z3usev() #[[ATTR7:[0-9]+]]
// CHECK1-NEXT:    ret void
//
//
// CHECK1-LABEL: define {{[^@]+}}@_Z3usev
// CHECK1-SAME: () #[[ATTR2:[0-9]+]] {
// CHECK1-NEXT:  entry:
// CHECK1-NEXT:    [[CAPTURED_VARS_ADDRS:%.*]] = alloca [0 x i8*], align 8
// CHECK1-NEXT:    [[TMP0:%.*]] = call i32 @__kmpc_global_thread_num(%struct.ident_t* @[[GLOB1]])
// CHECK1-NEXT:    [[TMP1:%.*]] = bitcast [0 x i8*]* [[CAPTURED_VARS_ADDRS]] to i8**
// CHECK1-NEXT:    call void @__kmpc_parallel_51(%struct.ident_t* @[[GLOB1]], i32 [[TMP0]], i32 1, i32 -1, i32 -1, i8* bitcast (void (i32*, i32*)* @__omp_outlined__1 to i8*), i8* null, i8** [[TMP1]], i64 0)
// CHECK1-NEXT:    ret void
//
//
// CHECK1-LABEL: define {{[^@]+}}@__omp_outlined__1
// CHECK1-SAME: (i32* noalias [[DOTGLOBAL_TID_:%.*]], i32* noalias [[DOTBOUND_TID_:%.*]]) #[[ATTR0]] {
// CHECK1-NEXT:  entry:
// CHECK1-NEXT:    [[DOTGLOBAL_TID__ADDR:%.*]] = alloca i32*, align 8
// CHECK1-NEXT:    [[DOTBOUND_TID__ADDR:%.*]] = alloca i32*, align 8
// CHECK1-NEXT:    store i32* [[DOTGLOBAL_TID_]], i32** [[DOTGLOBAL_TID__ADDR]], align 8
// CHECK1-NEXT:    store i32* [[DOTBOUND_TID_]], i32** [[DOTBOUND_TID__ADDR]], align 8
// CHECK1-NEXT:    call void @_Z4workv() #[[ATTR7]]
// CHECK1-NEXT:    ret void
//
//
// CHECK1-LABEL: define {{[^@]+}}@{{__omp_offloading_[0-9a-z]+_[0-9a-z]+}}_main_l23_worker
// CHECK1-SAME: () #[[ATTR5:[0-9]+]] {
// CHECK1-NEXT:  entry:
// CHECK1-NEXT:    [[WORK_FN:%.*]] = alloca i8*, align 8
// CHECK1-NEXT:    [[EXEC_STATUS:%.*]] = alloca i8, align 1
// CHECK1-NEXT:    store i8* null, i8** [[WORK_FN]], align 8
// CHECK1-NEXT:    store i8 0, i8* [[EXEC_STATUS]], align 1
// CHECK1-NEXT:    br label [[DOTAWAIT_WORK:%.*]]
// CHECK1:       .await.work:
// CHECK1-NEXT:    call void @__kmpc_barrier_simple_spmd(%struct.ident_t* null, i32 0)
// CHECK1-NEXT:    [[TMP0:%.*]] = call i1 @__kmpc_kernel_parallel(i8** [[WORK_FN]])
// CHECK1-NEXT:    [[TMP1:%.*]] = zext i1 [[TMP0]] to i8
// CHECK1-NEXT:    store i8 [[TMP1]], i8* [[EXEC_STATUS]], align 1
// CHECK1-NEXT:    [[TMP2:%.*]] = load i8*, i8** [[WORK_FN]], align 8
// CHECK1-NEXT:    [[SHOULD_TERMINATE:%.*]] = icmp eq i8* [[TMP2]], null
// CHECK1-NEXT:    br i1 [[SHOULD_TERMINATE]], label [[DOTEXIT:%.*]], label [[DOTSELECT_WORKERS:%.*]]
// CHECK1:       .select.workers:
// CHECK1-NEXT:    [[TMP3:%.*]] = load i8, i8* [[EXEC_STATUS]], align 1
// CHECK1-NEXT:    [[IS_ACTIVE:%.*]] = icmp ne i8 [[TMP3]], 0
// CHECK1-NEXT:    br i1 [[IS_ACTIVE]], label [[DOTEXECUTE_PARALLEL:%.*]], label [[DOTBARRIER_PARALLEL:%.*]]
// CHECK1:       .execute.parallel:
// CHECK1-NEXT:    [[TMP4:%.*]] = call i32 @__kmpc_global_thread_num(%struct.ident_t* @[[GLOB2:[0-9]+]])
// CHECK1-NEXT:    [[TMP5:%.*]] = bitcast i8* [[TMP2]] to void (i16, i32)*
// CHECK1-NEXT:    call void [[TMP5]](i16 0, i32 [[TMP4]])
// CHECK1-NEXT:    br label [[DOTTERMINATE_PARALLEL:%.*]]
// CHECK1:       .terminate.parallel:
// CHECK1-NEXT:    call void @__kmpc_kernel_end_parallel()
// CHECK1-NEXT:    br label [[DOTBARRIER_PARALLEL]]
// CHECK1:       .barrier.parallel:
// CHECK1-NEXT:    call void @__kmpc_barrier_simple_spmd(%struct.ident_t* null, i32 0)
// CHECK1-NEXT:    br label [[DOTAWAIT_WORK]]
// CHECK1:       .exit:
// CHECK1-NEXT:    ret void
//
//
// CHECK1-LABEL: define {{[^@]+}}@{{__omp_offloading_[0-9a-z]+_[0-9a-z]+}}_main_l23
// CHECK1-SAME: () #[[ATTR0]] {
// CHECK1-NEXT:  entry:
// CHECK1-NEXT:    [[NVPTX_TID:%.*]] = call i32 @llvm.nvvm.read.ptx.sreg.tid.x()
// CHECK1-NEXT:    [[NVPTX_NUM_THREADS:%.*]] = call i32 @llvm.nvvm.read.ptx.sreg.ntid.x()
// CHECK1-NEXT:    [[NVPTX_WARP_SIZE:%.*]] = call i32 @llvm.nvvm.read.ptx.sreg.warpsize()
// CHECK1-NEXT:    [[THREAD_LIMIT:%.*]] = sub nuw i32 [[NVPTX_NUM_THREADS]], [[NVPTX_WARP_SIZE]]
// CHECK1-NEXT:    [[TMP0:%.*]] = icmp ult i32 [[NVPTX_TID]], [[THREAD_LIMIT]]
// CHECK1-NEXT:    br i1 [[TMP0]], label [[DOTWORKER:%.*]], label [[DOTMASTERCHECK:%.*]]
// CHECK1:       .worker:
// CHECK1-NEXT:    call void @{{__omp_offloading_[0-9a-z]+_[0-9a-z]+}}_main_l23_worker() #[[ATTR4:[0-9]+]]
// CHECK1-NEXT:    br label [[DOTEXIT:%.*]]
// CHECK1:       .mastercheck:
// CHECK1-NEXT:    [[NVPTX_TID1:%.*]] = call i32 @llvm.nvvm.read.ptx.sreg.tid.x()
// CHECK1-NEXT:    [[NVPTX_NUM_THREADS2:%.*]] = call i32 @llvm.nvvm.read.ptx.sreg.ntid.x()
// CHECK1-NEXT:    [[NVPTX_WARP_SIZE3:%.*]] = call i32 @llvm.nvvm.read.ptx.sreg.warpsize()
// CHECK1-NEXT:    [[TMP1:%.*]] = sub nuw i32 [[NVPTX_WARP_SIZE3]], 1
// CHECK1-NEXT:    [[TMP2:%.*]] = sub nuw i32 [[NVPTX_NUM_THREADS2]], 1
// CHECK1-NEXT:    [[TMP3:%.*]] = xor i32 [[TMP1]], -1
// CHECK1-NEXT:    [[MASTER_TID:%.*]] = and i32 [[TMP2]], [[TMP3]]
// CHECK1-NEXT:    [[TMP4:%.*]] = icmp eq i32 [[NVPTX_TID1]], [[MASTER_TID]]
// CHECK1-NEXT:    br i1 [[TMP4]], label [[DOTMASTER:%.*]], label [[DOTEXIT]]
// CHECK1:       .master:
// CHECK1-NEXT:    [[NVPTX_NUM_THREADS4:%.*]] = call i32 @llvm.nvvm.read.ptx.sreg.ntid.x()
// CHECK1-NEXT:    [[NVPTX_WARP_SIZE5:%.*]] = call i32 @llvm.nvvm.read.ptx.sreg.warpsize()
// CHECK1-NEXT:    [[THREAD_LIMIT6:%.*]] = sub nuw i32 [[NVPTX_NUM_THREADS4]], [[NVPTX_WARP_SIZE5]]
// CHECK1-NEXT:    call void @__kmpc_kernel_init(i32 [[THREAD_LIMIT6]], i16 1)
// CHECK1-NEXT:    call void @__kmpc_data_sharing_init_stack()
// CHECK1-NEXT:    call void @_Z3usev() #[[ATTR7]]
// CHECK1-NEXT:    br label [[DOTTERMINATION_NOTIFIER:%.*]]
// CHECK1:       .termination.notifier:
// CHECK1-NEXT:    call void @__kmpc_kernel_deinit(i16 1)
// CHECK1-NEXT:    call void @__kmpc_barrier_simple_spmd(%struct.ident_t* null, i32 0)
// CHECK1-NEXT:    br label [[DOTEXIT]]
// CHECK1:       .exit:
// CHECK1-NEXT:    ret void
//
//
// CHECK2-LABEL: define {{[^@]+}}@{{__omp_offloading_[0-9a-z]+_[0-9a-z]+}}_main_l21
// CHECK2-SAME: () #[[ATTR0:[0-9]+]] {
// CHECK2-NEXT:  entry:
// CHECK2-NEXT:    [[CAPTURED_VARS_ADDRS:%.*]] = alloca [0 x i8*], align 4
// CHECK2-NEXT:    [[NVPTX_NUM_THREADS:%.*]] = call i32 @llvm.nvvm.read.ptx.sreg.ntid.x()
// CHECK2-NEXT:    call void @__kmpc_spmd_kernel_init(i32 [[NVPTX_NUM_THREADS]], i16 1)
// CHECK2-NEXT:    call void @__kmpc_data_sharing_init_stack_spmd()
// CHECK2-NEXT:    br label [[DOTEXECUTE:%.*]]
// CHECK2:       .execute:
// CHECK2-NEXT:    [[TMP0:%.*]] = call i32 @__kmpc_global_thread_num(%struct.ident_t* @[[GLOB1:[0-9]+]])
// CHECK2-NEXT:    [[TMP1:%.*]] = bitcast [0 x i8*]* [[CAPTURED_VARS_ADDRS]] to i8**
// CHECK2-NEXT:    call void @__kmpc_parallel_51(%struct.ident_t* @[[GLOB1]], i32 [[TMP0]], i32 1, i32 -1, i32 -1, i8* bitcast (void (i32*, i32*)* @__omp_outlined__ to i8*), i8* null, i8** [[TMP1]], i32 0)
// CHECK2-NEXT:    br label [[DOTOMP_DEINIT:%.*]]
// CHECK2:       .omp.deinit:
// CHECK2-NEXT:    call void @__kmpc_spmd_kernel_deinit_v2(i16 1)
// CHECK2-NEXT:    br label [[DOTEXIT:%.*]]
// CHECK2:       .exit:
// CHECK2-NEXT:    ret void
//
//
// CHECK2-LABEL: define {{[^@]+}}@__omp_outlined__
// CHECK2-SAME: (i32* noalias [[DOTGLOBAL_TID_:%.*]], i32* noalias [[DOTBOUND_TID_:%.*]]) #[[ATTR0]] {
// CHECK2-NEXT:  entry:
// CHECK2-NEXT:    [[DOTGLOBAL_TID__ADDR:%.*]] = alloca i32*, align 4
// CHECK2-NEXT:    [[DOTBOUND_TID__ADDR:%.*]] = alloca i32*, align 4
// CHECK2-NEXT:    store i32* [[DOTGLOBAL_TID_]], i32** [[DOTGLOBAL_TID__ADDR]], align 4
// CHECK2-NEXT:    store i32* [[DOTBOUND_TID_]], i32** [[DOTBOUND_TID__ADDR]], align 4
// CHECK2-NEXT:    call void @_Z3usev() #[[ATTR7:[0-9]+]]
// CHECK2-NEXT:    ret void
//
//
// CHECK2-LABEL: define {{[^@]+}}@_Z3usev
// CHECK2-SAME: () #[[ATTR2:[0-9]+]] {
// CHECK2-NEXT:  entry:
// CHECK2-NEXT:    [[CAPTURED_VARS_ADDRS:%.*]] = alloca [0 x i8*], align 4
// CHECK2-NEXT:    [[TMP0:%.*]] = call i32 @__kmpc_global_thread_num(%struct.ident_t* @[[GLOB1]])
// CHECK2-NEXT:    [[TMP1:%.*]] = bitcast [0 x i8*]* [[CAPTURED_VARS_ADDRS]] to i8**
// CHECK2-NEXT:    call void @__kmpc_parallel_51(%struct.ident_t* @[[GLOB1]], i32 [[TMP0]], i32 1, i32 -1, i32 -1, i8* bitcast (void (i32*, i32*)* @__omp_outlined__1 to i8*), i8* null, i8** [[TMP1]], i32 0)
// CHECK2-NEXT:    ret void
//
//
// CHECK2-LABEL: define {{[^@]+}}@__omp_outlined__1
// CHECK2-SAME: (i32* noalias [[DOTGLOBAL_TID_:%.*]], i32* noalias [[DOTBOUND_TID_:%.*]]) #[[ATTR0]] {
// CHECK2-NEXT:  entry:
// CHECK2-NEXT:    [[DOTGLOBAL_TID__ADDR:%.*]] = alloca i32*, align 4
// CHECK2-NEXT:    [[DOTBOUND_TID__ADDR:%.*]] = alloca i32*, align 4
// CHECK2-NEXT:    store i32* [[DOTGLOBAL_TID_]], i32** [[DOTGLOBAL_TID__ADDR]], align 4
// CHECK2-NEXT:    store i32* [[DOTBOUND_TID_]], i32** [[DOTBOUND_TID__ADDR]], align 4
// CHECK2-NEXT:    call void @_Z4workv() #[[ATTR7]]
// CHECK2-NEXT:    ret void
//
//
// CHECK2-LABEL: define {{[^@]+}}@{{__omp_offloading_[0-9a-z]+_[0-9a-z]+}}_main_l23_worker
// CHECK2-SAME: () #[[ATTR5:[0-9]+]] {
// CHECK2-NEXT:  entry:
// CHECK2-NEXT:    [[WORK_FN:%.*]] = alloca i8*, align 4
// CHECK2-NEXT:    [[EXEC_STATUS:%.*]] = alloca i8, align 1
// CHECK2-NEXT:    store i8* null, i8** [[WORK_FN]], align 4
// CHECK2-NEXT:    store i8 0, i8* [[EXEC_STATUS]], align 1
// CHECK2-NEXT:    br label [[DOTAWAIT_WORK:%.*]]
// CHECK2:       .await.work:
// CHECK2-NEXT:    call void @__kmpc_barrier_simple_spmd(%struct.ident_t* null, i32 0)
// CHECK2-NEXT:    [[TMP0:%.*]] = call i1 @__kmpc_kernel_parallel(i8** [[WORK_FN]])
// CHECK2-NEXT:    [[TMP1:%.*]] = zext i1 [[TMP0]] to i8
// CHECK2-NEXT:    store i8 [[TMP1]], i8* [[EXEC_STATUS]], align 1
// CHECK2-NEXT:    [[TMP2:%.*]] = load i8*, i8** [[WORK_FN]], align 4
// CHECK2-NEXT:    [[SHOULD_TERMINATE:%.*]] = icmp eq i8* [[TMP2]], null
// CHECK2-NEXT:    br i1 [[SHOULD_TERMINATE]], label [[DOTEXIT:%.*]], label [[DOTSELECT_WORKERS:%.*]]
// CHECK2:       .select.workers:
// CHECK2-NEXT:    [[TMP3:%.*]] = load i8, i8* [[EXEC_STATUS]], align 1
// CHECK2-NEXT:    [[IS_ACTIVE:%.*]] = icmp ne i8 [[TMP3]], 0
// CHECK2-NEXT:    br i1 [[IS_ACTIVE]], label [[DOTEXECUTE_PARALLEL:%.*]], label [[DOTBARRIER_PARALLEL:%.*]]
// CHECK2:       .execute.parallel:
// CHECK2-NEXT:    [[TMP4:%.*]] = call i32 @__kmpc_global_thread_num(%struct.ident_t* @[[GLOB2:[0-9]+]])
// CHECK2-NEXT:    [[TMP5:%.*]] = bitcast i8* [[TMP2]] to void (i16, i32)*
// CHECK2-NEXT:    call void [[TMP5]](i16 0, i32 [[TMP4]])
// CHECK2-NEXT:    br label [[DOTTERMINATE_PARALLEL:%.*]]
// CHECK2:       .terminate.parallel:
// CHECK2-NEXT:    call void @__kmpc_kernel_end_parallel()
// CHECK2-NEXT:    br label [[DOTBARRIER_PARALLEL]]
// CHECK2:       .barrier.parallel:
// CHECK2-NEXT:    call void @__kmpc_barrier_simple_spmd(%struct.ident_t* null, i32 0)
// CHECK2-NEXT:    br label [[DOTAWAIT_WORK]]
// CHECK2:       .exit:
// CHECK2-NEXT:    ret void
//
//
// CHECK2-LABEL: define {{[^@]+}}@{{__omp_offloading_[0-9a-z]+_[0-9a-z]+}}_main_l23
// CHECK2-SAME: () #[[ATTR0]] {
// CHECK2-NEXT:  entry:
// CHECK2-NEXT:    [[NVPTX_TID:%.*]] = call i32 @llvm.nvvm.read.ptx.sreg.tid.x()
// CHECK2-NEXT:    [[NVPTX_NUM_THREADS:%.*]] = call i32 @llvm.nvvm.read.ptx.sreg.ntid.x()
// CHECK2-NEXT:    [[NVPTX_WARP_SIZE:%.*]] = call i32 @llvm.nvvm.read.ptx.sreg.warpsize()
// CHECK2-NEXT:    [[THREAD_LIMIT:%.*]] = sub nuw i32 [[NVPTX_NUM_THREADS]], [[NVPTX_WARP_SIZE]]
// CHECK2-NEXT:    [[TMP0:%.*]] = icmp ult i32 [[NVPTX_TID]], [[THREAD_LIMIT]]
// CHECK2-NEXT:    br i1 [[TMP0]], label [[DOTWORKER:%.*]], label [[DOTMASTERCHECK:%.*]]
// CHECK2:       .worker:
// CHECK2-NEXT:    call void @{{__omp_offloading_[0-9a-z]+_[0-9a-z]+}}_main_l23_worker() #[[ATTR4:[0-9]+]]
// CHECK2-NEXT:    br label [[DOTEXIT:%.*]]
// CHECK2:       .mastercheck:
// CHECK2-NEXT:    [[NVPTX_TID1:%.*]] = call i32 @llvm.nvvm.read.ptx.sreg.tid.x()
// CHECK2-NEXT:    [[NVPTX_NUM_THREADS2:%.*]] = call i32 @llvm.nvvm.read.ptx.sreg.ntid.x()
// CHECK2-NEXT:    [[NVPTX_WARP_SIZE3:%.*]] = call i32 @llvm.nvvm.read.ptx.sreg.warpsize()
// CHECK2-NEXT:    [[TMP1:%.*]] = sub nuw i32 [[NVPTX_WARP_SIZE3]], 1
// CHECK2-NEXT:    [[TMP2:%.*]] = sub nuw i32 [[NVPTX_NUM_THREADS2]], 1
// CHECK2-NEXT:    [[TMP3:%.*]] = xor i32 [[TMP1]], -1
// CHECK2-NEXT:    [[MASTER_TID:%.*]] = and i32 [[TMP2]], [[TMP3]]
// CHECK2-NEXT:    [[TMP4:%.*]] = icmp eq i32 [[NVPTX_TID1]], [[MASTER_TID]]
// CHECK2-NEXT:    br i1 [[TMP4]], label [[DOTMASTER:%.*]], label [[DOTEXIT]]
// CHECK2:       .master:
// CHECK2-NEXT:    [[NVPTX_NUM_THREADS4:%.*]] = call i32 @llvm.nvvm.read.ptx.sreg.ntid.x()
// CHECK2-NEXT:    [[NVPTX_WARP_SIZE5:%.*]] = call i32 @llvm.nvvm.read.ptx.sreg.warpsize()
// CHECK2-NEXT:    [[THREAD_LIMIT6:%.*]] = sub nuw i32 [[NVPTX_NUM_THREADS4]], [[NVPTX_WARP_SIZE5]]
// CHECK2-NEXT:    call void @__kmpc_kernel_init(i32 [[THREAD_LIMIT6]], i16 1)
// CHECK2-NEXT:    call void @__kmpc_data_sharing_init_stack()
// CHECK2-NEXT:    call void @_Z3usev() #[[ATTR7]]
// CHECK2-NEXT:    br label [[DOTTERMINATION_NOTIFIER:%.*]]
// CHECK2:       .termination.notifier:
// CHECK2-NEXT:    call void @__kmpc_kernel_deinit(i16 1)
// CHECK2-NEXT:    call void @__kmpc_barrier_simple_spmd(%struct.ident_t* null, i32 0)
// CHECK2-NEXT:    br label [[DOTEXIT]]
// CHECK2:       .exit:
// CHECK2-NEXT:    ret void
//
//
// CHECK3-LABEL: define {{[^@]+}}@{{__omp_offloading_[0-9a-z]+_[0-9a-z]+}}_main_l21
// CHECK3-SAME: () #[[ATTR0:[0-9]+]] {
// CHECK3-NEXT:  entry:
// CHECK3-NEXT:    [[CAPTURED_VARS_ADDRS:%.*]] = alloca [0 x i8*], align 4
// CHECK3-NEXT:    [[NVPTX_NUM_THREADS:%.*]] = call i32 @llvm.nvvm.read.ptx.sreg.ntid.x()
// CHECK3-NEXT:    call void @__kmpc_spmd_kernel_init(i32 [[NVPTX_NUM_THREADS]], i16 1)
// CHECK3-NEXT:    call void @__kmpc_data_sharing_init_stack_spmd()
// CHECK3-NEXT:    br label [[DOTEXECUTE:%.*]]
// CHECK3:       .execute:
// CHECK3-NEXT:    [[TMP0:%.*]] = call i32 @__kmpc_global_thread_num(%struct.ident_t* @[[GLOB1:[0-9]+]])
// CHECK3-NEXT:    [[TMP1:%.*]] = bitcast [0 x i8*]* [[CAPTURED_VARS_ADDRS]] to i8**
// CHECK3-NEXT:    call void @__kmpc_parallel_51(%struct.ident_t* @[[GLOB1]], i32 [[TMP0]], i32 1, i32 -1, i32 -1, i8* bitcast (void (i32*, i32*)* @__omp_outlined__ to i8*), i8* null, i8** [[TMP1]], i32 0)
// CHECK3-NEXT:    br label [[DOTOMP_DEINIT:%.*]]
// CHECK3:       .omp.deinit:
// CHECK3-NEXT:    call void @__kmpc_spmd_kernel_deinit_v2(i16 1)
// CHECK3-NEXT:    br label [[DOTEXIT:%.*]]
// CHECK3:       .exit:
// CHECK3-NEXT:    ret void
//
//
// CHECK3-LABEL: define {{[^@]+}}@__omp_outlined__
// CHECK3-SAME: (i32* noalias [[DOTGLOBAL_TID_:%.*]], i32* noalias [[DOTBOUND_TID_:%.*]]) #[[ATTR0]] {
// CHECK3-NEXT:  entry:
// CHECK3-NEXT:    [[DOTGLOBAL_TID__ADDR:%.*]] = alloca i32*, align 4
// CHECK3-NEXT:    [[DOTBOUND_TID__ADDR:%.*]] = alloca i32*, align 4
// CHECK3-NEXT:    store i32* [[DOTGLOBAL_TID_]], i32** [[DOTGLOBAL_TID__ADDR]], align 4
// CHECK3-NEXT:    store i32* [[DOTBOUND_TID_]], i32** [[DOTBOUND_TID__ADDR]], align 4
// CHECK3-NEXT:    call void @_Z3usev() #[[ATTR7:[0-9]+]]
// CHECK3-NEXT:    ret void
//
//
// CHECK3-LABEL: define {{[^@]+}}@_Z3usev
// CHECK3-SAME: () #[[ATTR2:[0-9]+]] {
// CHECK3-NEXT:  entry:
// CHECK3-NEXT:    [[CAPTURED_VARS_ADDRS:%.*]] = alloca [0 x i8*], align 4
// CHECK3-NEXT:    [[TMP0:%.*]] = call i32 @__kmpc_global_thread_num(%struct.ident_t* @[[GLOB1]])
// CHECK3-NEXT:    [[TMP1:%.*]] = bitcast [0 x i8*]* [[CAPTURED_VARS_ADDRS]] to i8**
// CHECK3-NEXT:    call void @__kmpc_parallel_51(%struct.ident_t* @[[GLOB1]], i32 [[TMP0]], i32 1, i32 -1, i32 -1, i8* bitcast (void (i32*, i32*)* @__omp_outlined__1 to i8*), i8* null, i8** [[TMP1]], i32 0)
// CHECK3-NEXT:    ret void
//
//
// CHECK3-LABEL: define {{[^@]+}}@__omp_outlined__1
// CHECK3-SAME: (i32* noalias [[DOTGLOBAL_TID_:%.*]], i32* noalias [[DOTBOUND_TID_:%.*]]) #[[ATTR0]] {
// CHECK3-NEXT:  entry:
// CHECK3-NEXT:    [[DOTGLOBAL_TID__ADDR:%.*]] = alloca i32*, align 4
// CHECK3-NEXT:    [[DOTBOUND_TID__ADDR:%.*]] = alloca i32*, align 4
// CHECK3-NEXT:    store i32* [[DOTGLOBAL_TID_]], i32** [[DOTGLOBAL_TID__ADDR]], align 4
// CHECK3-NEXT:    store i32* [[DOTBOUND_TID_]], i32** [[DOTBOUND_TID__ADDR]], align 4
// CHECK3-NEXT:    call void @_Z4workv() #[[ATTR7]]
// CHECK3-NEXT:    ret void
//
//
// CHECK3-LABEL: define {{[^@]+}}@{{__omp_offloading_[0-9a-z]+_[0-9a-z]+}}_main_l23_worker
// CHECK3-SAME: () #[[ATTR5:[0-9]+]] {
// CHECK3-NEXT:  entry:
// CHECK3-NEXT:    [[WORK_FN:%.*]] = alloca i8*, align 4
// CHECK3-NEXT:    [[EXEC_STATUS:%.*]] = alloca i8, align 1
// CHECK3-NEXT:    store i8* null, i8** [[WORK_FN]], align 4
// CHECK3-NEXT:    store i8 0, i8* [[EXEC_STATUS]], align 1
// CHECK3-NEXT:    br label [[DOTAWAIT_WORK:%.*]]
// CHECK3:       .await.work:
// CHECK3-NEXT:    call void @__kmpc_barrier_simple_spmd(%struct.ident_t* null, i32 0)
// CHECK3-NEXT:    [[TMP0:%.*]] = call i1 @__kmpc_kernel_parallel(i8** [[WORK_FN]])
// CHECK3-NEXT:    [[TMP1:%.*]] = zext i1 [[TMP0]] to i8
// CHECK3-NEXT:    store i8 [[TMP1]], i8* [[EXEC_STATUS]], align 1
// CHECK3-NEXT:    [[TMP2:%.*]] = load i8*, i8** [[WORK_FN]], align 4
// CHECK3-NEXT:    [[SHOULD_TERMINATE:%.*]] = icmp eq i8* [[TMP2]], null
// CHECK3-NEXT:    br i1 [[SHOULD_TERMINATE]], label [[DOTEXIT:%.*]], label [[DOTSELECT_WORKERS:%.*]]
// CHECK3:       .select.workers:
// CHECK3-NEXT:    [[TMP3:%.*]] = load i8, i8* [[EXEC_STATUS]], align 1
// CHECK3-NEXT:    [[IS_ACTIVE:%.*]] = icmp ne i8 [[TMP3]], 0
// CHECK3-NEXT:    br i1 [[IS_ACTIVE]], label [[DOTEXECUTE_PARALLEL:%.*]], label [[DOTBARRIER_PARALLEL:%.*]]
// CHECK3:       .execute.parallel:
// CHECK3-NEXT:    [[TMP4:%.*]] = call i32 @__kmpc_global_thread_num(%struct.ident_t* @[[GLOB2:[0-9]+]])
// CHECK3-NEXT:    [[TMP5:%.*]] = bitcast i8* [[TMP2]] to void (i16, i32)*
// CHECK3-NEXT:    call void [[TMP5]](i16 0, i32 [[TMP4]])
// CHECK3-NEXT:    br label [[DOTTERMINATE_PARALLEL:%.*]]
// CHECK3:       .terminate.parallel:
// CHECK3-NEXT:    call void @__kmpc_kernel_end_parallel()
// CHECK3-NEXT:    br label [[DOTBARRIER_PARALLEL]]
// CHECK3:       .barrier.parallel:
// CHECK3-NEXT:    call void @__kmpc_barrier_simple_spmd(%struct.ident_t* null, i32 0)
// CHECK3-NEXT:    br label [[DOTAWAIT_WORK]]
// CHECK3:       .exit:
// CHECK3-NEXT:    ret void
//
//
// CHECK3-LABEL: define {{[^@]+}}@{{__omp_offloading_[0-9a-z]+_[0-9a-z]+}}_main_l23
// CHECK3-SAME: () #[[ATTR0]] {
// CHECK3-NEXT:  entry:
// CHECK3-NEXT:    [[NVPTX_TID:%.*]] = call i32 @llvm.nvvm.read.ptx.sreg.tid.x()
// CHECK3-NEXT:    [[NVPTX_NUM_THREADS:%.*]] = call i32 @llvm.nvvm.read.ptx.sreg.ntid.x()
// CHECK3-NEXT:    [[NVPTX_WARP_SIZE:%.*]] = call i32 @llvm.nvvm.read.ptx.sreg.warpsize()
// CHECK3-NEXT:    [[THREAD_LIMIT:%.*]] = sub nuw i32 [[NVPTX_NUM_THREADS]], [[NVPTX_WARP_SIZE]]
// CHECK3-NEXT:    [[TMP0:%.*]] = icmp ult i32 [[NVPTX_TID]], [[THREAD_LIMIT]]
// CHECK3-NEXT:    br i1 [[TMP0]], label [[DOTWORKER:%.*]], label [[DOTMASTERCHECK:%.*]]
// CHECK3:       .worker:
// CHECK3-NEXT:    call void @{{__omp_offloading_[0-9a-z]+_[0-9a-z]+}}_main_l23_worker() #[[ATTR4:[0-9]+]]
// CHECK3-NEXT:    br label [[DOTEXIT:%.*]]
// CHECK3:       .mastercheck:
// CHECK3-NEXT:    [[NVPTX_TID1:%.*]] = call i32 @llvm.nvvm.read.ptx.sreg.tid.x()
// CHECK3-NEXT:    [[NVPTX_NUM_THREADS2:%.*]] = call i32 @llvm.nvvm.read.ptx.sreg.ntid.x()
// CHECK3-NEXT:    [[NVPTX_WARP_SIZE3:%.*]] = call i32 @llvm.nvvm.read.ptx.sreg.warpsize()
// CHECK3-NEXT:    [[TMP1:%.*]] = sub nuw i32 [[NVPTX_WARP_SIZE3]], 1
// CHECK3-NEXT:    [[TMP2:%.*]] = sub nuw i32 [[NVPTX_NUM_THREADS2]], 1
// CHECK3-NEXT:    [[TMP3:%.*]] = xor i32 [[TMP1]], -1
// CHECK3-NEXT:    [[MASTER_TID:%.*]] = and i32 [[TMP2]], [[TMP3]]
// CHECK3-NEXT:    [[TMP4:%.*]] = icmp eq i32 [[NVPTX_TID1]], [[MASTER_TID]]
// CHECK3-NEXT:    br i1 [[TMP4]], label [[DOTMASTER:%.*]], label [[DOTEXIT]]
// CHECK3:       .master:
// CHECK3-NEXT:    [[NVPTX_NUM_THREADS4:%.*]] = call i32 @llvm.nvvm.read.ptx.sreg.ntid.x()
// CHECK3-NEXT:    [[NVPTX_WARP_SIZE5:%.*]] = call i32 @llvm.nvvm.read.ptx.sreg.warpsize()
// CHECK3-NEXT:    [[THREAD_LIMIT6:%.*]] = sub nuw i32 [[NVPTX_NUM_THREADS4]], [[NVPTX_WARP_SIZE5]]
// CHECK3-NEXT:    call void @__kmpc_kernel_init(i32 [[THREAD_LIMIT6]], i16 1)
// CHECK3-NEXT:    call void @__kmpc_data_sharing_init_stack()
// CHECK3-NEXT:    call void @_Z3usev() #[[ATTR7]]
// CHECK3-NEXT:    br label [[DOTTERMINATION_NOTIFIER:%.*]]
// CHECK3:       .termination.notifier:
// CHECK3-NEXT:    call void @__kmpc_kernel_deinit(i16 1)
// CHECK3-NEXT:    call void @__kmpc_barrier_simple_spmd(%struct.ident_t* null, i32 0)
// CHECK3-NEXT:    br label [[DOTEXIT]]
// CHECK3:       .exit:
// CHECK3-NEXT:    ret void
//
