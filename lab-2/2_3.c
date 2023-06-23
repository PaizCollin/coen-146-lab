// Collin Paiz
// 14 January 2022
// Lab 2 - Step 3
// This C program computes how much time elapses from when the client clicks a link until they receive the object. It also calculates how
// much time elapses for 6 small objects. And finally, it also calculates how much time elapses for n parallel TCP connections for 
// persistent and non-persistent HTTP.

#include <math.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    double n = atoi(argv[1]);     // n parallel TCP connections

    int rtt1 = 3;   // local DNS with RTT delay of 3ms
    int rtt2 = 20;  // DNS with RTT delay of 20ms
    int rtt3 = 26;  // DNS with RTT delay of 26ms
    int rtthttp = 47;   // RTT between local host and web server

    int totalRTT = rtt1 + rtt2 + rtt3;

    // calculations
    int a = totalRTT + (2*rtthttp);
    int b = a + (2*6*rtthttp);
    int c_persistent = a + (ceil(6/n)*rtthttp);
    int c_non_persistent = a + (ceil(6/n)*2*rtthttp);

    printf("a: %d ms \nb: %d ms \nc (persistent): %d ms \nc (non-persistent): %d ms \n", a, b, c_persistent, c_non_persistent);

    return 0;
}