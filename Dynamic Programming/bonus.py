import time
import sys
sys.setrecursionlimit(2147483647)


def fib_recursive(n):

    if(n <= 2):
        return n
    else:
        return fib_recursive(n-1) + fib_recursive(n-2)

def fib_memoized(n, memo=None):
    if memo is None:
        memo = [None] * (n+1)
    if(n <= 2):
        return n
    if memo[n] is not None:
        return memo[n]
    else: 
        memo[n] = fib_memoized(n-1, memo) + fib_memoized(n-2, memo)
        return memo[n]

def fib_bottom_up(n):
    if n <= 2:
        return n
    
    a, b = 1, 2 
    for _ in range(3, n + 1):
        a, b = b, a + b
    return b

print("Recursive: ")
start = time.perf_counter()
fib_recursive(50)
end = time.perf_counter()
print(f"Time to compute:{(end - start)}")


print("Iterative: ")
start = time.perf_counter()
fib_bottom_up(11_000_000)
end = time.perf_counter()
print(f"Time to compute:{(end - start)}")


print("Memoized:")
start = time.perf_counter()
fib_memoized(700_000)
end = time.perf_counter()
print(f"Time to compute:{(end - start)}")