/*
 *  Lincoln To
 *  104 441 725
 *  Assignment 6
 *  CS 35L Lab 5
 */

To begin, I first went over the general concepts of ray tracing and embarrassingly parallel problems to get an overview
of the problem that we are trying to solve in this lab. After doing this and going through the main.c source, I got a
general understanding of how to approach the problem - parallelize the drawing/rendering of pixels into multiple threads
to try and improve performance.

From here, an overview of the pthread_create syntax indicated that the thread needs a function pointer to be passed as
a parameter, thus indicating that part of the code in the main function likely needed to be separated into its own
function for use in multithreading applications. Thus, a large portion of the code was moved to a function called
render_colors, which stores the colors that need to be output in a 3-D array for later.

The biggest problem I ran into was how to logically divide the tasks into different threads based on an arbitrary number
of threads, but the hints in the course slides mentioning that the 3rd and 4th arguments are the focus allowed me to get
some insight on how to proceed, allowing me to complete the problem.

Finally, for the results:
From the output of make clean check, we can see the times as follows:
	real    0m0.086s
	user    0m0.065s
	sys     0m0.000s

	real    0m0.057s
	user    0m0.063s
	sys     0m0.002s

	real    0m0.046s
	user    0m0.065s
	sys     0m0.002s

	real    0m0.036s
	user    0m0.065s
	sys     0m0.003s

As we can see, the 4 times indicate 1 thread, 2 threads, 4 threads, and 8 threads, with increasing number of threads
decreasing the time significantly enough to notice. The maximum improvement of moving up to 8 threads allows the program
to complete 2.38x faster than with 1 thread, indicating that there is a noticeable improvement. 