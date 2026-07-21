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

His coroutine macros also employ another nice trick: using __LINE__ to save
the current context and as a switch case target, so that a single macro can
return a value and identify where the coroutine should continue when called
again, without needing to provide an explicit case target.

Simon's original coroutine.h supports two styles of coroutines: one limited
to only static context and one that dynamically allocates and frees context
data and names a struct pointer that to use to refer to local context. The
static context version does not reset its saved line number so only runs
through once unless you reset it explicitly.

Years ago, I had created my own version of coroutine.h, originally based on
Simon's version but with many changes, some trivial, some less so:

- Non-final coroutine returns are stylized as "yield" operations
- Revised (and Gnu-compatible) naming conventions are used
- There is no explicit static context variant
- A named pointer is supported but not required to access context data
- Separate void-return macros (and thus a few parentheses) are avoided
- Context can end in either a terminal state or a sequence restart
- Context state (pending/running/stopped) can be explicitly queried
- Context handles can be safely released/reused

I have experimented with several different implementations of this coroutine
device, a few of which will be published in this repository.

MIT license
