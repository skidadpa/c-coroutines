#!/usr/bin/env python3

# This is a Tower of Hanoi solution generator. It generates output lines of
# 2 numbers, each representing a move from the top of one stack to the top
# of another.
#
# There are always 3 stacks, numbered 1-3. Initially, all disks are in order
# from largest to smallest in stack 1, they must end in the same order in
# stack 3 without ever putting a larger disk on top of a smaller one. The
# input argument, if specified, indicates the height of the full stack. If
# not specified, the default stack height is 5.

def hanoi(towerSize,fro,to):
    other = 6 - (to + fro)
    if towerSize > 1:
        for d in hanoi(towerSize - 1, fro, other):
            yield d
    yield (fro,to)
    if towerSize > 1:
        for d in hanoi(towerSize - 1, other, to):
            yield d

def hanoi2(towerSize,fro,to):
    if towerSize:
        other = 6 - (to + fro)
        for d in hanoi(towerSize - 1, fro, other):
            yield d
        yield (fro,to)
        for d in hanoi(towerSize - 1, other, to):
            yield d

if __name__ == "__main__":
    from sys import argv

    if len(argv) > 1:
        stackSize = int(argv[1])
    else:
        stackSize = 5

    for i in hanoi2(stackSize,1,3):
        print("%d %d" % i)
