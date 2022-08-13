
def step(n):
    if n%2 == 0:
        return n/2
    else:
        return n*3 + 1

def get_collatz_sequence(n):
    seq = [n]

    while n != 1:
        n = step(n)
        seq.append(n)

    return seq

def get_longest_sequence(n):
    longest_seq = []

    for i in range(1, n+1):
        cur_seq = get_collatz_sequence(i)
        if len(cur_seq) > len(longest_seq):
            longest_seq = cur_seq

    return longest_seq
