#include<cstdio>
#include<cstdlib>
#include<cstring>
#include"include/riff.h"
#include"include/riffeffect.h" 
#include"include/getclock.h"
#include"include/id3toriff.h"
#include"include/rifftoid3.h"

using namespace std;

RIFF res,res1;

int main()
{
    printf("Loading resource file...\n");
    Converter(0);
    Reset(&res,0);
    printf("Done.\n");
    int arg0,arg1,arg2,arg3,arg4,arg6,arg7;
    double arg5,Begin,End,Location;
    char Order[100];
    int Year[1000],Month[1000],Day[1000],Hour[1000],Minute[1000],Second[1000],Top=0;
    system("mkdir OldVersions");
    while(1)
    {
        system("cls");
        printf("=========================================\n");
        printf("Welcome to HoneyTuner.\n");
        printf("Task 0:Rebuild MP3 file and exit the program.\n");
        printf("Task 1:Print information of file.\n");
        printf("Task 2:Change the voice of a part.\n");
        printf("Task 3:Reverse a part.\n");
        printf("Task 4:Cut off a part.\n");
        printf("Task 5:Merge a part.\n");
        printf("Task 6:Cut one channel.\n");
        printf("Task 7:Accelerate the music.\n");
        printf("Task 8:Moderate the music.\n");
        printf("Task 9:Add an environment effect.\n");
        printf("Task 10:Combine a part.\n");
        printf("Task 11:Raise the tone of a part.\n");
        printf("Task 12:Moderate the music and keep the tone.\n");
        printf("Task 13:Raise the samplerate.\n");
        printf("Task 14:Lower the samplerate.\n");
        printf("Task 666:Discard last change.\n");
        printf("Task 999:Discard all changes.\n");
        printf("To be continued...\n");
        printf("=========================================\n");
        printf("Please choose a task and press the Enter key:");
        scanf("%d",&arg0);
        if(arg0>=2&&arg0<=100)
        {
            Year[++Top]=GetYear();
            Month[Top]=GetMonth();
            Day[Top]=GetDay();
            Hour[Top]=GetHour();
            Minute[Top]=GetMinute();
            Second[Top]=GetSecond();
            sprintf(Order,"copy output.wav OldVersions\\Ver_%d_%d_%d_%d_%d_%d.wav",Year[Top],Month[Top],Day[Top],Hour[Top],Minute[Top],Second[Top]);
            system(Order);
        }
        system("cls");
        switch(arg0)
        {
            case 0:
                if(!transformer())
                {
                    printf("Failed:output.wav has been moved.\n");
                    break;
                }
                remove("output.wav");
                remove("res.wav");
                system("del /q OldVersions");
                system("rd OldVersions");
                system("pause");
                return 0;

            case 1:
                printf("Enter the args:");
                scanf("%d",&arg1);
                arg1?PutInfo(&res1):PutInfo(&res);
                break;

            case 2:
                printf("Enter the args:");
                scanf("%d%d%d%d%lf",&arg1,&arg2,&arg3,&arg4,&arg5);
                Begin=arg1*1.0+arg2/60.0;
                End=arg3*1.0+arg4/60.0;
                EditVoice(&res,Begin,End,arg5);
                break;

            case 3:
                printf("Enter the args:");
                scanf("%d%d%d%d",&arg1,&arg2,&arg3,&arg4); 
                Begin=arg1*1.0+arg2/60.0;
                End=arg3*1.0+arg4/60.0;
                Reverse(&res,Begin,End);
                break;

            case 4:
                printf("Enter the args:");
                scanf("%d%d%d%d",&arg1,&arg2,&arg3,&arg4);
                Begin=arg1*1.0+arg2/60.0;
                End=arg3*1.0+arg4/60.0;
                CutOff(&res,Begin,End);
                break;

            case 5:
                printf("Enter the args:");
                scanf("%d%d%d%d%d%d",&arg1,&arg2,&arg3,&arg4,&arg6,&arg7);
                Converter(1);
                Reset(&res1,1);
                if(res.SampleRate!=res1.SampleRate)
                    res.SampleRate>res1.SampleRate?LowerSample(&res,res1.SampleRate):RaiseSample(&res,res1.SampleRate);
                Begin=arg1*1.0+arg2/60.0;
                End=arg3*1.0+arg4/60.0;
                Location=arg6*1.0+arg7/60.0;
                Merge(&res,&res1,Location,Begin,End);
                break;

            case 6:
                printf("Enter the args:");
                scanf("%d%d%d%d%d",&arg1,&arg2,&arg3,&arg4,&arg6); 
                Begin=arg1*1.0+arg2/60.0;
                End=arg3*1.0+arg4/60.0;              
                CutChannel(&res,Begin,End,arg6);
                break;

            case 7:
                printf("Enter the args:");
                scanf("%d%d%d%d%d",&arg1,&arg2,&arg3,&arg4,&arg6);
                Begin=arg1*1.0+arg2/60.0;
                End=arg3*1.0+arg4/60.0;              
                Accelerate(&res,Begin,End,arg6);
                break;

            case 8:
                printf("Enter the args:");
                scanf("%d%d%d%d%d",&arg1,&arg2,&arg3,&arg4,&arg6);
                Begin=arg1*1.0+arg2/60.0;
                End=arg3*1.0+arg4/60.0;              
                Moderate(&res,Begin,End,arg6);
                break;

            case 9:
                printf("Enter the args:");
                scanf("%d%d%d%d%lf",&arg1,&arg2,&arg3,&arg4,&arg5);
                Begin=arg1*1.0+arg2/60.0;
                End=arg3*1.0+arg4/60.0;
                EnvironmentEffect(&res,Begin,End,arg5);
                break;  

            case 10:
                printf("Enter the args:");
                scanf("%d%d%d%d%d%d",&arg1,&arg2,&arg3,&arg4,&arg6,&arg7);
                Converter(1);
                Reset(&res1,1);
                if(res.SampleRate!=res1.SampleRate)
                    res.SampleRate>res1.SampleRate?LowerSample(&res,res1.SampleRate):RaiseSample(&res,res1.SampleRate);
                Begin=arg1*1.0+arg2/60.0;
                End=arg3*1.0+arg4/60.0;
                Location=arg6*1.0+arg7/60.0;
                Combine(&res,&res1,Location,Begin,End);
                break;   

            case 11:
                printf("Enter the args:");
                scanf("%d%d%d%d%d",&arg1,&arg2,&arg3,&arg4,&arg6);
                Begin=arg1*1.0+arg2/60.0;
                End=arg3*1.0+arg4/60.0;
                RaiseTone(&res,Begin,End,arg6);
                break;  
 
            case 12:
                printf("Enter the args:");
                scanf("%d%d%d%d%d",&arg1,&arg2,&arg3,&arg4,&arg6);
                if(arg6&1==1)
                {
                    printf("Invalid arg.Please select again.");
                    break;
                }
                Begin=arg1*1.0+arg2/60.0;
                End=arg3*1.0+arg4/60.0;
                ModeratePro(&res,Begin,End,arg6);
                break;

            case 13:
                printf("Enter the args:");
                scanf("%d",&arg1);
                if(arg1<=res.SampleRate)
                {
                    printf("Invalid arg.Please select again.");
                    break;
                }
                RaiseSample(&res,arg1);
                break;
            
            case 14:
                printf("Enter the args:");
                scanf("%d",&arg1);
                if(arg1>=res.SampleRate)  
                {
                    printf("Invalid arg.Please select again.");
                    break;
                }
                LowerSample(&res,arg1);
                break;

            case 666: 
                if(!Top)
                { 
                    printf("Invalid option.Please select again.\n");
                    break;
                }
                sprintf(Order,"copy OldVersions\\Ver_%d_%d_%d_%d_%d_%d.wav output.wav",Year[Top],Month[Top],Day[Top],Hour[Top],Minute[Top],Second[Top]);
                system(Order);
                sprintf(Order,"OldVersions\\Ver_%d_%d_%d_%d_%d_%d.wav",Year[Top],Month[Top],Day[Top],Hour[Top],Minute[Top],Second[Top]);
                remove(Order);
                --Top;
                break;

            case 999:
                Reset(&res,0);
                break;

            default:
                printf("Invalid option.Please select again.\n");
                break;   
        }
        system("pause");
    }
}
