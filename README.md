# c-adt

A collection of abstract data types in the C programming language

## Abstract Data Types

-   [Linked-List](src/list.h)
<!-- -   [Doubly Linked-List](src/dlist.h)
-   [Circular Linked-List](src/clist.h)
-   [Stack](src/stack.h)
-   [Queue](src/queue.h) -->

## Build Instructions

The code includes some unit-tests using the
[criterion](https://criterion.readthedocs.io/en/master/index.html) testing library.

```
make
make test
```

## Notes

At this point, the collection of adt's are not made into a library, but this would be a natural
next step. The code is documented using Doxygen style tags.

The code is refactored but heavily inspired by the adt's presented in
[Mastering Algorithms with C](http://shop.oreilly.com/product/9781565924536.do) by O'Reilly.