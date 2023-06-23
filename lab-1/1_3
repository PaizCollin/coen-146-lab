// Collin Paiz
// 5 January 2022
// Lab 1 - Steps 1-3
// Create a C program with a factorial function. The main function takes 4 arguments for linkBandwidth, userBandwidth, tPSusers, and nPSusers. 
// These values are then used to calculate the probability of certain circuit switching and packet switching scenarios. 

#include <stdio.h>  
#include <math.h>
#include <stdlib.h>

double factorial(double n)
{
    //factorial function
    return tgamma(n+1);
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
   nCSusers = linkBandwidth / userBandwidth;
   printf("5a: Circuit switching senario: %d users\n", nCSusers);
   
   // 6: Packet Switching Senario
   // compute: 6a, b, c, d, e, f, g, h 
   pPSusers = tPSusers;
   pPSusersNotBusy = 1 - pPSusers;
   double pAllNotBusy = pow((1 - pPSusers), (nPSusers - 1));
   double pOneBusy = pPSusers * pow(pPSusersNotBusy, (nPSusers - 1));
   double pExactlyOne = nPSusers * pOneBusy;
   double pTenBusy = pow(pPSusers, 10) * pow(pPSusersNotBusy, (nPSusers-10));
   double pAnyTenBusy = (factorial(nPSusers))/(factorial(10)*factorial((nPSusers-10))) * pow(pPSusers, 10) * pow(pPSusersNotBusy, (nPSusers-10));
   double pTenMoreBusy;
   for(i = 11; i < nPSusers; i++) {
        pTenMoreBusy += (factorial(nPSusers))/(factorial(i)*factorial((nPSusers-i))) * pow(pPSusers, i) * pow(pPSusersNotBusy, (nPSusers-i));
   }
   
   printf("6: Packet switching senario\n");
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