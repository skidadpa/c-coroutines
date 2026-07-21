# c-coroutines
Coroutines in C

A number of years ago I came across a fascinating implementation of coroutines
in C, which used preprocessor macros to implement YIELD functionality using an
unconventional, but surprisingly legal, functionality of the switch statement.

A similar "misuse" of the switch statement had previously been used in Duff's
Device, a trick Tom Duff (pretty sure he was at Bell Labs at the time) used to
implement loop unrolling. Here is the essence of Duff's Device, reformatted a
bit to (hopefully) better highlight the code flow:

		        n = (count + 7) / 8;

		switch (count % 8)
        {
		case 0:
                do
                {
                    *REG = *src++;
		case 7:		*REG = *src++;
		case 6:		*REG = *src++;
		case 5:		*REG = *src++;
		case 4:		*REG = *src++;
		case 3:		*REG = *src++;
		case 2:		*REG = *src++;
		case 1:		*REG = *src++;
                }
                while (--n > 0);
		}

This unrolls `do { *REG = *src++; } while (--count > 0);` by a factor of 8,
using a switch to start at an offset in the do loop body when count is not
divisible by 8 rather than duplicating part of the loop body outside of the
loop. This is a common practice in assembly language, but isn't something
you generally see in higher-order languages.

Simon Tatham, well known for other projects (most notably PuTTY, although I
am a fan of his GUI puzzle games and lots of folks will recognize him as the
author of NASM), used a similar trick to create a set of preprocessor macros
that implement coroutines. At the time of creation of this repository, lots
of information about the man and his projects (including work on coroutines)
was available at https://www.chiark.greenend.org.uk/~sgtatham/

His coroutine macros combine this trick with another: using `__LINE__` to
save and restore the current context, so that a single macro can return a
value and identify where the coroutine should continue when called again,
without needing to provide an explicit switch/case target.

Simon's original coroutine.h supports two styles of coroutines: one limited
to only static context (which does not reset the saved line number so only
runs through once unless you reset it explicitly) and one that dynamically
allocates and frees context data and provides a struct pointer that refers
to local context (which allocates and frees the context as needed and thus
automatically resets the context when complete).

Years ago, I had created my own version of coroutine.h, based on Simon's
version but with many changes, some trivial, some less so, including:

- Non-final coroutine returns are stylized as "yield" operations
- Revised (and Gnu-compatible) naming conventions are used
- There is no explicit static context variant
- A named pointer is supported but not required to access context data
- Separate void-return macros (and thus a few parentheses) are avoided
- Context can end in either a terminal state or a sequence restart
- Context state (pending/running/stopped) can be explicitly queried
- Context handles can be safely released/reused

I have experimented with a few implementations of this coroutine device
and will include some useful versions in this repo, including explicitly
coded versions like this:

        #include <stdio.h>

        #define START (0)
        #define RUN (1)
        #define END (2)

        struct ctx {
            int state;
            int value;
        };

        int one_to_ten(struct ctx *context)
        {
            switch (context->state) {
            case START:
                for (context->value = 1; context->value < 10; ++context->value)
                {
                    context->state = RUN;
                    return context->value;
            case RUN:;
                }
                context->state = END;
                return context->value;

            default:
                fprintf(stderr, "ERROR: illegal context state\n");
                return -1;
            }
        }

        int main()
        {
            struct ctx context = {START};

            while (context.state < END)
            {
                printf("%d", one_to_ten(&context));
            }

            return 0;
        }

Lately I have been using the Creative Commons Zero 1.0 Universal license
for most of my work, although Simon Tatham used the MIT license for his
implementation so I am using that license here. Even though these are
complete reimplementations that don't share any of his code, they are at
least spiritual successors so he should be given credit.
