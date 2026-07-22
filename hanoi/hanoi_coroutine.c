#include <stdio.h>
#include <stdlib.h>
#include "c-coroutine.h"

typedef struct
{
    int from;   /* 1-3, 0 if done */
    int to;     /* 1-3, 0 if done */
} Move_t;

Move_t no_more_moves_marker = { 0, 0 };

Move_t
hanoi_coroutine(c_coroutine_context_t *context, int towerSize, int from, int to)
{
    Move_t move;

    C_COROUTINE_CONTEXT_DEFINE();
    c_coroutine_context_t subcontext;
    int i;
    int other;
    C_COROUTINE_BEGIN_WITH_NAMED_CONTEXT(context,state);

    state->subcontext = 0;
    state->other = 6 - (from + to);

    if (towerSize > 1)
    {
        while (1)
        {
            move = hanoi_coroutine(&(state->subcontext),
                                   towerSize-1,from,state->other);
            if (!move.from)
            {
                break;
            }
            C_COROUTINE_YIELD(move);
        }
    }

    move.from = from;
    move.to = to;
    C_COROUTINE_YIELD(move);

    if (towerSize > 1)
    {
        while (1)
        {
            move = hanoi_coroutine(&(state->subcontext),
                                   towerSize-1,state->other,to);
            if (!move.from)
            {
                break;
            }
            C_COROUTINE_YIELD(move);
        }
    }

    C_COROUTINE_END_AND_RESTART(context);

    return no_more_moves_marker;
}

int
main(int argc, char *argv[])
{
    c_coroutine_context_t context = 0;
    Move_t move;
    int	towerSize = 0;

    if (argc > 1)
    {
	towerSize = atoi(argv[1]);
    }

    if (towerSize < 1)
    {
	towerSize = 5;
    }

    while (1)
    {
        move = hanoi_coroutine(&context,towerSize,1,3);

        if (!move.from)
        {
            break;
        }

        printf("%d %d\n",move.from,move.to);
    }

    return 0;
}

