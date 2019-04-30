#include <stdio.h>  
#include <Math.h> 
#include <stdlib.h>
#include <conio.h>

#define PI 3.14159265358 //pi with 11 correct places
double input_voltage;

void complex_addition(double in1_real,double in1_img,double in2_real,double in2_img, double *out3_real, double *out3_img)//Performs complex addition
{
	*out3_real=in1_real+in2_real;//real part
	*out3_img=in1_img+in2_img;//img part
}
void complex_substraction(double in1_real,double in1_img,double in2_real,double in2_img, double *out3_real, double *out3_img)
{
	*out3_real=in1_real-in2_real;//real part
	*out3_img=in1_img-in2_img;//Img part
}
void print_results(double *result_table_impedance_real,double *result_table_impedance_img,double *result_table_current_real,double *result_table_current_img,double *result_table_voltage_real,double *result_table_voltage_img, int n,int components[])//Print Results function
{
	int loop=0;// Iterative variable
	double total_imp_Real=0,total_imp_Img=0;// temp variable
	printf("\nComponents ");
	while(loop<n)//loop to print the table
	{
		if(components[loop]==1)
		{
			printf("|             R              ");
		}
		else if(components[loop]==2)
		{
			printf("|             C              ");
			
		}
		else 
		{
			printf("|             I              ");
		}
		loop++;
	}
	printf("|             Total          ");
	printf("\nZ(ohms)    ");
	loop=0;
	while(loop<n)//loop for printing the impedance
	{
		printf("|(%+-0.3e)+(%+-0.3e)j",*(result_table_impedance_real+loop),*(result_table_impedance_img+loop));
		loop++;
	}
	loop=0;
	printf("|(%+-0.3e)+(%+-0.3e)j|",*(result_table_impedance_real+n),*(result_table_impedance_img+n));//print the total impedance values
	printf("\nI(Amps)    ");
	while(loop<n)//loop for printing current values
	{
		printf("|(%+-0.3e)+(%+-0.3e)j",*(result_table_current_real+loop),*(result_table_current_img+loop));
		loop++;
	}
	loop=0;
	printf("|(%+-0.3e)+(%+-0.3e)j|",*(result_table_current_real+n),*(result_table_current_img+n));// print the total current value
	printf("\nV(Volt)    ");
	total_imp_Real=0;total_imp_Img=0,loop=0;
	while(loop<n)// loop for printing the voltage values
	{
		printf("|(%+-0.3e)+(%+-0.3e)j",*(result_table_voltage_real+loop),*(result_table_voltage_img+loop));
		loop++;
	}
	printf("|(%+-0.3e)+(%+-0.3e)j|",*(result_table_voltage_real+n),*(result_table_voltage_img+n));// print the total voltage value
}
void calculate_impeadance(double *result_table_impedance_real, double *result_table_impedance_img, int components[], double values[], int n, int freq, int choice)//calculate impedance functions
{
	double *result_table_current_real,*result_table_current_img,*result_table_voltage_real,*result_table_voltage_img;// variables declaration
	double total_imp_Real=0,total_imp_Img=0,total_current_Real=0,total_current_Img=0;// variables declaration
	int loop=0;
	result_table_current_real=(double*) malloc((n+1) * sizeof(double));//memory allocation
	result_table_current_img=(double*) malloc((n+1) * sizeof(double));//memory allocation
	result_table_voltage_real=(double*) malloc((n+1) * sizeof(double));//memory allocation
	result_table_voltage_img=(double*) malloc((n+1) * sizeof(double));//memory allocation
	if(choice==1)//Series circuit impedance calculation
	{
		while(loop<n)
		{
			if(components[loop]==1)// calculate for resistance
			{
				*(result_table_impedance_real+loop)=*(result_table_impedance_real+loop);
				*(result_table_impedance_img+loop)=*(result_table_impedance_img+loop);
				*(result_table_voltage_real+loop)=input_voltage;
				*(result_table_voltage_img+loop)=0;
				*(result_table_current_real+loop)=(*(result_table_voltage_real+loop)/(*(result_table_impedance_real+loop)));
				*(result_table_current_img+loop)=0;
				total_current_Real=(total_current_Real+ *(result_table_current_real+loop));
				total_current_Img=(total_current_Img+*(result_table_current_img+loop));
				total_imp_Real=(total_imp_Real+ *(result_table_impedance_real+loop));
				total_imp_Img=(total_imp_Img+(*(result_table_impedance_img+loop)));
			}
			else if(components[loop]==2)// claculate impedance for capacitance
			{
				*(result_table_impedance_img+loop)=-(1/ (*(result_table_impedance_img+loop)*2*PI*freq));	
				*(result_table_voltage_real+loop)=input_voltage;
				*(result_table_voltage_img+loop)=0;
				*(result_table_current_real+loop)=0;
				*(result_table_current_img+loop)=-(*(result_table_voltage_real+loop)/(*(result_table_impedance_img+loop)));
				total_imp_Real=(total_imp_Real+ *(result_table_impedance_real+loop));
				total_imp_Img=(total_imp_Img+*(result_table_impedance_img+loop));
				total_current_Real=(total_current_Real+ *(result_table_current_real+loop));
				total_current_Img=(total_current_Img+(*(result_table_current_img+loop)));
			}
			else // calculate the inductance
			{
				*(result_table_impedance_img+loop)=(*(result_table_impedance_img+loop)*2*PI*freq);
				*(result_table_voltage_real+loop)=input_voltage;
				*(result_table_voltage_img+loop)=0;
				*(result_table_current_real+loop)=0;
				*(result_table_current_img+loop)=-((*(result_table_voltage_real+loop))/(*(result_table_impedance_img+loop)));
				total_imp_Real=(total_imp_Real+ *(result_table_impedance_real+loop));
				total_imp_Img=(total_imp_Img+*(result_table_impedance_img+loop));
				total_current_Real=(total_current_Real+ *(result_table_current_real+loop));
				total_current_Img=(total_current_Img+(*(result_table_current_img+loop)));
			}
			loop++;
		}
		*(result_table_impedance_real+n)=total_imp_Real;// store total impedance real
		*(result_table_impedance_img+n)=total_imp_Img;// store total impedance img
		*(result_table_voltage_real+n)=input_voltage;// store total voltage real
		*(result_table_voltage_img+n)=0;// store total voltage img
		*(result_table_current_img+n)=total_current_Img;// store total current img
		*(result_table_current_real+n)=total_current_Real;// store total current real
	}
		if(choice==2)//parllel calculation
		{
			double temp;
			while(loop<n)
			{
				if(components[loop]==1)// impedance for resistir
				{
					*(result_table_impedance_real+loop)=*(result_table_impedance_real+loop);
					*(result_table_impedance_img+loop)=*(result_table_impedance_img+loop);
					*(result_table_voltage_real+loop)=input_voltage;
					*(result_table_voltage_img+loop)=0;
					*(result_table_current_real+loop)=(*(result_table_voltage_real+loop)/(*(result_table_impedance_real+loop)));
					*(result_table_current_img+loop)=0;
					total_current_Real=(total_current_Real+ *(result_table_current_real+loop));
					total_current_Img=(total_current_Img+*(result_table_current_img+loop));
					total_imp_Real=(1/((total_imp_Real+ *(result_table_impedance_real+loop))));
					total_imp_Img=(total_imp_Img+*(result_table_impedance_img+loop));
				}
				else if(components[loop]==2)// impedance for capacitor
				{
					*(result_table_impedance_img+loop)=-(1/ (*(result_table_impedance_img+loop)*2*PI*freq));	
					*(result_table_voltage_real+loop)=input_voltage;
					*(result_table_voltage_img+loop)=0;
					*(result_table_current_real+loop)=0;
					*(result_table_current_img+loop)=-(*(result_table_voltage_real+loop)/(*(result_table_impedance_img+loop)));
					temp= -(1/ (*(result_table_impedance_img+loop)));
					total_imp_Real=(total_imp_Real+ *(result_table_impedance_real+loop));
					total_imp_Img=(total_imp_Img+temp);
					total_current_Real=(total_current_Real+ *(result_table_current_real+loop));
					total_current_Img=(total_current_Img+(*(result_table_current_img+loop)));
				}
				else//impedance for inductance
				{
					*(result_table_impedance_img+loop)=(*(result_table_impedance_img+loop)*2*PI*freq);
					*(result_table_voltage_real+loop)=input_voltage;
					*(result_table_voltage_img+loop)=0;
					*(result_table_current_real+loop)=0;
					printf("value: %lf",*(result_table_impedance_img+loop));
					*(result_table_current_img+loop)=-((double)(*(result_table_voltage_real+loop))/(*(result_table_impedance_img+loop)));
					temp= -(1/ (*(result_table_impedance_img+loop)));
					total_imp_Real=(total_imp_Real+ *(result_table_impedance_real+loop));
					total_imp_Img=((total_imp_Img+temp));
					total_current_Real=(total_current_Real+ *(result_table_current_real+loop));
					total_current_Img=(total_current_Img+(*(result_table_current_img+loop)));
				}
				loop++;
			}
		*(result_table_impedance_real+n)=(total_imp_Real/((total_imp_Real*total_imp_Real)+(total_imp_Img*total_imp_Img)));
		*(result_table_impedance_img+n)=-(total_imp_Img/((total_imp_Real*total_imp_Real)+(total_imp_Img*total_imp_Img)));
		*(result_table_voltage_real+n)=input_voltage;
		*(result_table_voltage_img+n)=0;
		*(result_table_current_img+n)=total_current_Img;
		*(result_table_current_real+n)=total_current_Real;
	}
	print_results(result_table_impedance_real,result_table_impedance_img,result_table_current_real,result_table_current_img,result_table_voltage_real,result_table_voltage_img,n,components);// call the print function
}
void complex_multiplication(double in1_real,double in1_img,double in2_real,double in2_img, double *out3_real, double *out3_img)
{
	*out3_real=((in1_real*in2_real)-(in1_img*in2_img));
	*out3_img=((in1_real*in2_img)+(in2_real*in1_img));
}
void complex_division(double in1_real,double in1_img,double in2_real,double in2_img, double *out3_real, double *out3_img)
{
	*out3_real=(((in1_img*in2_real)+(in2_img*in1_img))/((in2_img*in2_img)+(in2_real*in2_real)));
	*out3_img=((in2_real-in1_real)/((in2_img*in2_img)+(in2_real*in2_real)));
}
int main()  
{  
	printf("** Lakshmi Saketh Impedance Calculator **\n");  //print student details
	int input,freq,n,loop=0;
	double *result_table_impedance_real,*result_table_impedance_img,temp_real=0, temp_img=0, *result_table_current_real,*result_table_current_img,*result_table_voltage_real,*result_table_voltage_img;
	float output,step_radians,iterator_radians=0;
	printf("Do you want to create 1.Series or 2.Parllel \n"); //give user some info that he has to enter
	scanf("%d", &input);// read the selection from user
	while(input !=1 && input !=2){printf("Invalid Inputs\n");
		printf("Do you want to create 1.Series or 2.Parllel \n");  
	scanf("%d", &input);// read the selection from user
	printf("\n");
	};//while loop close
		printf("\nEnter the frequency in Hertz of the Source:\n"); 
	scanf("%d",&freq);//read the frequency
	printf("Enter the Source Voltage of the circuit:\n"); 
	scanf("%lf", &input_voltage);// read the selection from user
	printf("How many Components you want to enter:\n"); 
	scanf("%d",&n);
	int component[n];
	double values[n];
	result_table_impedance_real=(double*) malloc((n+1) * sizeof(double));//Dynamically memory allocation
	result_table_impedance_img=(double*) malloc((n+1) * sizeof(double));
	printf("Enter component type 1.Resistor 2.Capacitor 3.Inductor:\n"); 
	while(loop<n)// reads the values in loop and stores values in array.
	{printf("\nEnter component :%d\n", (loop+1));
		scanf("%d",&component[loop]);// read the element type.
		if(component[loop]==1){printf("\nEnter the resistance in unit Ohms:%d\n",component[loop]); 
		scanf("%lf",&values[loop]);
		*(result_table_impedance_real+loop)=values[loop];//resistor has only real value
		*(result_table_impedance_img+loop)=0;//resistor has no imaginary value
		}
		else if(component[loop]==2){printf("\nEnter the capacitance in units Farads:%d\n",component[loop]);
		scanf("%lf",&values[loop]);
		*(result_table_impedance_real+loop)=0;//resistor has no real value
		*(result_table_impedance_img+loop)=values[loop];//resistor has only real value
		}
		else {printf("Enter the inductance units in Henrys:%d\n",component[loop]);
			scanf("%lf",&values[loop]);
			*(result_table_impedance_real+loop)=0;//resistor has no real value
			*(result_table_impedance_img+loop)=(values[loop]);//resistor has only real value
			}
	loop++;
	}//close while loop
	calculate_impeadance(result_table_impedance_real,result_table_impedance_img,component,values,n,freq,input);//call the calculate impedance function
	getch();
    return 0;  
	
}//Main close