// RUN: %clang_delta --query-instances=replace-dependent-typedef %s 2>&1 | %remove_lit_checks | FileCheck %s --check-prefix=CHECK-CNT
// RUN: %clang_delta --transformation=replace-dependent-typedef --counter=1 %s 2>&1 | %remove_lit_checks | FileCheck %s --check-prefix=CHECK-1

template <typename T>
struct A {
  struct Inner;
  // This shouldn't be treated as an instance:
  typedef A::Inner Foo;
};

template <class T> struct S { typedef T type; };

struct B {
  struct Inner;
};

template <typename T>
struct C {
  typedef typename S<T>::type::Inner Bar;
};

// CHECK-1: typedef B::Inner D;
typedef C<B>::Bar D;

// CHECK-CNT: Available transformation instances: 1
