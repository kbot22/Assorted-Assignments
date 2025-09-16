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

# test algorithms
data = []
with open('input_fib.txt', 'r') as file:
    for line in file:
        row = [int(x.strip()) for x in line.split(',') if x.strip()]
        data.append(row)


results = []

for i in range(0, len(data[0])):
    n = len(data[0]) - 1

    
    print("Iterative: ")
    start = time.perf_counter()
    print(fib_bottom_up(data[0][i]))
    end = time.perf_counter()
    results.append(end - start)

    print("Recursive: ")
    start = time.perf_counter()
    print(fib_recursive(data[0][i]))
    end = time.perf_counter()
    results.append(end - start)

    print("Memoized:")
    start = time.perf_counter()
    print(fib_memoized(data[0][i]))
    end = time.perf_counter()
    results.append(end - start)

# print results

print("Final Results:")
for i in range(0, len(results), 3):
    
    print(f"Iterative: {results[i]}")

    print(f"Recursive: {results[i+1]}")

    print(f"Memoized: {results[i+2]}")