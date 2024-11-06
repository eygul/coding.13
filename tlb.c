/*

1- As far as I was able to understand, gettimeofday() is as precise as a microsecond. The operation has to take longer than a microsecond for it to be timed precisely. 
2- The program is below.
5- Using gcc's optimize option gcc -O0 to disable optimization. This is the default setting.
6- This could be achieved by pinning the process to a certain CPU core to ensure cache affinity. We can do that by using methods such as sched_setaffinity or pthread_setaffinity_np in Linux. 
7- Yes, the uninitialized array could incur additional overhead, which would affect the timing. To prevent that, the array could be initialized before starting the timing loop to avoid this first access penalty.

*/

#include <sys/time.h> 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // for sysconf

int main(int argc, char *argv[])
{
    if (argc < 3) {
        fprintf(stderr, "Usage: %s pages trials\n", argv[0]);
        return 1;
    }
    int num_pages = atoi(argv[1]);        
    int trials = atoi(argv[2]);      
    long page_size = sysconf(_SC_PAGESIZE);   
    long jump = page_size / sizeof(int);
    int *arr = malloc(num_pages * page_size);  
    struct timeval start, end;
    gettimeofday(&start, NULL);
    for (int j = 0; j < trials; j++) {
        for (int i = 0; i < num_pages * jump; i += jump) {
            arr[i] += 1;
        }
    }
    gettimeofday(&end, NULL);
    double avg_cost_per_page = ((end.tv_sec - start.tv_sec) * 1000000.0 + (end.tv_usec - start.tv_usec)) / (trials * num_pages);
    printf("Average time per page access: %f µs\n", avg_cost_per_page);
    free(arr);
    return 0;
}