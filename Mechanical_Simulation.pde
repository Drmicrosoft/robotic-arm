
import processing.serial.*;
Serial myPort;

float pos1=0;
float pos2=0;
float pos3=0;
float pos4=0;
float pos5=0;
float pos6=0; 
float k;
float q;
 float pos=0;
 float Z;
     float E,U;


void setup() {
size(1200,1200);
myPort = new Serial(this, "/dev/ttyUSB0", 9600);
}
void draw() {
  
   int a=mouseX;
   int b=mouseY;
   robot(a,b);
   
if (keyPressed) {
    if (key == 'b' || key == 'B') {
      if(a>420)
      {
        println("Start" + Z );
        if((int(Z)<280)&&(int(Z)>125))
        {
           println("pos3 " + int(180));
           myPort.write('d');
          delay(2000);
          myPort.write(str(180));
          delay(5000);
           println("pos2 " + int(pos2*180/PI));
          myPort.write('e');
          delay(2000);
          myPort.write(str(int(pos2*180/PI)));
          delay(5000);
          
           println("pos4 " + int((pos4*180/PI)+(180-(pos2*180/PI))));
           myPort.write('c');
          delay(2000);
          myPort.write(str(int((pos4*180/PI)+(180-(pos2*180/PI)))));
          delay(5000);
          
      }
       if((int(Z)<400)&&(int(Z)>280))
        {
           println("pos3 " + int(91));
           
          myPort.write('d');
          delay(2000);
          myPort.write(str(91));
          delay(5000);
            println("pos2 " + int(pos2*180/PI));
           
          myPort.write('e');
          delay(2000);
          myPort.write(str(int(pos2*180/PI)));
          delay(5000);
         
           println("pos4 " + int((pos4*180/PI)-(90-(180-(pos2*180/PI)))));
           
          myPort.write('c');
          delay(2000);
          myPort.write(str(int((pos4*180/PI)-(90-(180-(pos2*180/PI))))));
          delay(5000);
      }
    }
    else if(a<420)
      {
        println("Start" + Z );
        if((int(Z)<280)&&(int(Z)>125))
        {
          
           println("pos3 " + int(0));
           
           myPort.write('d');
          delay(1000);
          myPort.write(str(0));
          delay(5000);
           println("pos2 " + int(180-(pos2*180/PI)));
           myPort.write('e');
          delay(2000);
          myPort.write(str(int(180-(pos2*180/PI))));
          delay(5000);
          
           println("pos4 " + int(180-((pos4*180/PI)+(180-(pos2*180/PI)))));
           
           myPort.write('c');
          delay(2000);
          myPort.write(str(int(180-((pos4*180/PI)+(180-(pos2*180/PI))))));
          delay(5000);
          
      }
       if((int(Z)<400)&&(int(Z)>280))
        {
          
           println("pos3 " + int(91));
           myPort.write('d');
          delay(2000);
          myPort.write(str(91));
          delay(5000);
           println("pos2 " + int(180-(pos2*180/PI)));
           myPort.write('e');
          delay(2000);
          myPort.write(str(int(180-(pos2*180/PI))));
          delay(5000);
          
           println("pos4 " + int(180-((pos4*180/PI)-(90-(180-(pos2*180/PI))))));
           myPort.write('c');
          delay(2000);
          myPort.write(str(int(180-((pos4*180/PI)-(90-(180-(pos2*180/PI)))))));
          delay(5000);
          
      }
    }
    
    
    
    

    }   
       else if (key == 'c' || key == 'C') {
           myPort.write('e');
          delay(2000);
          myPort.write(str(91));
          delay(5000);
         
         myPort.write('d');
          delay(2000);
          myPort.write(str(91));
          delay(5000);
         
         myPort.write('c');
          delay(2000);
          myPort.write(str(91));
          delay(5000);
         
       }

}

   
}
void robot(int a, int b) 
{
  
if(a<410)

{background(115);
fill(155,155,155);
ellipseMode(CENTER);
ellipse(420,600,800,800);
   float O = 0;
   text("a = "+a, 0, 180);
    Z=sqrt((600-b)*(600-b)+(410-a)*(410-a));
   if(a!=410)
   {O =asin((600-b)/Z);}
c(O,Z,b);
text("z = "+Z, 10,60); 
text("o = "+O, 10,100); 
text("o degree = "+(O*180/PI), 100,10); 
text("a = "+a, 100,60); 
text("b = "+b, 100,100); 
text("600-b = "+(600-b), 200,100); 
text("410-a = "+(410-a), 200,60); 
 if(Z<=400)
{
   
  float  c =Z *cos(O);
  float d =Z * sin(O);
  //line(300,600,300-c,600-d);
//  text("word", 0, 30);
 
  text("c = "+c, 10, 30); 
  
  text("d = "+d, 120, 30); 
  
 }
 
 else {
   text("error", 80, 30);
 }

d();
k=410;
q=600;

 text("k = "+k, 190, 30); 
  
  text("q = "+q, 250, 30); 
pos2=(pos2*PI/180);
pos4=(pos4*PI/180);
stroke(255);

k=420;
q=600;
c(O,Z,b);
 
sketch(k,q,110,pos2,a);


text("k = "+k, 190, 60); 
  
  text("q = "+q, 250, 60);
sketch(k,q,100,pos3,a);
text("k = "+k, 190, 90); 
  
  text("q = "+q, 190, 90);
sketch(k,q,190,pos4,a);
text("k = "+k, 190, 120); 
  
  text("q = "+q, 250, 120);
 
}

else 
{
background(115);
fill(155,155,155);
ellipseMode(CENTER);
ellipse(420,600,800,800);

   float O = 0;
   text("a = "+a, 0, 180);
    Z =sqrt((600-b)*(600-b)+(a-410)*(a-410));
   if(a!=410)
   {O =asin((600-b)/Z);}

text("z = "+Z, 10,60); 
text("o = "+O, 10,100); 
text("o degree = "+(O*180/PI), 100,10); 
text("a = "+a, 100,60); 
text("b = "+b, 100,100); 
text("600-b = "+(600-b), 200,100); 
text("410-a = "+(410-a), 200,60);

 if(Z<=400)
{
   
  float  c =Z *cos(O);
  float d =Z * sin(O);
  //line(300,600,300+c,600-d);
//  text("word", 0, 30);
 
  text("c = "+c, 10, 30); 
  
  text("d = "+d, 120, 30); 
  
 }
 
 else {
   text("error", 80, 30);
 }
d();


k=420;
q=600;
//if(pos2<90)
  //pos4=180-(pos2+pos4+90);
 // else
 c(O,Z,b);
  
 text("k = "+k, 190, 30); 
  
  text("q = "+q, 250, 30); 

sketch(k,q,110,pos2,a);

text("k = "+k, 190, 60); 
  
  text("q = "+q, 250, 60);
sketch(k,q,100,pos3,a);
text("k = "+k, 190, 90); 
  text("q = "+q, 190, 90);
sketch(k,q,190,pos4,a);
text("k = "+k, 190, 120); 
  
  
 
}

}

void sketch(float kk, float qq, float z, float O,int vc)
{
  stroke(255,0,0);
  float c=z*cos(O);
  float d=z*sin(O);
  if(vc<410)
  {
    line (kk,qq,kk-c,qq-d);
    k=kk-c;
    q=qq-d;
  }
  else
  {
    
    
    line (kk,qq,kk+c,qq-d);
    k=kk+c;
    q=qq-d;
    text("vvvvv",200,200);
  }
  
  stroke(0);
  
}


void d ()
{
  
line(430,370,430,240);
line(410,370,410,240);

line(430,480,430,380);
line(410,480,410,380);

line(430,600,430,490);
line(410,600,410,490);
 
}

void c ( float u ,float r , int vc)
{
  if (vc <=600)
  {
    float z;
  float pos=0;
  float Q=0 ;
    float Y ;
    float B;

    float one =42.3;
    float two;
    float three=47.7;
    float five;
r =r/10;
      z =r ;
           text("z = "+z,800 ,20);
      Q = u*180/PI ;


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
 

              if(pos1>180)
              {
               pos2=180-B-Q;
                 pos4=180-(Y-90);

                  if(pos<=pos1)
                  {
                    text("pos1 = "+pos1,1000 ,30);
                  }
                  if(pos<=pos2)
                  {
                     text("pos2 = "+pos2,1000 ,60);
                  }
                  if(pos<=pos4)
                  {
                    text("pos4 = "+pos4,1000 ,90);
                  }
                }
               else   if((pos1<=180))
               {
                  pos2=(B+Q);
                  pos4=(Y-90);

                  if(pos<=pos1)
                  {
                    text("pos1 = "+pos1,1000 ,30);
                  }
                  if(pos<=pos2)
                  {
                     text("pos2 = "+pos2,1000 ,60);
                  }
                  if(pos<=pos4)
                  {
                    text("pos4 = "+pos4,1000 ,90);
                    text("pos3 = "+pos3,1000 ,500);
                  }
               }
                pos4=(pos2+pos4+90)-180;
  pos2=pos2*PI/180;
  pos4=pos4*PI/180;
  pos3=pos2;
 
            }
            
            
           else if(z>=12.5 && z<=28)
            {
               E=(z*z)+(14.8*14.8)-(19*19);
               E=E/(2*14.8*z);
                E=acos(E)*(180/PI);
                
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
                    text("pos1 = "+pos1,1000 ,30);
                  }
                  if(pos<=pos2)
                  {
                     text("pos2 = "+pos2,1000 ,60);
                  }
                  if(pos<=pos4)
                  {
                    text("pos4 = "+pos4,1000 ,90);
                  }
                
              }
              else   if((pos1<=180))
              {
                 pos3=180;
                 pos2=one+two+Q;
                  pos4=three+five-90;
                  if(pos<=pos1)
                  {
                    text("pos1 = "+pos1,1000 ,30);
                  }
                  if(pos<=pos2)
                  {
                     text("pos2 = "+pos2,1000 ,60);
                  }
                  if(pos<=pos4)
                  {
                    text("pos4 = "+pos4,1000 ,90);
                  }
                
                }
                }
                 else
                    text("error",1000 ,90);


 pos3=90-(180-pos2);
        pos4=pos4-(90-pos3);
         pos2=pos2*PI/180;
  pos4=pos4*PI/180;
   pos3=pos3*PI/180;

        }
        
        
            
            
            
      }
  }     
}
