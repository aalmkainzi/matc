# matc

Basic pattern matching in C

```C
int x = 3;

match(x,
    (gt(20),  printf("GT 20!")),
    (lte(50), printf("LTE 50")),
    (true,    printf("NEITHER")),
);
```

```C
int y =
match_exp(x,
      (in_range(5,10), 7),
      (gt(5),          5),
      (PAT < 20,       4),
      (true,           1),
);
```
By default offers the following pattern macros:
```C
#define in_range(a, b)
#define gt(a)
#define gte(a)
#define lt(a)
#define lte(a)
#define equal(a)
#define divisible_by(a)
```
You can add your own pattern expression by using `PAT` like in the second example  
