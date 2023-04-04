class Bar:
    def __init__(self, a):
        self.a = a

class Foo:
    def __init__(self, x):
        self.x = x
        self.y = None
    
    def setY(self, b):
        self.y = b

def foo(N, M):
    foo = [None] * N # ????
    outer = None

    i = 1
    while i <= N:
        o1 = Foo(i)
        if i % 3 == 0:
            foo[i % M - 1] = o1

        o2 = Bar(i)
        if i % 5 == 0:
            o1.setY(o2)
        outer = o1

        i += 1

def main():
    N = 4000000
    M = 1000
    foo(N, M)

main()
