/*COEN 146L : Lab1 - Step 5&6*/
#include <stdio.h>  
#include <math.h>
#include <stdlib.h>

double factorial(double n)
{
    //factorial function
}

int main(int argc, char *argv[]) {
    if (argc !=5){
	fprintf(stderr,"usage: ./a.out <linkBandwidth> <userBandwidth> <tPSusers> <nPSusers> \n");
	exit(0);
    } 
   int i, linkBandwidth, userBandwidth, nCSusers, nPSusers;
   double pPSusers, tPSusers, pPSusersBusy, pPSusersNotBusy;
   
   // Get values from command line
   linkBandwidth = atoi(argv[1]);
   userBandwidth = atoi(argv[2]);
   tPSusers  = atof(argv[3]);
   nPSusers = atoi(argv[4]);

   // 5a: Circuit Switching Senario
   // how many users --> nCSusers
   printf("5a: Circuit switching senario: %d users\n", nCSusers);
   
   // 6: Packet Switching Senario
   /* compute: 6a, b, c, d, e, f, g, h 
   pPSusers = 
   pPSusersNotBusy = 
   double pAllNotBusy = 
   double pOneBusy = 
   double pExactlyOne = 
   double pTenBusy = 
   double pAnyTenBusy = 
   double pTenMoreBusy = 
   
   */
   printf("6: Packet switching senario");
   printf("6a: The probability that a given (specific) user is busy transmitting = %f\n", pPSusers);
   printf("6b: The probability that ine specific other user is not busy =  %f\n", pPSusersNotBusy);
   printf("6c: The probablility that all of the other specific other users are not busy =  %e\n", pAllNotBusy);
   printf("6d: The probability that one specific user is transmitting and the remianing users are not transmitting =  %e\n", pOneBusy);
   printf("6e: The probability that exactly one of the nPSusers users is busy is pPSusers times the probability that a given specific user is transmitting and the remaining users are not transmitting = %le\n", pExactlyOne);
   printf("6f: The probabalitiy that 10 specific users of nPSusers are transmitting and the others are idle = %lg\n", pTenBusy);
   printf("6g: The probability that any 10 users of nPSusers are transmitting and the others are idle = %lg\n", pAnyTenBusy);
   printf("6h: The probability that more than 10 users of nPSusers are transmitting and the others are idle = %lg\n", pTenMoreBusy);
   return 0;
}