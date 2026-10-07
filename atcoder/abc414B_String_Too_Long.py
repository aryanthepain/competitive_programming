n = int(input())
parts = []
sum_len = 0

for _ in range(n):
    a_l = input().split()
    a = a_l[0]
    l = int(a_l[1])

    sum_len += l
    if sum_len > 100:
        print("Too Long")
        exit()

    parts.append(a * l)

print(''.join(parts))
