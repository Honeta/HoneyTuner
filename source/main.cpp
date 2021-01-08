#include<cstdio>
#include<cstdlib>
#include<cstring>
#include"../include/riff.h"
#include"../include/riffeffect.h" 
#include"../include/id3toriff.h"
#include"../include/rifftoid3.h"
#include"../include/getclock.h"
#include"../include/getfile.h"

using namespace std;

RIFF Res,Res1;

void CreateVersion()
{
    int Year=GetYear(),
        Month=GetMonth(),
        Day=GetDay(),
        Hour=GetHour(),
        Minute=GetMinute(),
        Second=GetSecond();
    char Order[100];
    sprintf(Order,"copy audio\\output.wav audio\\oldversions\\output_%d_%d_%d_%d_%d_%d.wav",Year,Month,Day,Hour,Minute,Second);
    system(Order);
    return;
}

void Discard()
{
    char Order[100];
    const char *Last=LastFile("audio\\oldversions","wav");
    if(Last[0]!=' ')
    {
        sprintf(Order,"move audio\\oldversions\\%s audio\\output.wav",Last);
        system(Order);
    }     
    return;
}

int main()
{
    if(!freopen("audio\\honeyset.in","r",stdin))
        return 0;
    int Mode;
    double Begin,End,Location,Arg;
    fscanf(stdin,"%d%lf%lf%lf%lf",&Mode,&Begin,&End,&Location,&Arg);
    fclose(stdin);
    system("del /q audio\\honeyset.in");
    if(Mode>=2&&Mode<=100)
    {
        CreateVersion();
        Reset(&Res,2);
        if(End<=Begin||Begin<0||(Location==0&&End>Res.TotalTime))return 0;
    }
    switch(Mode)
    {
        case 0:
            system("mkdir audio\\oldversions");
            Converter(0);
            Reset(&Res,0);
            break;

        case 1:
            system("audio\\output.wav");
            break;

        case 2:
            EditVoice(&Res,Begin,End,Arg);
            break;

        case 3:
            Reverse(&Res,Begin,End);
            break;

        case 4:
            CutOff(&Res,Begin,End);
            break;

        case 5:
            Converter(1);
            Reset(&Res1,1);
            if(End>Res1.TotalTime||Location<0||Location>Res.TotalTime)
            {
                remove("audio\\res1.wav");
                break;
            }
            if(Res.SampleRate!=Res1.SampleRate)
                Res.SampleRate>Res1.SampleRate?RaiseSample(&Res1,Res.SampleRate):LowerSample(&Res1,Res.SampleRate);
            Merge(&Res,&Res1,Location,Begin,End);
            break;

        case 6: 
            CutChannel(&Res,Begin,End,Arg);
            break;

        case 7:        
            Accelerate(&Res,Begin,End,Arg);
            break;

        case 8:        
            Moderate(&Res,Begin,End,Arg);
            break;

        case 9:
            EnvironmentEffect(&Res,Begin,End,Arg);
            break;  

        case 10:
            Converter(1);
            Reset(&Res1,1);
            if(End>Res1.TotalTime||Location<0||Location>Res.TotalTime)
            {
                remove("audio\\res1.wav");
                break;
            }
            if(Res.SampleRate!=Res1.SampleRate)
                Res.SampleRate>Res1.SampleRate?RaiseSample(&Res1,Res.SampleRate):LowerSample(&Res1,Res.SampleRate);
            Combine(&Res,&Res1,Location,Begin,End);
            break;   

        case 11:
            RaiseTone(&Res,Begin,End,Arg);
            break;  
 
        case 12:
            ModeratePro(&Res,Begin,End,Arg);
            break;

        case 13:
            Repeat(&Res,Location,Begin,End);
            break;

        case 14:
            Transfer(&Res,Location,Begin,End);
            break;

        case 666:
            Discard();      
            break;

        case 999:
            transformer();
            remove("audio\\output.wav");
            system("del /q audio\\OldVersions");
            system("rd audio\\OldVersions");
            break;

        default:
            break;   
    }
    return 0;
}
