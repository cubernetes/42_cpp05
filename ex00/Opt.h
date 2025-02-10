#pragma once /* Opt.h */

#ifndef COMPILING_FOR_CPP23
#ifdef COMPILING_FOR_CPP98
#if COMPILING_FOR_CPP98
#define COMPILING_FOR_CPP23 0
#else
#define COMPILING_FOR_CPP23 1
#endif
#else
#define COMPILING_FOR_CPP23 0
#endif
#endif

#ifndef COMPILING_FOR_CPP98
#if COMPILING_FOR_CPP23
#define COMPILING_FOR_CPP98 0
#else
#define COMPILING_FOR_CPP98 1
#endif
#else
#error "COMPILING_FOR_CPP98 must not be defined manually"
#endif

// redundant check
#if COMPILING_FOR_CPP23 == COMPILING_FOR_CPP98
#error "Preprocessor constants COMPILING_FOR_CPP23 and COMPILING_FOR_CPP98 are mutually exclusive"
#endif

#define EMPTY()
#define DEFER(id) id EMPTY()
#define EXPAND(...) __VA_ARGS__
#define CPP23_1(expr) expr
#define CPP23_0(expr)
#define CPP23_(BOOL) CPP23_##BOOL

#define CPP23(expr) EXPAND(DEFER(CPP23_)(COMPILING_FOR_CPP23)(expr))

#define CPP98_1(expr) expr
#define CPP98_0(expr)
#define CPP98_(BOOL) CPP98_##BOOL

#define CPP98(expr) EXPAND(DEFER(CPP98_)(COMPILING_FOR_CPP98)(expr))
