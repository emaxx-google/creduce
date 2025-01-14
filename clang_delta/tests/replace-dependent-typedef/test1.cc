// RUN: %clang_delta --transformation=replace-dependent-typedef --counter=1 %s 2>&1 | %remove_lit_checks | FileCheck %s --check-prefix=CHECK-1
// RUN: %clang_delta --transformation=replace-dependent-typedef --counter=2 %s 2>&1 | %remove_lit_checks | FileCheck %s --check-prefix=CHECK-2
// RUN: %clang_delta --transformation=replace-dependent-typedef --counter=3 %s 2>&1 | %remove_lit_checks | FileCheck %s --check-prefix=CHECK-3

typedef long xx_t;
// CHECK-1: typedef long xx;
typedef xx_t xx;

template <class T> struct S { typedef T type; };
struct A { };
// CHECK-2: struct B { typedef A type; };
struct B { typedef S<A>::type type; };

template <typename T>
struct C {
  typedef int Inner;
  // CHECK-3: typedef int Bar;
  typedef C::Inner Bar;
};
