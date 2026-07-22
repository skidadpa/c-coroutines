#include <stdio.h>
#include "c-coroutine.h"

typedef struct
{
    int from;   /* 1-3, 0 if done */
    int to;     /* 1-3, 0 if done */
} Move_t;

void
hanoi_coroutine(
    c_coroutine_context_t *context,
    int towerSize,
    int from,
    int to,
    Move_t *move)
{
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
            hanoi_coroutine(&(state->subcontext),
                            towerSize-1,from,state->other,move);
            if (!move->from)
            {
                break;
            }
            C_COROUTINE_YIELD(C_COROUTINE_YIELD_NOTHING);
        }
    }

    move->from = from;
    move->to = to;
    C_COROUTINE_YIELD(C_COROUTINE_YIELD_NOTHING);

    if (towerSize > 1)
    {
        while (1)
        {
            hanoi_coroutine(&(state->subcontext),
			    towerSize-1,state->other,to,move);
            if (!move->from)
            {
                break;
            }
            C_COROUTINE_YIELD(C_COROUTINE_YIELD_NOTHING);
        }
    }

    C_COROUTINE_END_AND_RESTART(context);

    move->from = 0;
    move->to = 0;

    return;
}

int
main()
{
    c_coroutine_context_t context = 0;
    Move_t move;

    while (1)
    {
        hanoi_coroutine(&context,5,1,3,&move);

        if (!move.from)
        {
            break;
        }

        printf("%d %d\n",move.from,move.to);
    }

    return 0;
}

