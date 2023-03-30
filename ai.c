////////////////////////////////////////
//
//	File : ai.c
//	CoSpace Robot
//	Version 1.0.0
//	OCT 1 2021
//	Copyright (C) 2021 CoSpace Robot. All Rights Reserved
//
//////////////////////////////////////
//
// ONLY C Code can be compiled.
//
/////////////////////////////////////

#define CsBot_AI_H//DO NOT delete this line
#ifndef CSBOT_REAL
#include <windows.h>
#include <stdio.h>
#include <math.h>
#define DLL_EXPORT extern __declspec(dllexport)
#define false 0
#define true 1
#endif
//The robot ID : six chars unique CID.
//Find it from your CoSpace Robot label or CoSpace program download GUI.
//Don't write the below line into two lines or more lines.
char AI_MyID[6] = {'1','2','3','4','5','6'};

int Duration = 0;
int SuperDuration = 0;
int bGameEnd = false;
int CurAction = -1;
int CurGame = 0;
int SuperObj_Num = 0;
int SuperObj_X = 0;
int SuperObj_Y = 0;
int Teleport = 0;
int LoadedObjects = 0;
int US_Front = 0;
int US_Left = 0;
int US_Right = 0;
int CSLeft_R = 0;
int CSLeft_G = 0;
int CSLeft_B = 0;
int CSRight_R = 0;
int CSRight_G = 0;
int CSRight_B = 0;
int PositionX = 0;
int PositionY = 0;
int TM_State = 0;
int Compass = 0;
int Time = 0;
int WheelLeft = 0;
int WheelRight = 0;
int LED_1 = 0;
int MyState = 0;
int AI_TeamID = 1;   //Robot Team ID. 1:Blue Ream; 2:Red Team.
int MySMS; //A integer value which you want to send to the other robot.
           //In Super Team mode, you can use this value to inform your another robot of your status.
           //In Indiviual Mode, you should keep this value to 0.  

//The following three variables save the information of the other robot.
int OtherRob_SMS; //Keep the recieved value of the other robot MySMS value.
            //In Super Team mode, this value is sent by your another robot.
            //In Indiviual Mode, this value has no meaning.
int OtherRob_PositionX;//The X coordinate of the other robot. 
int OtherRob_PositionY;//The Y coordinate of the other robot. 

//The following four variables keep the information of the last state-changed object.
int ObjState;    //The state (0: Disappear; 1:Appear.) of the last state changed object.
int ObjPositionX;//The X coordinate of the last state-changed object.
int ObjPositionY;//The Y coordinate of the last state-changed object.
int ObjDuration; //The duration(seconds) of the object maintains the current state;
//------------------------------------------
int speed=8;     //10
int AOR;
//int tan;
#define CsBot_AI_C//DO NOT delete this line

DLL_EXPORT void SetGameID(int GameID)
{
    if(CurGame != GameID) LoadedObjects = 0;
    CurGame = GameID;
    bGameEnd = 0;
}


DLL_EXPORT void SetTeamID(int TeamID)
{
    AI_TeamID = TeamID;
}

DLL_EXPORT int GetGameID()
{
    return CurGame;
}

//Only Used by CsBot Dance Platform
DLL_EXPORT int IsGameEnd()
{
    return bGameEnd;
}

#ifndef CSBOT_REAL

char info[3000];
DLL_EXPORT char* GetDebugInfo()
{
    sprintf(info, "AOR=%d;Duration=%d;SuperDuration=%d;bGameEnd=%d;CurAction=%d;CurGame=%d;SuperObj_Num=%d;SuperObj_X=%d;SuperObj_Y=%d;Teleport=%d;LoadedObjects=%d;US_Front=%d;US_Left=%d;US_Right=%d;CSLeft_R=%d;CSLeft_G=%d;CSLeft_B=%d;CSRight_R=%d;CSRight_G=%d;CSRight_B=%d;PositionX=%d;PositionY=%d;TM_State=%d;Compass=%d;Time=%d;WheelLeft=%d;WheelRight=%d;LED_1=%d;MyState=%d;tan;",AOR,Duration,SuperDuration,bGameEnd,CurAction,CurGame,SuperObj_Num,SuperObj_X,SuperObj_Y,Teleport,LoadedObjects,US_Front,US_Left,US_Right,CSLeft_R,CSLeft_G,CSLeft_B,CSRight_R,CSRight_G,CSRight_B,PositionX,PositionY,TM_State,Compass,Time,WheelLeft,WheelRight,LED_1,MyState,tan);
    return info;
}
 
DLL_EXPORT char* GetTeamName()
{
    return "VIANA";
}

DLL_EXPORT int GetCurAction()
{
    return CurAction;
}

//Only Used by CsBot Rescue Platform
DLL_EXPORT int GetTeleport()
{
    return Teleport;
}

//Only Used by CsBot Rescue Platform
DLL_EXPORT void SetSuperObj(int X, int Y, int num)
{
    SuperObj_X = X;
    SuperObj_Y = Y;
    SuperObj_Num = num;
}
//Only Used by CsBot Rescue Platform
DLL_EXPORT void GetSuperObj(int *X, int *Y, int *num)
{
    *X = SuperObj_X;
    *Y = SuperObj_Y;
    *num = SuperObj_Num;
}
//Used by CoSpace Rescue Simulation. 
///Called each time frame by CoSpaceRobot Studio to update the other robot information.
DLL_EXPORT void UpdateRobInfo(int sms, int X, int Y)
{
	OtherRob_SMS = sms;
	OtherRob_PositionX = X;
	OtherRob_PositionY = Y;
}

//Used by CsBot Rescue Platform
DLL_EXPORT void UpdateObjectInfo(int X, int Y, int state, int duration)
{
	ObjState = state;
	ObjPositionX = X;
	ObjPositionY = Y;
	ObjDuration = duration;
}
DLL_EXPORT int GetMySMS()
{
	return MySMS;
}

#endif ////CSBOT_REAL

DLL_EXPORT void SetDataAI(volatile int* packet, volatile int *AI_IN)
{

    int sum = 0;

    US_Front = AI_IN[0]; packet[0] = US_Front; sum += US_Front;
    US_Left = AI_IN[1]; packet[1] = US_Left; sum += US_Left;
    US_Right = AI_IN[2]; packet[2] = US_Right; sum += US_Right;
    CSLeft_R = AI_IN[3]; packet[3] = CSLeft_R; sum += CSLeft_R;
    CSLeft_G = AI_IN[4]; packet[4] = CSLeft_G; sum += CSLeft_G;
    CSLeft_B = AI_IN[5]; packet[5] = CSLeft_B; sum += CSLeft_B;
    CSRight_R = AI_IN[6]; packet[6] = CSRight_R; sum += CSRight_R;
    CSRight_G = AI_IN[7]; packet[7] = CSRight_G; sum += CSRight_G;
    CSRight_B = AI_IN[8]; packet[8] = CSRight_B; sum += CSRight_B;
    PositionX = AI_IN[9]; packet[9] = PositionX; sum += PositionX;
    PositionY = AI_IN[10]; packet[10] = PositionY; sum += PositionY;
    TM_State = AI_IN[11]; packet[11] = TM_State; sum += TM_State;
    Compass = AI_IN[12]; packet[12] = Compass; sum += Compass;
    Time = AI_IN[13]; packet[13] = Time; sum += Time;
    packet[14] = sum;

}
DLL_EXPORT void GetCommand(int *AI_OUT)
{
    AI_OUT[0] = WheelLeft;
    AI_OUT[1] = WheelRight;
    AI_OUT[2] = LED_1;
    AI_OUT[3] = MyState;
}
void TurnTo(int curRot, int targetRot)
{
    int p0 = targetRot;
    int p3 = (targetRot + 3) % 360;
    int p15 = (targetRot + 15) % 360;
    int n3 = (targetRot - 3 + 360) % 360;
    int n15 = (targetRot - 15 + 360) % 360;
    int p180 = (targetRot + 180) % 360;
    int l = 0, r = 0;
    Duration = 6;
    //Within(-3,+3)deg, stop turing.
    l = n3; r = p3;
    if ((l < r && curRot > l && curRot < r) ||
    (l > r && (curRot > l || curRot < r)))
    {
        WheelLeft = 0;
        WheelRight = 0;
        Duration = 0;
        return;
    }
    //Within[3,15]deg,Turn Slowly
    l = p3; r = p15;
    if ((l < r && curRot >= l && curRot <= r) ||
        (l > r && (curRot >= l || curRot <= r)))
    {
        WheelLeft = 10;
        WheelRight = -10;
        return;
    }
    //Within[15,180]deg,Turn Faast
    l = p15; r = p180;
    if ((l < r && curRot >= l && curRot <= r) ||
       (l > r && (curRot >= l || curRot <= r)))
    {
        WheelLeft = 30;
        WheelRight = -30;
        return;
    }
    //Within[-15,-3]deg,Turn Slowly
    l = n15; r = n3;
    if ((l < r && curRot >= l && curRot <= r) ||
    (l > r && (curRot >= l || curRot <= r)))
    {
        WheelLeft = -10;
        WheelRight = 10;
        return;
    }
    //Within[-180,-15]deg,Turn Fast
    l = p180; r = n15;
    if ((l < r && curRot >= l && curRot <= r) ||
    (l > r && (curRot >= l || curRot <= r)))
    {
        WheelLeft = -30;
        WheelRight = 30;
        return;
    }
}
//--------
int F;
int g;
//--------
int MOTORS(int r ,int l , int led)
{
    WheelLeft=l*speed;  
    WheelRight=r*speed;
    LED_1=led;
}
int Ae(int angle1)
{
    int a = angle1 - Compass;            //
    int b = (angle1 - (360 - Compass))*(-1);         //
    if (a>=b)
    {
        return 0;
    }
    else if (b>a)
    {
        return 1;
    }
}
void compass(int angle2)
{
    //int gahat = Ae(angle);
    if (!((Compass <= angle2 + 3) && (Compass >= angle2 - 3)))
    {
        if (Ae(angle2)== 1)
        {
            MOTORS(1,-1,0); 
        }
        else if (Ae(angle2)==0)
        {
            MOTORS(-1,1,0);
        }
    }
    else if ((Compass <= angle2 + 3) && (Compass >= angle2 - 3))
    {
        MOTORS(0,0,2);
    }
}
/*void Am(int LocitionX,int LocitionY)
{
    int LCV_X=LocitionX-PositionX;
    int LCV_Y=LocitionY-PositionY;
    if (LCV_X > 0 && LCV_Y > 0)
    {
        compass((LCV_Y/LCV_X)*180/3.14);
    }
    else if (LCV_X < 0 && LCV_Y > 0)
    {
        compass((LCV_Y*(-1)/LCV_X)*180/3.14);
    }
    else if (LCV_X < 0 && LCV_Y < 0)
    {
        compass((LCV_Y/LCV_X)*180/3.14);
    }
    else if (LCV_X > 0 && LCV_Y < 0)
    {
        compass(LCV_Y/LCV_X*(-1)*180/3.14);
    }
}
int amotors()
    int baza us=7; 
    if (US_Left<=baza us || US_Right<=baze us || US_Front <=baza us - 1)
    {
        if (US_Left < US_Right)
        {
            if (US_Left<US_Right && Compass<=90)
            {
                int ac=Compass-90;
                compass=ac+270;
        }
        }
    }*/
//_________________________________________________/GAME 0\__________________________________________________
void Game0()
{ 
    if(Duration>0)
    {
        Duration--;
    }
    //-----------------------------------------------[COLER SENSOR]----------------------------------------
    else if(CSRight_R>240 && CSRight_G<10 && CSRight_B<10 && LoadedObjects<6)//RED RIGHT 0
    {
        Duration=55;
        CurAction=7;
    }
    else if(CSLeft_R>240 && CSLeft_G<10 && CSLeft_B<10 && LoadedObjects<6)//RED LEFT 0
    {
        Duration=55;
        CurAction=7;
    }
    else if(CSRight_R<=10 && CSRight_G==255 && CSRight_B==255 && LoadedObjects<6)//CYAN RIGHT 0
    {
        Duration=55;
        CurAction=7;
    }
    else if(CSLeft_R<=10 && CSLeft_G==255 && CSLeft_B==255 && LoadedObjects<6)//CYAN LEFT 0
    {
        Duration=55;
        CurAction=7;
    }
    else if(CSRight_R<=10 && CSRight_G<=10 && CSRight_B<=10 && LoadedObjects<6)//BLACK RIGHT 0
    {
        Duration=55;
        CurAction=7;
    }
    else if(CSLeft_R<=10 && CSLeft_G<=10 && CSLeft_B<=10 && LoadedObjects<6)//BLACK LEFT 0
    {
        Duration=55;
        CurAction=7;
    }
    else if(CSRight_R>240 && CSRight_G>240 && CSRight_B<=150 && CSRight_B<115)//YELLOW TRAP RIGHT 0
    {
        if(LoadedObjects==0)
        {
            Duration=0;
            CurAction=1;
        }
        else if(LoadedObjects>0)
        {
            CurAction=10;
            Duration=7;
        }
    }
    else if(CSLeft_R>240 && CSLeft_G>240 && CSLeft_B<=150 && CSLeft_B<115)//YELLOW TRAP Left 0
    {
        
        if(LoadedObjects==0)
        {
            Duration=0;
            CurAction=1;
        }
        else if(LoadedObjects>0)
        {
            CurAction=9;
            Duration=7;
        }
    }
    else if(LoadedObjects>0 && CSRight_R>=235 && CSRight_G<=165 && CSRight_B<=70 && CSLeft_R>=235 && CSLeft_G<=165 && CSLeft_B<=70  )//ORENGE 0 
    {  
        
        Duration=54;
        CurAction=8;
        
    }
    else if(LoadedObjects>0 && CSLeft_R>=235 && CSLeft_G<=165 && CSLeft_B<=70  )//ORENGE 1 
    {   
        // Duration=2;
        CurAction=11;
    }
    else if(LoadedObjects>0 && CSRight_R>=235 && CSRight_G<=165 && CSRight_B<=70)//ORENGE 1 
    {   
        // Duration=2;
        CurAction=12;
    }
    
//_________________________________________________/US SENSOR\____________________________________________ 
    else if(US_Left != US_Right && US_Front>US_Left && US_Front>US_Right && US_Left<=2 && US_Right<=2)
    {
        Duration=0;
        if(US_Left<US_Right)
        {
            CurAction=6;
        } 
        else if(US_Left>US_Right)
        {
            CurAction=5;
        } 
    }
    else if((US_Left <= 8) && (US_Left < US_Right) && (US_Left >= 3))
    {
        Duration=0;
        CurAction=3;     
    }
    else if((US_Right <= 8) && (US_Right < US_Left) && (US_Right >= 3))
    {   
        Duration=0;
        CurAction=2;
    } 
    else if((US_Front <= 7) && (US_Right < US_Left))
    {
        Duration=0;
        CurAction=2;
    }
    else if((US_Front <= 7) && (US_Right > US_Left))
    {
        Duration=0;
        CurAction=3;
    }
    else if((US_Front <=7)&&(US_Left == US_Right)) 
    {
        Duration=0;
        CurAction=3;
    }
    else if(US_Front>7 && (US_Front!=255))
    {
        Duration=0;
        CurAction=1;
    }
    else if(US_Front==255||US_Left==255||US_Right==255)
    {
        Duration=0;
        CurAction=4;
    }

//-------------------------------------------------SWITCH_CASE--------------------------------------------
switch(CurAction)
{
    case 1:
        MOTORS(10,10,0);
        MyState=0;
        break;
    case 2:
        MOTORS(10,-10,0);
        MyState=0;
        break;
    case 3:
        MOTORS(-10,10,0);
        MyState=0;
        break;
    case 4:
        MOTORS(-10,-10,0);
        MyState=0;
        break;
    case 5:
        MOTORS(1,0,0);
        MyState=0;
        break;
    case 6:
        MOTORS(0,1,0);
        MyState=0;
        break;
    case 7:
        MOTORS(0,0,1);
        MyState=0;
        if(Duration == 1)
        {
            LoadedObjects++;
            MOTORS(5,5,0);
        }
        break;
    case 8:
        MOTORS(0,0,2);
        MyState=0;
        if(Duration == 1) LoadedObjects = 0;
        break;
    case 9:
        MOTORS(-10,-4,0);
        MyState=0;
        break;
    case 10:
        MOTORS(-4,-10,0);
        MyState=0;
        break;
    case 11:
        MOTORS(8,0,0);
        MyState=0;
        break;
    case 12:
        MOTORS(0,8,0);
        MyState=0;
        break;
    default:
        break;
}
}
//________________________________________________END OF THE GAME 0_______________________________________
//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\/GAME 1\////////////////////////////////////////////
void Game1()
{   
    if(Duration>0)          
    {
        Duration--;
    }
    /*else if(LoadedObjects==6 && save1[1]!=0)
    {
        if(save2[0]==0)
        {
            LED_1=0;
        }
        else if (save2[1]!=0)
        {
            int a =(save1[0]*save1[0])+(save1[1]*save1[1]);
            int b =(save2[0]*save2[0])+(save2[1]*save2[1]);
            if(a>b)
            {
                LED_1=2;
            }
            else if(b>a)
            {
                LED_1=1;
            }
            else if(a==b)
            {
                LED_1=2;
            }
        }
    }*/
//-----------------------------------------------[COLER SENSOR]---------------------------------------------------
    else if(CSRight_R>240 && CSRight_G<10 && CSRight_B<10 && LoadedObjects<6)//RED RIGHT 1
    {
        Duration=55;
        CurAction=7;
    }
    else if(CSLeft_R>240 && CSLeft_G<10 && CSLeft_B<10 && LoadedObjects<6)//RED LEFT 1
    {
        Duration=55;
        CurAction=7;
    }
    else if(CSRight_R<=10 && CSRight_G==255 && CSRight_B==255 && LoadedObjects<6)//CYAN RIGHT 1
    {
        Duration=55;
        CurAction=7;
    }
    else if(CSLeft_R<=10 && CSLeft_G==255 && CSLeft_B==255 && LoadedObjects<6)//CYAN LEFT 1
    {
        Duration=55;
        CurAction=7;
    }
    else if(CSRight_R<=10 && CSRight_G<=10 && CSRight_B<=10 && LoadedObjects<6)//BLACK RIGHT 1
    {
        Duration=55;
        CurAction=7;
    }
    else if(CSLeft_R<=10 && CSLeft_G<=10 && CSLeft_B<=10 && LoadedObjects<6)//BLACK LEFT 1
    {
        Duration=55;
        CurAction=7;
    }
    else if(PositionY == 0 && PositionX == 0)//koor    
    {
        CurAction=9;
        Duration=7;   
    }
    else if(CSRight_R>240 && CSRight_G>240 && CSRight_B<=150 && CSRight_B<115)//YELLOW TRAP RIGHT 1
    {   
        if(LoadedObjects==0)
        {
            Duration=0;
            CurAction=1;
        }
        else if(LoadedObjects>0)
        {
            CurAction=10;
            Duration=7;
        }
    }
    else if(CSLeft_R>240 && CSLeft_G>240 && CSLeft_B<=150 && CSLeft_B<115)//YELLOW TRAP Left 1
    {
        if(LoadedObjects==0)
        {
            Duration=0;
            CurAction=1;
        }
        else if(LoadedObjects>0)
        {
            CurAction=9;
            Duration=7;
        }
    }
    else if(LoadedObjects>0 && CSRight_R>=235 && CSRight_G<=165 && CSRight_B<=70 && CSLeft_R>=235 && CSLeft_G<=165 && CSLeft_B<=70  )//ORENGE 1 
    {   
        Duration=54;
        CurAction=8;
        //if(PositionX!=0 && PositionY!=0)
        //{
        //    int save1[2]={PositionX,PositionY};
        //}
        //else if (!(PositionX <= save1[0]+10) && !(PositionX >= save1[0]-10) || !(PositionY <= save1[1]+10) && !(PositionY >= save1[1]-10) && PositionX!=0 && PositionY!=0 )
        //{
        //    int save2[2]={PositionX,PositionY};
        //}
    }
    else if(LoadedObjects>0 && CSLeft_R>=235 && CSLeft_G<=165 && CSLeft_B<=70  )//ORENGE 1 
    {  
        CurAction=11;
    }
    else if(LoadedObjects>0 && CSRight_R>=235 && CSRight_G<=165 && CSRight_B<=70)//ORENGE 1 
    {   
        CurAction=12;
    }
//-------------------------------------------------POSITION(Y)---------------------------------------------
    else if (PositionX<=10 && Compass>=180)
    {
        Duration=3;
        CurAction=1;
    }
    else if(PositionX>=340 && Compass<=180)
    {
        Duration=3;
        CurAction=1;
    }
    else if (PositionY<=10 && Compass>=270 || PositionY<=10 && Compass<=90)
    {
        Duration=3;
        CurAction=1;
    }    
    else if(PositionY>=260 && Compass>=90 && Compass<=270)
    {   
        Duration=3;
        CurAction=1;
    }
    else if(PositionY<=10  || PositionY>=260 || PositionX<=10  || PositionX>=340 && PositionX!=PositionY)
    {
        Duration=4;
        CurAction=4;
        Duration=2;
        CurAction=9;
    }
    // else if (PositionX==PositionY && PositionX==0 && PositionY==0)
    // {
    //     CurAction=1;
    // }
//_________________________________________________/US SENSOR\____________________________________________
    // else if(US_Left != US_Right && US_Front>US_Left && US_Front>US_Right && US_Left<=2 && US_Right<=2)
    // {
    //     Duration=0;
    //     if(US_Left<US_Right)
    //     {
    //         CurAction=6;
    //     } 
    //     else if(US_Left>US_Right)
    //     {
    //         CurAction=5;
    //     } 
    // }
    else if(US_Left<=7 && (US_Left<US_Right) && !(PositionY<=10||PositionY>=260||PositionX<=10||PositionX>=340))
    {
        Duration=0;
        CurAction=3;     
    }
    else if(US_Right<=7 && (US_Right<US_Left) && !(PositionY<=10||PositionY>=260||PositionX<=10||PositionX>=340))
    {   
        Duration=0;
        CurAction=2;
    } 
    else if(US_Front<=6 && (US_Right<US_Left) && !(PositionY<=10||PositionY>=260||PositionX<=10||PositionX>=340))
    {
        Duration=0;
        CurAction=2;
    }
    else if(US_Front <=6 && (US_Right>US_Left) && !(PositionY<=10||PositionY>=260||PositionX<=10||PositionX>=340))
    {
        Duration=0;
        CurAction=3;
    }
    else if(US_Front<=6 && (US_Left==US_Right) && !(PositionY<=10||PositionY>=260||PositionX<=10||PositionX>=340)) 
    {
        Duration=0;
        CurAction=3;
    }
    else if(US_Front>6 && !(PositionY<=10||PositionY>=260||PositionX<=10||PositionX>=340))
    {
        Duration=0;
        CurAction=1;
    }
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|SAVE THE LOCITION|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-

//-------------------------------------------------SWITCH_CASE--------------------------------------------
switch(CurAction)
{
    case 1:
        MOTORS(10,10,0);
        MyState=0;
        break;
    case 2:
        MOTORS(10,-10,0);
        MyState=0;
        break;
    case 3:
        MOTORS(-10,10,0);
        MyState=0;
        break;
    case 4:
        MOTORS(-10,-10,0);
        MyState=0;
        break;
    case 5:
        MOTORS(1,0,0);
        MyState=0;
        break;
    case 6:
        MOTORS(0,1,0);
        MyState=0;
        break;
    case 7:
        MOTORS(0,0,1);
        MyState=0;
        if(Duration == 1)
        {
            LoadedObjects++;
            MOTORS(5,5,0);
        }
        break;
    case 8:
        MOTORS(0,0,2);
        MyState=0;
        if(Duration == 1) LoadedObjects = 0;
        break;
    case 9:
        MOTORS(-10,-2,0);
        MyState=0;
        break;
    case 10:
        MOTORS(-4,-10,0);
        MyState=0;
        break;
    case 11:
        MOTORS(8,1,0);
        MyState=0;
        break;
    case 12:
        MOTORS(1,8,0);
        MyState=0;
        break; 
    default:
        break;
}
}
//_______________________________________________\END OF GAME1/_______________________________________________
DLL_EXPORT void OnTimer()
{
    switch (CurGame)
    {
        case 9:
            break;
        case 10:
            WheelLeft=0;
            WheelRight=0;
            LED_1=0;
            MyState=0;
            break;
        case 0:
            Game0();
            break;
        case 1:
            Game1();
            break;
        default:
            break;
    }
}