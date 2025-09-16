import time

def matrix_iterative(p, n):
    # create tables m and s
    m = [[0] * (n + 1) for _ in range(n + 1)]
    s = [[0] * (n + 1) for _ in range(n + 1)]
    min_cost = float('inf')
    opt_split = None
    
    # Set diagonal elements of m to 0
    for i in range(1, n + 1):
        m[i][i] = 0
    
    # l is the chain length
    for l in range(2, n + 1):
        for i in range(1, n - l + 2):
            j = i + l - 1
            m[i][j] = float('inf')
            
            # Check all possible splits
            for k in range(i, j):
                # Calculate q (cost)
                q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j]
                
                # Update minimum cost and store the index of the split
                if q < m[i][j]:
                    m[i][j] = q
                    s[i][j] = k
                    min_cost = q
                    opt_split = k
    return (min_cost, opt_split)

def matrix_recursive(p, i, j):
    # base case (only one matrix)
    if i == j:
        return 0
    
    min_cost = float('inf')

    # check all possible splits
    for k in range(i, j):
        # calculate q (cost)
        q = matrix_recursive(p,i,k) + matrix_recursive(p,k + 1,j) + p[i - 1] * p[k] * p[j]
    
        # update cost
        if q < min_cost:
            min_cost = q
    return min_cost


def matrix_memoized(p, i, j, memo=None):
    if memo is None:
        memo = {}
    if (i, j) in memo:
        return memo[(i, j)]
    if i == j:
        return (0, None)
    else:
        min_cost = float('inf')
        opt_split = None

        for k in range(i, j):
            left = matrix_memoized(p, i, k, memo)
            right = matrix_memoized(p, k+1, j, memo)
            current = left[0] + right[0] + p[i-1] * p[k] * p[j]


            if current < min_cost:
                min_cost = current
                opt_split = k
            
        result = (min_cost, opt_split)
    memo[(i,j)] = result
    return result
        

# test algorithms
data = []
with open('input_matrix.txt', 'r') as file:
    for line in file:
        row = [int(x.strip()) for x in line.split(',') if x.strip()]
        data.append(row)


results = []

for i in range(0, len(data)):
    arr = data[i]
    n = len(arr) - 1

    
    print("Iterative: ")
    start = time.perf_counter()
    print(matrix_iterative(arr,n))
    end = time.perf_counter()
    results.append(end - start)

    print("Recursive: ")
    start = time.perf_counter()
    print(matrix_recursive(arr, 1, n))
    end = time.perf_counter()
    results.append(end - start)

    print("Memoized:")
    start = time.perf_counter()
    print(matrix_memoized(arr, 1, n, {}))
    end = time.perf_counter()
    results.append(end - start)

# print results

print("Final Results:")
for i in range(0, len(results), 3):
    print(f"Sample Set {(i/3)+1}")

    print(f"Iterative: {results[i]}")

    print(f"Recursive: {results[i+1]}")

    print(f"Memoized: {results[i+2]}")