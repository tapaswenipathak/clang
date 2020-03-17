// RUN: %clang_cc1 -emit-llvm %s -o - | FileCheck %s

// CHECK: @tentative_attr_first = global i32 undef, align 4
int tentative_attr_first __attribute__((loader_uninitialized));
int tentative_attr_first;

// CHECK: @tentative_attr_second = global i32 undef, align 4
int tentative_attr_second;
int tentative_attr_second __attribute__((loader_uninitialized));

// CHECK: @array = global [16 x float] undef, align 16
float array[16] __attribute__((loader_uninitialized));

typedef struct
{
  int x;
  float y;
} s;

// CHECK: @i = global %struct.s undef, align 4
s i __attribute__((loader_uninitialized));

// CHECK: @private_extern_ok = hidden global i32 undef, align 4
__private_extern__ int private_extern_ok __attribute__((loader_uninitialized));
