import math
import numpy


def fx(x) -> float:
    return x[0] ** 3 + x[1] ** 3 - 3 * x[0] * x[1]


def simplex_metod(x0, eps):
    yx = 0.5
    lx = 1
    n = 2

    while True:
        pn = lx * (math.sqrt(n+1) + n - 1) / (n * math.sqrt(2))
        qn = pn - lx * math.sqrt(2) / 2

        simpl = [[x0[0] + 0,  x0[1] + 0],
                 [x0[0] + pn, x0[1] + qn],
                 [x0[0] + qn, x0[1] + pn]]

        x0 = [0, 0]
        for i in range(n + 1):
            x0[0] += simpl[i][0]
            x0[1] += simpl[i][1]
        x0[0] /= (n + 1)
        x0[1] /= (n + 1)

        minx = maxx = simpl[1]
        maxi = 1
        for i in range(1, n + 1):
            if fx(minx) >= fx(simpl[i]):
                minx = simpl[i]
            if fx(maxx) < fx(simpl[i]):
                maxx = simpl[i]
                maxi = i

        temp = [0, 0]
        xp = [0, 0]
        for i in range(n+1):
            temp[0] += simpl[i][0]
            temp[1] += simpl[i][1]
        xp[0] = (2 / n) * math.floor(temp[0] - maxx[0]) - maxx[0]
        xp[1] = (2 / n) * math.floor(temp[1] - maxx[1]) - maxx[1]

        if fx(xp) <= fx(maxx):
            lx *= 0.5
            simpl[maxi] = xp
        else:
            for i in range(n):
                simpl[i][0] = yx * simpl[i][0] + (1 - yx) * minx[0]
                simpl[i][1] = yx * simpl[i][1] + (1 - yx) * minx[1]

        temp = [0, 0]
        for i in range(n+1):
            temp[0] += simpl[i][0]
            temp[1] += simpl[i][1]
        temp[0] /= n + 1
        temp[1] /= n + 1
        x0, temp = temp, x0
        if (numpy.linalg.norm(x=[x0[0] - temp[0], x0[1] - temp[1]], ord=2) <= eps) and \
                (math.fabs(fx(x0) - fx(temp)) <= eps):
            return x0


def huck(x0, eps):
    delt: float = 1
    alif: float = 2
    vx = x0

    while True:
        xi = vx

        if fx(xi) > fx([xi[0] + delt, xi[1]]):
            vx[0] += delt

        if fx(xi) > fx([xi[0], xi[1] + delt]):
            vx[1] += delt

        if vx[0] == xi[0] and vx[1] == xi[1]:
            if fx(xi) > fx([xi[0] - delt, xi[1]]):
                vx[0] -= delt

            if fx(xi) > fx([xi[0], xi[1] - delt]):
                vx[1] -= delt

        if numpy.linalg.norm([delt, delt]) >= eps:
            delt /= alif
            continue

        xo = [0, 0]
        xo[0] = xi[0] + (xi[0] - x0[0])
        xo[1] = xi[1] + (xi[1] - x0[1])
        if fx(xo) < fx(xi):
            vx = xo
        else:
            vx = xi

        if (numpy.linalg.norm([delt, delt]) <= eps) and (math.fabs(fx(vx) - fx(x0)) <= eps):
            break

        x0 = vx

    return vx


def main():
    x0 = [1.5, 0.7]
    eps = 0.0001
    sim = simplex_metod(x0, eps)
    print(f'f({sim[0]}, {sim[1]}) = {fx(sim)}')
    huck_val = huck(x0, eps)
    print(f'f({huck_val[0]}, {huck_val[1]}) = {fx(huck_val)}')


if __name__ == "__main__":
    main()
