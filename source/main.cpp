#include<cstdio>
#include<cstdlib>
#include<cstring>
#include"../include/riff.h"
#include"../include/riffeffect.h" 
#include"../include/id3toriff.h"
#include"../include/rifftoid3.h"
#include"../include/getclock.h"

using namespace std;

RIFF res,res1;

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
            int Year,Month,Day,Hour,Minute,Second;
            Year=GetYear();
            Month=GetMonth();
            Day=GetDay();
            Hour=GetHour();
            Minute=GetMinute();
            Second=GetSecond();
            char Order[100];
            sprintf(Order,"copy audio\\output.wav audio\\oldversions\\output_%d_%d_%d_%d_%d_%d.wav",Year,Month,Day,Hour,Minute,Second);
            system(Order);
        }
    switch(Mode)
    {
        case 0:
            system("mkdir audio\\oldversions");
            Converter(0);
            Reset(&res,0);
            break;

        case 1:
            system("audio\\output.wav");
            break;

        case 2:
            Reset(&res,2);
            EditVoice(&res,Begin,End,Arg);
            break;

        case 3:
            Reset(&res,2);
            Reverse(&res,Begin,End);
            break;

        case 4:
            Reset(&res,2);
            CutOff(&res,Begin,End);
            break;

        case 5:
            Reset(&res,2);
            Converter(1);
            Reset(&res1,1);
            if(res.SampleRate!=res1.SampleRate)
                res.SampleRate>res1.SampleRate?RaiseSample(&res1,res.SampleRate):LowerSample(&res1,res.SampleRate);
            Merge(&res,&res1,Location,Begin,End);
            remove("audio\\res1.wav");
            break;

        case 6: 
            Reset(&res,2);
            CutChannel(&res,Begin,End,Arg);
            break;

        case 7:        
            Reset(&res,2);
            Accelerate(&res,Begin,End,Arg);
            break;

        case 8:        
            Reset(&res,2);
            Moderate(&res,Begin,End,Arg);
            break;

        case 9:
            Reset(&res,2);
            EnvironmentEffect(&res,Begin,End,Arg);
            break;  

        case 10:
            Reset(&res,2);
            Converter(1);
            Reset(&res1,1);
            if(res.SampleRate!=res1.SampleRate)
                res.SampleRate>res1.SampleRate?RaiseSample(&res1,res.SampleRate):LowerSample(&res1,res.SampleRate);
            Combine(&res,&res1,Location,Begin,End);
            remove("audio\\res1.wav");
            break;   

        case 11:
            Reset(&res,2);
            RaiseTone(&res,Begin,End,Arg);
            break;  
 
        case 12:
            Reset(&res,2);
            ModeratePro(&res,Begin,End,Arg);
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
