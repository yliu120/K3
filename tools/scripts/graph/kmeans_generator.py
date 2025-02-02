import random

D = 32
K = 5
N = 270 * 1000000

means = [[j * 10 for i in range(D)] for j in range(-2, 3)]

for i in range(N):
    mean = random.choice(means)
    point = [random.gauss(c, 2.5) for c in mean]

    print(','.join("{:0.8f}".format(i) for i in point))
