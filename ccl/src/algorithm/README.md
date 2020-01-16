# Algorithm

## Parallel

The parallel algorithm is implemented in `parallel.c`. It utilises code split
over two subdirectories, `/parallel` and `/steps`:

* `/parallel` is responsible for the _meat_ of the algorithm, and contains 
  functions that depend purely on their inputs. This allows for easy testing of
  the core algorithm.
* `/steps` contains all code for the BSP supersteps. This includes code that
  depends on _e.g._ the BSP library, global state and/or all things God hath
  forbidden Man. This is fairly hard to bring  under test, hence the distinction
  between `/parallel` and `/steps`.

## Sequential

Implemented in `sequential.c` - nothing special.