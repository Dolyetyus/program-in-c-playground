With this experiment, I did research on execution speeds of the same program written in C and Assembly x64 and compared to results. 

Both programs are run on the same cloud computer, where each of the four basic arithmetic operations are done in the same order and the loop is executed 250 million times and the time difference before and after the loop is noted. Both programs used 8 byte long/quad values and for division, conversion to float is performed on the dividend.

Both programs are executed 10 times, where the average computation speed for the Assembly program was ***2.715606*** seconds and for the C program it was ***3.907587***.

The result shows us that Assembly language is **1.44** times faster for basic calculations compared to C on the cloud computer I used.
