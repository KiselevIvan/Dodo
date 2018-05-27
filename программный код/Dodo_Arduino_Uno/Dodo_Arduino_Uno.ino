#include <AccelStepper.h>
#include <AFMotor.h>
#include <Servo.h>

#define angle 4 //шаг поворота камеры
#define del 40 //задержка при повороте камеры
#define motorMAXSpeed 230.0 //скорость вращения двигателей    
#define stepperDistance 100 //Количество шагов на одну команду
#define AngleTurn 15 //Угол поворота робота на одну команду
#define maxMouseX 100 //Максимальное значение координаты Х указателя мыши
#define minMouseX 0  //Минимальное значение координаты Х указателя мыши
#define maxMouseY 100  //Максимальное значение координаты У указателя мыши
#define minMouseY 0  //Минимальное значение координаты У указателя мыши
#define maxCamXLeft 170 //Максимальный угол поворота камеры (влево)
#define minCamXRight 0  //Минимальный угол поворота камеры (вправо)
#define maxCamY  120 //Максимальный угол поворота камеры (ввех)
#define minCamY  68 //Минимальный угол поворота камеры (вниз)
Servo servox;
Servo servoy;

AF_Stepper motorL(200, 2);
AF_Stepper motorR(200, 1);

void forwardstepL() {  
  motorL.onestep(FORWARD, SINGLE);
}
void backwardstepL() {  
  motorL.onestep(BACKWARD, SINGLE);
}

void forwardstepR() {  
  motorR.onestep(FORWARD, SINGLE);
}
void backwardstepR() {  
  motorR.onestep(BACKWARD, SINGLE);
}

AccelStepper stepperL(forwardstepL, backwardstepL);
AccelStepper stepperR(forwardstepR, backwardstepR);
  
void setup() {
  Serial.begin(115200);
  servox.attach(9);
  servoy.attach(10);             
  servox.write(85);
  servoy.write(85);
  
  stepperL.setMaxSpeed(motorMAXSpeed);  
  stepperR.setMaxSpeed(motorMAXSpeed);  
}
byte camX=85, camY=85;//начальное положение камеры по центру
String command; //строка для команды по uart

void loop(){
  byte i=0;
  command="";
  
  delay(3); //задержка нужна, чтобы успеть принять комманду 

  while(Serial.available()>0)
  {
    int c=Serial.read();
    command+=(char)c;
  }
    
    CamCoor(command); //Управление камерой посредствам мыши
                                
      if (command.substring(0,9)=="camCenter")
                { 
                  servox.write(85);
                  servoy.write(85);
                  camX=85;
                  camY=85;    
                }
      
      else if (command.substring(0,7)=="camLeft")
                { i=servox.read();                   
                 while ((i<(camX+angle))&&(i<maxCamXLeft))
                 { 
                     servox.write(i);    
                     i=i+1;
                     delay(del);                        
                 }
                     camX=i; 
                }

      else if (command.substring(0,8)=="camRight")
                 { i=servox.read();
                  while ((i>(camX-angle))&&(i>minCamXRight))
                  { 
                       servox.write(i);    
                       i=i-1;
                       delay(del);         
                  }
                       camX=i;                       
               }
          
       else if (command.substring(0,5)=="camUp")
                { i=servoy.read();
                 while ((i<(camY+angle))&&(i<maxCamY))
                 { 
                     servoy.write(i);    
                     i=i+1;
                     delay(del);       
                 }
                     camY=i;                     
                }

      else if (command.substring(0,7)=="camDown")
               { i=servoy.read();
                 while ((i>(camY-angle))&&(i>minCamY))
                 { 
                       servoy.write(i);    
                       i=i-1;
                       delay(del);         
                 }
                       camY=i;
               }
      else if (command.substring(0,7)=="forward")
                {
                steppersMove(1,1); //движение двигателей 1-вперед, 0-назад для левого и правого соответственно
                }
      else if (command.substring(0,8)=="backward")
                {
                 steppersMove(0,0);
                }
       else if (command.substring(0,4)=="left")
                {
                 steppersMove(0,1);
                } 
        else if (command.substring(0,5)=="right")
                {
                 steppersMove(1,0);
                } 
}

  
  inline void CamCoor(String command) //Управление камерой посредствам мыши. Формат команд "coor<X>:<Y>"
{
  if(command.substring(0,4)=="coor")
     {
      static byte oldCoorY;
      register char X[4],Y[4],data[8];
      strcpy( data,"");      
      for (byte i=0;i<3;i++) //обнуление 
      {
        X[i]='\0';
        Y[i]='\0';
      }      
      command.substring(4).toCharArray(data,8);
      register byte k=0;
      while ((data[k]!=':')&&(data[k]!='\0'))
      {
        X[k]=data[k];
        k++;
      }
      if (data[k]==':')
      {
        int coorX,coorY;
        k++;
        register byte l=0;
        while (data[k]!='\0')
        {
        Y[l]=data[k];
        k++;
        l++;
        }
        coorX=atoi(X);
        coorY=atoi(Y); 
        coorX=map(coorX,minMouseX,maxMouseX,maxCamXLeft,minCamXRight);
        coorY=map(coorY,maxMouseY,minMouseY,minCamY,maxCamY);
            //проверка разницы для избежания ошибки, если команда дойдет не полностью + проверка диапазона, можно заменить Contrain()
        if ((abs(coorY-oldCoorY)<10)&&((coorX<=maxCamXLeft)&&(coorX>=minCamXRight))&&((coorY<=maxCamY)&&(coorY>=minCamY)))
        {        
        servox.write(coorX);
        camX=coorX;
        servoy.write(coorY);
        camY=coorY;        
        }
        oldCoorY=coorY;
      }
    }
 }

 inline void steppersMove(bool directionL,bool directionR)//движение двигателей 1-вперед, 0-назад. Левый и правый двигатель соответственно
 {  
   if (directionL)
   stepperL.setSpeed(motorMAXSpeed);
   else stepperL.setSpeed(-motorMAXSpeed);
   
   if (directionR)
   stepperR.setSpeed(motorMAXSpeed);
   else stepperR.setSpeed(-motorMAXSpeed);
   //если движение прямолинейное то делаем stepperDistance шагов,если поворот то переводим угол поворота AngleTurn в в количество шагов.
   while (abs(stepperL.currentPosition())< (((directionL==false) && (directionR==true)) || ((directionL==true) && (directionR==false))? AngleToStep(AngleTurn):stepperDistance))
    {     
     stepperL.runSpeed();
     stepperR.runSpeed();
    }
    stepperL.setCurrentPosition(0);
    stopen();//обесточиваем двигатели, чтобы избежать их нагрева и экономить заряд        
 }

int AngleToStep (double Angle)
{
  return (int)round(Angle*2.009565);
  /*((((Angle*PI)/180 )*11.75)/20.41)*200) 11.75 длинна окружности колес, 20.41 расстояние между колесами
  , 200 шагов на полный оборот
  */
} 

void stopen()
{
  motorR.release();
  motorL.release();
}
