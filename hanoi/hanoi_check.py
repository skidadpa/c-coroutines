#!/usr/bin/env python3

# Check the output of a Tower of Hanoi solution generator. Input lines are
# to contain 2 numbers, representing a move of one disk from the top of one
# stack to the top of another.
#
# If a move is legal, the resulting state of all stacks is printed. If not,
# an error is indicated. Otherwise, if all moves are processed leaving all
# disks on stack 3, success is indicated.
#
# There are always 3 stacks, numbered 1-3. Initially, all disks are in order
# from largest to smallest in stack 1, they must end in the same order in
# stack 3 without ever putting a larger disk on top of a smaller one. The
# input argument, if specified, indicates the height of the full stack. If
# not specified, the default stack height is 5 and intermediate stack state
# printing is suppressed.

def check_solution(inp,stackSize,displayStack):
    board = [ None, list(range(stackSize,0,-1)), [], [] ]
    bottomBase = stackSize+1
    if displayStack:
        print(f" {board[1:]}")

    try:
        for move in inp.readlines():
            iFrom, iTo = map(int, move.strip().split())
            board[iTo].append(board[iFrom].pop())
            for stack in board[1:]:
                topdisk = bottomBase
                for disk in stack:
                    assert disk < topdisk
                    topdisk = disk
            if displayStack:
                print(f" {board[1:]}")
    except:
        print("Illegal move attempted")
    else:
        if not board[1] and not board[2]:
            return True

    return False

if __name__ == "__main__":
    import sys

    if len(sys.argv) > 1:
        stackSize = int(sys.argv[1])
        displayStack = True
    else:
        stackSize = 5
        displayStack = False

    if check_solution(sys.stdin,stackSize,displayStack):
        print("TEST PASSED")
    else:
        print("TEST FAILED")
        sys.exit(1)
