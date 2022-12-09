#ifndef CO_GCC_H_
#define CO_GCC_H_

#ifdef _lint /* Make sure no compiler comes this way */

/* Standard library headers typically define the assert macro so that it
   expands to a complicated conditional expression that uses special
   funtions that Lint does not know about by default.  For linting
   purposes, we can simplify things a bit by forcing assert() to expand to
   a call to a special function that has the appropriate 'assert'
   semantics.
 */
//lint -function( __assert, __lint_assert )
void __lint_assert( int );
//lint ++d"assert(e)=__lint_assert(e)"
//(++d makes this definition permanently immutable for the Lint run.)
//Now that we've made our own 'assert', we need to keep people from being
//punished when the marco in 'assert.h' appears not to be used:
//lint  -efile(766,*assert.h)

/*
   The headers included below must be generated; For C++, generate
   with:

   g++ [usual build options] -E -dM t.cpp >lint_cppmac.h

   For C, generate with:

   gcc [usual build options] -E -dM t.c >lint_cmac.h

   ...where "t.cpp" and "t.c" are empty source files.

   It's important to use the same compiler options used when compiling
   project code because they can affect the existence and precise
   definitions of certain predefined macros.  See gcc-readme.txt for
   details and a tutorial.
 */
#if defined(__cplusplus)
#       include "lint_cppmac.h"
#else
#       include "lint_cmac.h"
#endif

#define GCC_VERSION ( __GNUC__     * 10000 +       \
                      __GNUC_MINOR__ * 100 +       \
                      __GNUC_PATCHLEVEL__ )

/* If the macro set given by the generated macro files must be adjusted in
   order for Lint to cope, then you can make those adjustments here.
 */

/* The following is a workaround for versions of GCC with bug 25717, in
   which the preprocessor does not dump a #define directive for __STDC__
   when -dM is given:
   http://gcc.gnu.org/bugzilla/show_bug.cgi?id=25717

   We know the unconditional definition of __STDC__ was introduced no
   later than version 3.0; the preprocessor bug was fixed no later than
   version 4.1.0.
 */
#if GCC_VERSION >= 30000 && GCC_VERSION < 40100
#        define __STDC__ 1
#endif


#endif /* _lint      */
#endif /* CO_GCC_H_ */
