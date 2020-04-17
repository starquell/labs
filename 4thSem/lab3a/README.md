# Lab 3a (Parallel quicksort)

**Requires C++14**

Running tests and benchmark requires C++17 and linking `tbb` and `pthread` for C++17 Parallel Algorihms

Running benchmark also requires globally installed [Google Benchmark](https://github.com/google/benchmark)

All executables can be generated using CMake and `CMakeLists.txt` file in repository

___
**Benchmark results on my machine (Intel Core i5 5200U (2.2 GHz), 8 GB RAM):**

| Sort function 	| Time     	| Vector Size 	| 
|---------------	|----------	|-------------	| 
| std::sort     	| 0.001 ms 	| 100         	| 
| std::sort     	| 0.009 ms 	| 1000        	| 
| std::sort     	| 0.141 ms 	| 10000       	| 
| std::sort     	| 1.64 ms  	| 100000      	| 
| std::sort     	| 20.9 ms  	| 1000000     	| 
| std::sort     	| 1013 ms  	| 10000000    	| 

| Sort function 	| Time     	| Vector Size 	|
|---------------	|----------	|-------------	|
| My Quicksort  	| 0.001 ms 	| 100         	|
| My Quicksort  	| 0.010 ms 	| 1000        	|
| My Quicksort  	| 0.164 ms 	| 10000       	|
| My Quicksort  	| 1.87 ms  	| 100000      	|
| My Quicksort  	| 23.7 ms  	| 1000000     	|
| My Quicksort  	| 1027 ms  	| 10000000    	|

| Sort function      	| Time     	| Vector Size 	|
|--------------------	|----------	|-------------	|
| Parallel std::sort 	| 0.000 ms 	| 100         	|
| Parallel std::sort 	| 0.011 ms 	| 1000        	|
| Parallel std::sort 	| 0.074 ms  | 10000       	|
| Parallel std::sort 	| 0.660 ms 	| 100000      	|
| Parallel std::sort 	| 8.28 ms  	| 1000000     	|
| Parallel std::sort 	| 270 ms   	| 10000000    	|

| Sort function         	| Time     	| Vector Size 	|
|-----------------------	|----------	|-------------	|
| My Parallel Quicksort 	| 0.001 ms 	| 100         	|
| My Parallel Quicksort 	| 0.010 ms 	| 1000        	|
| My Parallel Quicksort 	| 0.164 ms 	| 10000       	|
| My Parallel Quicksort 	| 1.34 ms  	| 100000      	|
| My Parallel Quicksort 	| 13.0 ms  	| 1000000     	|
| My Parallel Quicksort 	| 146 ms   	| 10000000    	|

___
**Heap operations in sorting std::vector of size 1000000) :** 

| Sort functions     	| Heap memory consumed 	| Allocations 	|
|--------------------	|----------------------	|-------------	|
| std::sort          	| 0                    	| 0           	|
| My Quicksort         	| 0                    	| 0           	|
| Parallel std::sort 	| 1.7 KB               	| 7           	|
| My Parallel Quicksort	| 18 KB                	| 423  ^_^    	|

Heap operations have been measured using [Heaptrack](https://github.com/KDE/heaptrack)




