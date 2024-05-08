#include <stdbool.h>

#define MATC_PARENS ()

#define MATC_EXPAND(...)  MATC_EXPAND4(MATC_EXPAND4(MATC_EXPAND4(MATC_EXPAND4(__VA_ARGS__))))
#define MATC_EXPAND4(...) MATC_EXPAND3(MATC_EXPAND3(MATC_EXPAND3(MATC_EXPAND3(__VA_ARGS__))))
#define MATC_EXPAND3(...) MATC_EXPAND2(MATC_EXPAND2(MATC_EXPAND2(MATC_EXPAND2(__VA_ARGS__))))
#define MATC_EXPAND2(...) MATC_EXPAND1(MATC_EXPAND1(MATC_EXPAND1(MATC_EXPAND1(__VA_ARGS__))))
#define MATC_EXPAND1(...) __VA_ARGS__

#define MATC_FOR_EACH(macro, ...)                                    \
  __VA_OPT__(MATC_EXPAND(MATC_FOR_EACH_HELPER(macro, __VA_ARGS__)))
#define MATC_FOR_EACH_HELPER(macro, a1, ...)                         \
  macro(a1)                                                     \
  __VA_OPT__(MATC_FOR_EACH_AGAIN MATC_PARENS (macro, __VA_ARGS__))
#define MATC_FOR_EACH_AGAIN() MATC_FOR_EACH_HELPER

#define MATC_ARG_1(a, ...)    a
#define MATC_ARG_2(a, b, ...) b
#define MATC_ARG_NO_1(a, ...) __VA_ARGS__

#define MATC_expand_case(cond_block) MATC_expand_case_ cond_block
#define MATC_expand_case_(cond, ...) \
else if(cond) \
{ \
    __VA_ARGS__; \
}

#define MATC_expand_first_case(cond_block) MATC_expand_first_case_ cond_block
#define MATC_expand_first_case_(cond, ...) \
if(cond) \
{ \
    __VA_ARGS__; \
}

#define MATC_expand_remaining_cases(...) \
MATC_FOR_EACH(MATC_expand_case, MATC_ARG_NO_1(__VA_ARGS__))

#define MATC_exp_expand_case(cond_block) MATC_exp_expand_case_ cond_block
#define MATC_exp_expand_case_(cond, ...) \
else if(cond) \
{ \
    ret = __VA_ARGS__; \
}

#define MATC_exp_expand_first_case(cond_block) MATC_exp_expand_first_case_ cond_block
#define MATC_exp_expand_first_case_(cond, ...) \
if(cond) \
{ \
    ret = __VA_ARGS__; \
}

#define MATC_exp_expand_remaining_cases(...) \
MATC_FOR_EACH(MATC_exp_expand_case, MATC_ARG_NO_1(__VA_ARGS__))

#define match(var, ...) \
do { \
    const typeof((0,var)) PAT = var; \
    MATC_expand_first_case(MATC_ARG_1(__VA_ARGS__)) \
    MATC_expand_remaining_cases(__VA_ARGS__) \
} while(0)

#define match_exp(var, ...) \
({ \
    const typeof((0,var)) PAT = var; \
    typeof( MATC_EXPAND1(MATC_ARG_2 MATC_ARG_1(__VA_ARGS__)) ) ret; \
    MATC_exp_expand_first_case(MATC_ARG_1(__VA_ARGS__)) \
    MATC_exp_expand_remaining_cases(__VA_ARGS__) \
    ret; \
})

#define in_range(a, b)  (PAT >= (a) && PAT <= (b))
#define gt(a)           (PAT > (a))
#define gte(a)          (PAT >= (a))
#define lt(a)           (PAT < (a))
#define lte(a)          (PAT <= (a))
#define equal(a)        (PAT == (a))
#define divisible_by(a) (PAT % (a) == 0)
