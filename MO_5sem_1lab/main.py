from math import fabs


def f(x) -> float:
    return 2 * x * x + (16 / x)
    # return x * x * x - x + 1


def uniform_search(a, b, eps):
    mini = f(a)
    mini_x = x = a

    while x <= b:
        if f(x) < mini:
            mini = f(x)
            mini_x = x
        x += eps
    print(mini)
    return mini_x


def dihotomia(a, b, eps):
    e = 0.2 * eps
    y = (a + b - e)/2
    z = (a + b + e)/2

    if fabs(b - a) <= eps:
        print(f((a + b) / 2.0))
        return (a + b) / 2.0

    if f(y) <= f(z):
        return dihotomia(a, z, eps)
    else:
        return dihotomia(y, b, eps)


def main():
    a = 1
    b = 5
    eps = 0.0001
    print("Uniform search: ")
    print("%.9f" % uniform_search(a, b, eps))
    print("")
    print("Dihotomia: ")
    print("%.9f" % dihotomia(a, b, eps))


if __name__ == "__main__":
    main()
