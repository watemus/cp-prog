import math

n = int(input())

a = []

for i in range(n):
	x, y = map(int, input().split())
	a.append((x, y))

def dist(a, b):
	return math.sqrt((a[0] - b[0]) ** 2 + (a[1] - b[1]) ** 2)

def ternary_y(x):
	global a
	l = -1001
	r = 1001
	ans = 1000000000
	for iters in range(50):
		y1 = l + (r - l) / 3
		y2 = l + (r - l) / 3 * 2
		cans1 = 0
		cans2 = 0
		for xx, yy in a:
			cans1 += dist((xx, yy), (x, y1))
			cans2 += dist((xx, yy), (x, y2))
		if cans1 < cans2:
			r = y2
		else:
			l = y1
		ans = min(ans, cans1, cans2)
	return (l, ans)


def ternary_x():
	global a
	l = -1001
	r = 1001
	ans = 10000000000
	for iters in range(50):
		x1 = l + (r - l) / 3
		x2 = l + (r - l) / 3 * 2
		cans1 = ternary_y(x1)
		cans2 = ternary_y(x2)
		if cans1[1] < cans2[1]:
			r = x2
		else:
			l = x1
		ans = min(ans, cans1[1], cans2[1])
	return (l, ternary_y(l)[0], ans)

x, y, r = ternary_x()
print("{:.7f} {:.7f}".format(x, y))
print("{:.7f}".format(r))
