// NOTE: Assertions have been autogenerated by utils/update_cc_test_checks.py UTC_ARGS: --function-signature --include-generated-funcs --replace-value-regex "__omp_offloading_[0-9a-z]+_[0-9a-z]+" "reduction_size[.].+[.]" "pl_cond[.].+[.|,]" --prefix-filecheck-ir-name _
// RUN: %clang_cc1 -verify -fopenmp -x c++ -triple powerpc64le-unknown-unknown -fopenmp-targets=nvptx64-nvidia-cuda -emit-llvm-bc %s -o %t-ppc-host.bc
// RUN: %clang_cc1 -verify -fopenmp -x c++ -triple nvptx64-nvidia-cuda -fopenmp-targets=nvptx64-nvidia-cuda -emit-llvm %s -fopenmp-is-device -fopenmp-host-ir-file-path %t-ppc-host.bc -o - -disable-llvm-optzns | FileCheck %s --check-prefix=CHECK1
// expected-no-diagnostics

int foo(int &a) { return a; }

int bar() {
  int a;
  return foo(a);
}


int maini1() {
  int a;
#pragma omp target parallel map(from:a)
  {
    int b;
    a = foo(b) + bar();
  }
  return a;
}

// parallel region


// CHECK1-LABEL: define {{[^@]+}}@{{__omp_offloading_[0-9a-z]+_[0-9a-z]+}}__Z6maini1v_l16
// CHECK1-SAME: (i32* nonnull align 4 dereferenceable(4) [[A:%.*]]) #[[ATTR0:[0-9]+]] {
// CHECK1-NEXT:  entry:
// CHECK1-NEXT:    [[A_ADDR:%.*]] = alloca i32*, align 8
// CHECK1-NEXT:    [[OMP_OUTLINED_ARG_AGG_:%.*]] = alloca [[STRUCT_ANON:%.*]], align 8
// CHECK1-NEXT:    [[CAPTURED_VARS_ADDRS:%.*]] = alloca [1 x i8*], align 8
// CHECK1-NEXT:    store i32* [[A]], i32** [[A_ADDR]], align 8
// CHECK1-NEXT:    [[TMP0:%.*]] = load i32*, i32** [[A_ADDR]], align 8
// CHECK1-NEXT:    [[TMP1:%.*]] = call i32 @__kmpc_target_init(%struct.ident_t* @[[GLOB1:[0-9]+]], i1 true, i1 false, i1 true)
// CHECK1-NEXT:    [[EXEC_USER_CODE:%.*]] = icmp eq i32 [[TMP1]], -1
// CHECK1-NEXT:    br i1 [[EXEC_USER_CODE]], label [[USER_CODE_ENTRY:%.*]], label [[WORKER_EXIT:%.*]]
// CHECK1:       user_code.entry:
// CHECK1-NEXT:    [[TMP2:%.*]] = call i32 @__kmpc_global_thread_num(%struct.ident_t* @[[GLOB2:[0-9]+]])
// CHECK1-NEXT:    [[TMP3:%.*]] = getelementptr inbounds [[STRUCT_ANON]], %struct.anon* [[OMP_OUTLINED_ARG_AGG_]], i32 0, i32 0
// CHECK1-NEXT:    store i32* [[TMP0]], i32** [[TMP3]], align 8
// CHECK1-NEXT:    [[TMP4:%.*]] = getelementptr inbounds [1 x i8*], [1 x i8*]* [[CAPTURED_VARS_ADDRS]], i64 0, i64 0
// CHECK1-NEXT:    [[TMP5:%.*]] = call i8* @__kmpc_alloc_shared(i64 8)
// CHECK1-NEXT:    [[TMP6:%.*]] = load [[STRUCT_ANON]], %struct.anon* [[OMP_OUTLINED_ARG_AGG_]], align 8
// CHECK1-NEXT:    [[TMP7:%.*]] = bitcast i8* [[TMP5]] to %struct.anon*
// CHECK1-NEXT:    store [[STRUCT_ANON]] [[TMP6]], %struct.anon* [[TMP7]], align 8
// CHECK1-NEXT:    store i8* [[TMP5]], i8** [[TMP4]], align 8
// CHECK1-NEXT:    [[TMP8:%.*]] = bitcast [1 x i8*]* [[CAPTURED_VARS_ADDRS]] to i8**
// CHECK1-NEXT:    call void @__kmpc_parallel_51(%struct.ident_t* @[[GLOB2]], i32 [[TMP2]], i32 1, i32 -1, i32 -1, i8* bitcast (void (i32*, i32*, %struct.anon*)* @__omp_outlined__ to i8*), i8* null, i8** [[TMP8]], i64 1)
// CHECK1-NEXT:    call void @__kmpc_free_shared(i8* [[TMP5]])
// CHECK1-NEXT:    call void @__kmpc_target_deinit(%struct.ident_t* @[[GLOB1]], i1 true, i1 true)
// CHECK1-NEXT:    ret void
// CHECK1:       worker.exit:
// CHECK1-NEXT:    ret void
//
//
// CHECK1-LABEL: define {{[^@]+}}@__omp_outlined__
// CHECK1-SAME: (i32* noalias [[DOTGLOBAL_TID_:%.*]], i32* noalias [[DOTBOUND_TID_:%.*]], %struct.anon* noalias [[__CONTEXT:%.*]]) #[[ATTR0]] {
// CHECK1-NEXT:  entry:
// CHECK1-NEXT:    [[DOTGLOBAL_TID__ADDR:%.*]] = alloca i32*, align 8
// CHECK1-NEXT:    [[DOTBOUND_TID__ADDR:%.*]] = alloca i32*, align 8
// CHECK1-NEXT:    [[__CONTEXT_ADDR:%.*]] = alloca %struct.anon*, align 8
// CHECK1-NEXT:    [[B:%.*]] = alloca i32, align 4
// CHECK1-NEXT:    store i32* [[DOTGLOBAL_TID_]], i32** [[DOTGLOBAL_TID__ADDR]], align 8
// CHECK1-NEXT:    store i32* [[DOTBOUND_TID_]], i32** [[DOTBOUND_TID__ADDR]], align 8
// CHECK1-NEXT:    store %struct.anon* [[__CONTEXT]], %struct.anon** [[__CONTEXT_ADDR]], align 8
// CHECK1-NEXT:    [[TMP0:%.*]] = load %struct.anon*, %struct.anon** [[__CONTEXT_ADDR]], align 8
// CHECK1-NEXT:    [[TMP1:%.*]] = getelementptr inbounds [[STRUCT_ANON:%.*]], %struct.anon* [[TMP0]], i32 0, i32 0
// CHECK1-NEXT:    [[TMP2:%.*]] = load i32*, i32** [[TMP1]], align 8
// CHECK1-NEXT:    [[CALL:%.*]] = call i32 @_Z3fooRi(i32* nonnull align 4 dereferenceable(4) [[B]]) #[[ATTR3:[0-9]+]]
// CHECK1-NEXT:    [[CALL1:%.*]] = call i32 @_Z3barv() #[[ATTR3]]
// CHECK1-NEXT:    [[ADD:%.*]] = add nsw i32 [[CALL]], [[CALL1]]
// CHECK1-NEXT:    store i32 [[ADD]], i32* [[TMP2]], align 4
// CHECK1-NEXT:    ret void
//
//
// CHECK1-LABEL: define {{[^@]+}}@_Z3fooRi
// CHECK1-SAME: (i32* nonnull align 4 dereferenceable(4) [[A:%.*]]) #[[ATTR1:[0-9]+]] {
// CHECK1-NEXT:  entry:
// CHECK1-NEXT:    [[A_ADDR:%.*]] = alloca i32*, align 8
// CHECK1-NEXT:    store i32* [[A]], i32** [[A_ADDR]], align 8
// CHECK1-NEXT:    [[TMP0:%.*]] = load i32*, i32** [[A_ADDR]], align 8
// CHECK1-NEXT:    [[TMP1:%.*]] = load i32, i32* [[TMP0]], align 4
// CHECK1-NEXT:    ret i32 [[TMP1]]
//
//
// CHECK1-LABEL: define {{[^@]+}}@_Z3barv
// CHECK1-SAME: () #[[ATTR1]] {
// CHECK1-NEXT:  entry:
// CHECK1-NEXT:    [[A:%.*]] = call i8* @__kmpc_alloc_shared(i64 4)
// CHECK1-NEXT:    [[A_ON_STACK:%.*]] = bitcast i8* [[A]] to i32*
// CHECK1-NEXT:    [[CALL:%.*]] = call i32 @_Z3fooRi(i32* nonnull align 4 dereferenceable(4) [[A_ON_STACK]]) #[[ATTR3]]
// CHECK1-NEXT:    call void @__kmpc_free_shared(i8* [[A]])
// CHECK1-NEXT:    ret i32 [[CALL]]
//
