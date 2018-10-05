/**
 *  Simple program to demonstrate the code profiling
 */

/** functions to be tested */
int max (int i1, int i2)
{
  int r = 0;
  if (i1 > i2) 
	r = i1;
  else 
	r = i2;
  return r;
}

int min (int i1, int i2)
{
  int r = 0;
  if (i1 < i2) 
	r = i1;
  else 
	r = i2;
  return r;
}


/** main program to run the test program */
int main()
{
   for (int j=0; j<1000; j++) {
     for (int i=0; i<100000; i++) max (3,6);
     for (int i=0; i<300000; i++) min (6,3);
   }

   return 0;
}



