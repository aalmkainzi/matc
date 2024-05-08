#include <stdbool.h>

#define PARENS ()

#define EXPAND(...)  EXPAND4(EXPAND4(EXPAND4(EXPAND4(__VA_ARGS__))))
#define EXPAND4(...) EXPAND3(EXPAND3(EXPAND3(EXPAND3(__VA_ARGS__))))
#define EXPAND3(...) EXPAND2(EXPAND2(EXPAND2(EXPAND2(__VA_ARGS__))))
#define EXPAND2(...) EXPAND1(EXPAND1(EXPAND1(EXPAND1(__VA_ARGS__))))
#define EXPAND1(...) __VA_ARGS__

#define FOR_EACH(macro, ...)                                    \
  __VA_OPT__(EXPAND(FOR_EACH_HELPER(macro, __VA_ARGS__)))
#define FOR_EACH_HELPER(macro, a1, ...)                         \
  macro(a1)                                                     \
  __VA_OPT__(FOR_EACH_AGAIN PARENS (macro, __VA_ARGS__))
#define FOR_EACH_AGAIN() FOR_EACH_HELPER

#define ARG_1(a, ...)    a
#define ARG_2(a, b, ...) b
#define ARG_NO_1(a, ...) __VA_ARGS__

#define expand_case(cond_block) expand_case_ cond_block
#define expand_case_(cond, ...) \
else if(cond) \
{ \
    __VA_ARGS__; \
}

#define expand_first_case(cond_block) expand_first_case_ cond_block
#define expand_first_case_(cond, ...) \
if(cond) \
{ \
    __VA_ARGS__; \
}

#define expand_remaining_cases(...) \
FOR_EACH(expand_case, ARG_NO_1(__VA_ARGS__))

#define exp_expand_case(cond_block) exp_expand_case_ cond_block
#define exp_expand_case_(cond, ...) \
else if(cond) \
{ \
    ret = __VA_ARGS__; \
}

#define exp_expand_first_case(cond_block) exp_expand_first_case_ cond_block
#define exp_expand_first_case_(cond, ...) \
if(cond) \
{ \
    ret = __VA_ARGS__; \
}

#define exp_expand_remaining_cases(...) \
FOR_EACH(exp_expand_case, ARG_NO_1(__VA_ARGS__))

#define match(var, ...) \
do { \
    const typeof((0,var)) PAT = var; \
    expand_first_case(ARG_1(__VA_ARGS__)) \
    expand_remaining_cases(__VA_ARGS__) \
} while(0)

#define match_exp(var, ...) \
({ \
    const typeof((0,var)) PAT = var; \
    typeof( EXPAND1(ARG_2 ARG_1(__VA_ARGS__)) ) ret; \
    exp_expand_first_case(ARG_1(__VA_ARGS__)) \
    exp_expand_remaining_cases(__VA_ARGS__) \
    ret; \
})

#define in_range(a, b)  (PAT >= (a) && PAT <= (b))
#define gt(a)           (PAT > (a))
#define gte(a)          (PAT >= (a))
#define lt(a)           (PAT < (a))
#define lte(a)          (PAT <= (a))
#define equal(a)        (PAT == (a))
#define divisible_by(a) (PAT % (a) == 0)
