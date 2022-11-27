from math import fabs


def f(x) -> float:
    return 2 * x * x + (16 / x)
    # return x * x * x - x + 1


def f1(x) -> float:
    return 4*x-16/(x*x)


def f2(x) -> float:
    return 32/(x**2) + 4


def newton(a, b, eps):
    x = (a + b)/2
    while True:
        x = x - (f1(x)/f2(x))
        if fabs(f1(x)) <= eps:
            break
    print(f(x))
    return x


def midpoint(a, b, eps) -> float:
    z = (a + b) / 2

    if fabs(f1(z)) <= eps:
        print(f(z))
        return z

    if f1(z) < 0:
        return midpoint(z, b, eps)
    elif f1(z) > 0:
        return midpoint(a, z, eps)
    else:
        print(f(z))
        return z


def main():
    a = 1
    b = 5
    eps = 0.0001
    print("Newton: ")
    print("%.9f" % newton(a, b, eps))
    print("")
    print("Midpoint: ")
    print("%.9f" % midpoint(a, b, eps))


if __name__ == "__main__":
    main()
