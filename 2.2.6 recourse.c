//---------------------------------------------------------------------------

#include <stdio.h>
#pragma hdrstop

#include <tchar.h>
#include <math.h>
#include <conio.h>


//---------------------------------------------------------------------------

#pragma argsused

int factorial(int n)
{
  int result = 1;
  int i;
  for(i = 1; i<=n; i++)
  {
	  result *= i;
  }

  return result;
}



double MacLoren_recourse(double x,double SequenceResult, double e0, int* n)
{

	double e = fabs( sin(x) - SequenceResult);
	if(e >= e0)
	{
	   (*n)++;
	   SequenceResult += powl( (-1), (*n)-1 )*( powl(x, 2*(*n) -1) )/ factorial(2*(*n) -1);
	   return MacLoren_recourse(x,SequenceResult,e0,n);
	}
	else
	{
		return SequenceResult;
    }
}
int _tmain(int argc, _TCHAR* argv[])
{


	double e0;
	double x;
	double SequenceResult;
	double RealResult;
	int n = 1;


	printf("please, enter x in radians desirable from the interval [-3.14;3.14] \n");
	scanf("%lf",&x);
	printf("please, enter e \n");
	scanf("%lf",&e0);

	RealResult = sin(x);
	SequenceResult = x;
	SequenceResult = MacLoren_recourse(x,SequenceResult,e0,&n);
	printf("value of sin(x) is %1.10lf\n value of sequence is %1.10lf\n the numbers of members is %d", RealResult,SequenceResult,n);
	getch();


	return 0;
}
//---------------------------------------------------------------------------
