import turtle


def create_l_system(l_instructions, l_axiom, l_rules):
    start_string = l_axiom
    if l_instructions == 0:
        return l_axiom
    end_string = ""
    for _ in range(l_instructions):
        end_string = "".join(l_rules[i] if i in l_rules else i for i in start_string)
        start_string = end_string

    return end_string


def draw_l_system(t, l_instructions, l_angle, distance):
    for cmd in l_instructions:
        if cmd == 'F':
            t.forward(distance)
        elif cmd == 'S':
            t.up()
            t.forward(distance)
            t.down()
        elif cmd == '+':
            t.right(l_angle)
        elif cmd == '-':
            t.left(l_angle)
        elif cmd == '[':
            angle_, pos_ = t.heading(), t.pos()
            stack.append((angle_, pos_))
        elif cmd == ']':
            angle_, pos_ = stack.pop()
            t.setheading(angle_)
            t.up()
            t.goto(pos_)
            t.down()


def start(l_iterations, l_axiom, l_rules, l_angle, length, size, y_offset,
          x_offset, offset_angle, width=1600, height=900):

    inst = create_l_system(l_iterations, l_axiom, l_rules)

    t = turtle.Turtle()
    wn = turtle.Screen()
    wn.setup(width, height)
    wn.screensize(3*width, 3*height)
    wn.bgcolor('black')

    t.up()
    t.color('orange')
    t.speed(0)
    t.backward(-x_offset)
    t.left(90)
    t.backward(-y_offset)
    t.left(offset_angle)
    t.down()
    t.pensize(size)
    turtle.tracer(0, 0)
    draw_l_system(t, inst, l_angle, length)
    t.hideturtle()
    turtle.update()

    wn.exitonclick()


axiom = "F"
rules = {"F": "F[+F]F[-F]F"}
iterations = 4  # TOP: 16
angle = 25.7

s_length = 10
s_size = 1
s_angle = 0
y = -900 // 2 + 20
x = 0

stack = []

start(iterations, axiom, rules, angle, s_length, s_size, y, x, s_angle)
