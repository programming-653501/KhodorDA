//---------------------------------------------------------------------------

#include <stdio.h>
#pragma hdrstop
#include <math.h>
#include <stdio.h>
#include <tchar.h>
#include <conio.h>
//---------------------------------------------------------------------------


int factorial(int);
#pragma argsused
int _tmain(int argc, _TCHAR* argv[])
{
	double e0;
	double x;
	double RealResult;
	double SequenceResult;
	int n =1;
	double e;
	//printf("%1.10lf\n",sin(90) );

	printf("please, enter x in radians desirable from the interval [-3.14;3.14] \n");
	scanf("%lf",&x);
	printf("please, enter e\n");
	scanf("%lf",&e0);

	RealResult = sin(x);
	SequenceResult = x;
	e = fabs( RealResult - SequenceResult);

	while(e >= e0)
	{
		n++;
		SequenceResult += powl( (-1), n-1 )*( powl(x, 2*n -1) )/ factorial(2*n -1);
		e = fabs(RealResult - SequenceResult);
	}

	printf("value of sin(x) is %1.10lf\n value of sequence is %1.10lf\n the numbers of members is %d", RealResult,SequenceResult,n);
	getch();
	return 0;
}
//---------------------------------------------------------------------------

int factorial(int n)
{
	if(n==1 || n==0)
	{
		return 1;
	}

	return n*factorial(n-1);
}
