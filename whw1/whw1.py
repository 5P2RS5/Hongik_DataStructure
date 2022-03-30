def memoize(f):
    memo = {}

    def helper(x):
        if x not in memo:
            memo[x] = f(x)
        return memo[x]
    return helper


def fib(n):
    if n == 0 or n == 1:
        return 1
    else:
        result = 0
        k = 0
        while k < n:
            result += fib(n-1-k) * fib(k)
            k+=1
        return result


fib = memoize(fib)

for i in range(0, 101):
    print("{} : {}".format(i, fib(i)))
