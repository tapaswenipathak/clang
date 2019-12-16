// RUN: %clang_cc1 -emit-llvm -o - %s | FileCheck %s

// test to ensure that these builtins don't do the variadic promotion of float->double.
void test_floats(float f1, float f2) {
  (void)__builtin_isgreater(f1, f2);
  // CHECK: fcmp ogt float
  // CHECK-NEXT: zext i1
  (void)__builtin_isgreaterequal(f1, f2);
  // CHECK: fcmp oge float
  // CHECK-NEXT: zext i1
  (void)__builtin_isless(f1, f2);
  // CHECK: fcmp olt float
  // CHECK-NEXT: zext i1
  (void)__builtin_islessequal(f1, f2);
  // CHECK: fcmp ole float
  // CHECK-NEXT: zext i1
  (void)__builtin_islessgreater(f1, f2);
  // CHECK: fcmp one float
  // CHECK-NEXT: zext i1
  (void)__builtin_isunordered(f1, f2);
  // CHECK: fcmp uno float
  // CHECK-NEXT: zext i1
}

void test_doubles(double d1, double f2) {
  (void)__builtin_isgreater(d1, f2);
  // CHECK: fcmp ogt double
  // CHECK-NEXT: zext i1
  (void)__builtin_isgreaterequal(d1, f2);
  // CHECK: fcmp oge double
  // CHECK-NEXT: zext i1
  (void)__builtin_isless(d1, f2);
  // CHECK: fcmp olt double
  // CHECK-NEXT: zext i1
  (void)__builtin_islessequal(d1, f2);
  // CHECK: fcmp ole double
  // CHECK-NEXT: zext i1
  (void)__builtin_islessgreater(d1, f2);
  // CHECK: fcmp one double
  // CHECK-NEXT: zext i1
  (void)__builtin_isunordered(d1, f2);
  // CHECK: fcmp uno double
  // CHECK-NEXT: zext i1
}

void test_mixed(double d1, float f2) {
  (void)__builtin_isgreater(d1, f2);
  // CHECK: fpext float {{.*}} to double
  // CHECK-NEXT: fcmp ogt double
  // CHECK-NEXT: zext i1
  (void)__builtin_isgreaterequal(d1, f2);
  // CHECK: fpext float {{.*}} to double
  // CHECK-NEXT: fcmp oge double
  // CHECK-NEXT: zext i1
  (void)__builtin_isless(d1, f2);
  // CHECK: fpext float {{.*}} to double
  // CHECK-NEXT: fcmp olt double
  // CHECK-NEXT: zext i1
  (void)__builtin_islessequal(d1, f2);
  // CHECK: fpext float {{.*}} to double
  // CHECK-NEXT: fcmp ole double
  // CHECK-NEXT: zext i1
  (void)__builtin_islessgreater(d1, f2);
  // CHECK: fpext float {{.*}} to double
  // CHECK-NEXT: fcmp one double
  // CHECK-NEXT: zext i1
  (void)__builtin_isunordered(d1, f2);
  // CHECK: fpext float {{.*}} to double
  // CHECK-NEXT: fcmp uno double
  // CHECK-NEXT: zext i1
}
