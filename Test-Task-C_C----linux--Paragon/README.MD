# Problem
Your task is to implement an interface for a basic [LRU cache](https://en.wikipedia.org/wiki/Cache_replacement_policies#LRU).

The interface with the description is provided in the file `cache_lru.h`.

For the implementation, you should use Linux kernel containers: a doubly linked list (`list.h`) and a red-black tree (`rbtree.h`). The headers for these containers and their dependencies are located in the `linux-utils` directory.

## Details
The main structure of the cache, `Cache_lru`, is an implementation detail and can have any content.

The functions `cache_lru_put()` and `cache_lru_get()` must each run in **O(log n)** time complexity or better on average.

Because the containers are derived from the Linux kernel, they extensively use macros — feel free to take advantage of them.

Documentation on how to use the [doubly linked list](https://litux.nl/mirror/kerneldevelopment/0672327201/app01lev1sec2.html) and [red-black trees (rbtree) in Linux](https://www.kernel.org/doc/Documentation/rbtree.txt).
## Build & environment
The project (see `Makefile`) includes a `tests` target. To run tests while working on the problem, you can build and execute them as follows::
```
$ make all
$ ./tests
```
The code will be tested for buildability and functionality using the GCC 12.4.0 compiler. For final verification, you can use the Docker image gcc:12.4 by running the following command:
```
$ docker run --rm -v "$PWD":/usr/src/test_problem -w /usr/src/test_problem gcc:12.4 /bin/bash -c "make all && ./tests"
```

## Misc
When writing code, please try to adhere to the [Linux kernel coding style](https://www.kernel.org/doc/html/v6.10/process/coding-style.html#codingstyle).

If you leave comments in the code, please write them in English.

Additional tests are welcome.
