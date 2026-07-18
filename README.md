# c-coroutines
Coroutines in C

A number of years ago I came across a fascinating implementation of coroutines
in C, which used preprocessor macros to implement YIELD functionality using an
unconventional, but surprisingly legal, functionality of the switch statement.
A similar "misuse" of the switch statement had previously been used in Duff's
device, a trick discovered by Tom Duff at Bell Labs.

This implementation was done by Simon Tatham, who is well known for his other
projects, probably most notably PuTTY, although I am a fan of the set of GUI
puzzle games he wrote. At the time of creation of this repository, lots of
information about the man and his projects (including coroutines) was availble
here: https://www.chiark.greenend.org.uk/~sgtatham/

I have experimented with several different implementations of this coroutine
device, a few of which will be published in this repository.
