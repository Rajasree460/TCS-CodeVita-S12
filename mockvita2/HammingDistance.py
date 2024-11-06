def min_cost_hamming_distance(s, A, B):
    if not all(c in '01' for c in s):
        return "INVALID"

    cost = 0
    for i in range(len(s) - 1):
        if s[i] != s[i+1]:
            cost += A if s[i] == '0' else B

    # Rearrange the string
    new_s = ''.join(sorted(s))

    # Calculate Hamming distance
    hamming_distance = sum(1 for i in range(len(s)) if s[i] != new_s[i])

    return hamming_distance

# Main function to handle multiple test cases
def main():
    T = int(input())  # Number of test cases
    for _ in range(T):
        s = input()  # Binary string
        A, B = map(int, input().split())  # Costs A and B
        result = min_cost_hamming_distance(s, A, B)
        print(result)

# Corrected check for script execution
if __name__ == "__main__":
    main()
