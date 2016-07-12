#include <stdio.h>
#include <math.h>
#define PI 3.14159265
int main ()
{
    float z;
	float pos=0;
	float pos1;
	float pos2;
	float pos3;
	float pos4;
	float pos5;
	float pos6;
	float Q ;
    float Y ;
    float B,E,U;

    float one =42.3;
    float two;
    float three=47.7;
    float five;
    for(;;)
    {
        printf("z");
        scanf("%f",&z);
        printf("pos1");
        scanf("%f",&pos1);
        printf("Q");
        scanf("%f",&Q);
        for(pos=0; pos<=180 ;pos++)
        {
            if(z>=28 && z<=40)
            {
                pos3=90;
                Y=((19*19)+(21*21)-(z*z));
			    Y=Y/(2*19*21);
			    Y=acos(Y)*(180/PI);
			    B=((z*z)+(21*21)-(19*19));
                B=B/(2*21*z);
                B=acos(B)*(180/PI);
                if(pos<=pos3)
                {
           	        printf("pos 3 = %f \n",pos);
                }
                if(pos1>180 )
                {
                	
                    pos2=180-B-Q;
                    pos4=180-(Y-90);
                    if(pos<=pos1)
                    {
 	           	        printf("pos 1 = %f \n",pos);
                    }
                    if(pos<=pos2)
                    {
           	            printf("pos 2 = %F \n",pos);
                    }
                    if(pos<=pos4)
                    {
           	            printf("pos 4 = %F \n",pos);
                    }
                 }
                 else   if((pos1<=180))
                 {
                     pos2=(B+Q);
                     pos4=(Y-90);
                     if(pos<=pos1)
                     {
 	           	         printf("pos 1 = %f \n",pos);
                     }
                     if(pos<=pos2)
                     {
           	             printf("pos 2 = %f \n",pos);
                     }
                     if(pos<=pos4)
                     {
           	             printf("pos 4 = %f \n",pos);
                     }
                  }
                  
                }
            if(z>=12.5 && z<28)
            {
      	     	E=(z*z)+(14.8*14.8)-(19*19);
             	E=E/(2*14.8*z);
              	E=acos(B)*(180/PI);
              	
               	U=180-42.3-E;
                if(Q<=U)
                {
       	  	   		two =((z*z)+(14.87*14.87)-(19*19));
   					two =two/(2*z*14.87);
        			two =acos(two)*(180/PI);
        			five =((19*19)+(14.87*14.87)-(z*z));
        			five =five/(2*19*14.87);
	    			five =acos(five)*(180/PI);
     				if(pos1>180)
      				{
      				
       					pos3=0;
         				pos2=180-(one+two+Q);
          				pos4=180-(three+five-90);
           				if(pos<=pos1)
           				{
   	        				printf("pos 1 = %f \n",pos);
           				}
            			if(pos<=pos2)
            			{
            				printf("pos 2 = %F \n",pos);
             			}
             			if(pos<=pos3)
           				{
            				printf("pos 3 = %f \n",pos);
           				}
            			if(pos<=pos4)
           				{
            				printf("pos 4 = %F \n",pos);
             			}
      				}
      				else   if((pos1<=180))
      				{
      				
       					pos3=180;
         				pos2=one+two+Q;
          				pos4=three+five-90;
           				if(pos<=pos1)
           				{
        					printf("pos 1 = %f \n",pos);
           				}
               			if(pos<=pos2)
               			{
  	            			printf("pos 2 = %f \n",pos);
           				}
            			if(pos<=pos3)
            			{
            				printf("pos 3 = %f \n",pos);
           				}
         			    if(pos<=pos4)
             			{
	            			printf("pos 4 = %f \n",pos);
             			}
          			}
                }
          			 else
					  printf("error \n");

        }
        }
    
    if(pos1>180)
    pos1 =pos1-180;
    printf("\n\n\n\n\n\n\n");
    printf("pos 1 = %f \n",pos1);
    printf("pos 2 = %f \n",pos2);
    printf("pos 3 = %f \n",pos3);
    printf("pos 4 = %f \n",pos4);

 	}
    
}
