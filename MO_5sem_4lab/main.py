import numpy


def fx(x) -> float:
    return x[0] ** 3 + x[1] ** 3 - 3 * x[0] * x[1]


def dfx(x) -> float:
    return 3 * (x[0] ** 2) - 3 * x[1]


def dfy(x) -> float:
    return - 3 * x[0] + 3 * (x[1] ** 2)


def f(x, xy) -> float:
    return fx(x=[
        xy[0] - x * dfx(xy),
        xy[1] - x * dfy(xy)
    ])


def uniform_search(a, b, xy, eps):
    mini = f(a, xy)
    mini_x = x = a

    while x <= b:
        if f(x, xy) < mini:
            mini = f(x, xy)
            mini_x = x
        x += eps
    print(mini_x)
    return mini_x


def koshy(x: list, eps):
    k = 0
    x_now = x.copy()
    while True:
        x = x_now.copy()
        dx = - dfx(x)
        dy = - dfy(x)
        lam = uniform_search(0, 1, x, eps)
        x_now = [x[0] + lam * dx,
                 x[1] + lam * dy]

        if (numpy.linalg.norm([x_now[0] - x[0], x_now[1] - x[1]], ord=2) <= eps) and \
                (numpy.linalg.norm([dfx(x_now), dfy(x_now)], ord=2) <= eps):
            print("Za {0} iteraciy\n".format(k))
            return x_now

        k += 1


def main():
    x0 = [1.5, 0.7]
    eps = 0.0001
    kosh = koshy(x0, eps)
    print(f'f({kosh[0]}, {kosh[1]}) = {fx(kosh)}')


if __name__ == "__main__":
    main()
