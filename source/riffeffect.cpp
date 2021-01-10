#include<cstdio>
#include<cmath>
#include<cstdlib>
#include"../include/riff.h"

static FILE *fp_res,*fp_res1,*fp_out;

static short Temp[100000][2];

void EditVoice(RIFF *ptr,double Begin,double End,double Arg)
{
    system("copy audio\\output.wav audio\\temp.wav");
    fp_res=fopen("audio\\temp.wav","rb");
    PutFile(ptr);
    fp_out=fopen("audio\\output.wav","rb+");
    fseek(fp_out,ptr->Location,SEEK_SET);

    //Put Former Part
    fseek(fp_res,ptr->Location,SEEK_SET);
    for(int i=0;i<floor(ptr->SampleRate*1.0*Begin);i++)
        for(int j=0;j<ptr->NumChannels;j++)
        {
            short temp;
            fread(&temp,ptr->BitsPerSample>>3,1,fp_res);
            fwrite(&temp,ptr->BitsPerSample>>3,1,fp_out);
        }

    //Put Edited Part
    fseek(fp_res,ptr->Location+floor(ptr->ByteRate*1.0*Begin),SEEK_SET);
    for(int i=0;i<floor(ptr->SampleRate*1.0*(End-Begin));i++)
        for(int j=0;j<ptr->NumChannels;j++)
        {
            short temp;
            fread(&temp,ptr->BitsPerSample>>3,1,fp_res);
            temp*=Arg;
            fwrite(&temp,ptr->BitsPerSample>>3,1,fp_out);
        }

    //Put Latter Part
    fseek(fp_res,ptr->Location+floor(ptr->ByteRate*1.0*End),SEEK_SET);
    for(int i=floor(ptr->SampleRate*1.0*End);i<ptr->DataSize/(ptr->NumChannels*ptr->BitsPerSample>>3);i++)
        for(int j=0;j<ptr->NumChannels;j++)
        {
            short temp;
            fread(&temp,ptr->BitsPerSample>>3,1,fp_res);
            fwrite(&temp,ptr->BitsPerSample>>3,1,fp_out);
        }
    fclose(fp_res);
    fclose(fp_out);
    remove("audio\\temp.wav");
    return;
}

void Reverse(RIFF *ptr,double Begin,double End)
{
    system("copy audio\\output.wav audio\\temp.wav");
    fp_res=fopen("audio\\temp.wav","rb");
    PutFile(ptr);
    fp_out=fopen("audio\\output.wav","rb+");
    fseek(fp_out,ptr->Location,SEEK_SET);

    //Put Former Part
    fseek(fp_res,ptr->Location,SEEK_SET);
    for(int i=0;i<floor(ptr->SampleRate*1.0*Begin);i++)
        for(int j=0;j<ptr->NumChannels;j++)
        {
            short temp;
            fread(&temp,ptr->BitsPerSample>>3,1,fp_res);
            fwrite(&temp,ptr->BitsPerSample>>3,1,fp_out);
        }

    //Put Reversed Part
    if(floor(Begin)==floor(End))
    {
        for(int j=0;j<floor((End-Begin)*ptr->SampleRate);j++)
            for(int k=0;k<ptr->NumChannels;k++)
                fread(&Temp[j][k],ptr->BitsPerSample>>3,1,fp_res);
        for(int j=floor((End-Begin)*ptr->SampleRate)-1;j>=0;j--)
            for(int k=0;k<ptr->NumChannels;k++)
                fwrite(&Temp[j][k],ptr->BitsPerSample>>3,1,fp_out);
    }
    else
    {
        //Put First Part
        fseek(fp_res,ptr->Location+floor(End)*ptr->ByteRate,SEEK_SET);
        for(int j=0;j<floor((End-1.0*floor(End))*ptr->SampleRate);j++)
            for(int k=0;k<ptr->NumChannels;k++)
                fread(&Temp[j][k],ptr->BitsPerSample>>3,1,fp_res);
        for(int j=floor((End-1.0*floor(End))*ptr->SampleRate)-1;j>=0;j--)
            for(int k=0;k<ptr->NumChannels;k++)
                fwrite(&Temp[j][k],ptr->BitsPerSample>>3,1,fp_out);

        //Put Middle Part
        for(int i=0;i<(floor(End)-ceil(Begin));i++)
        {
            fseek(fp_res,ptr->Location+(floor(End)-1-i)*ptr->ByteRate,SEEK_SET);
            for(int j=0;j<ptr->SampleRate;j++)
                for(int k=0;k<ptr->NumChannels;k++)
                    fread(&Temp[j][k],ptr->BitsPerSample>>3,1,fp_res);
            for(int j=ptr->SampleRate-1;j>=0;j--)
                for(int k=0;k<ptr->NumChannels;k++)
                    fwrite(&Temp[j][k],ptr->BitsPerSample>>3,1,fp_out);
        }

        //Put Last Part
        fseek(fp_res,ptr->Location+floor(ptr->ByteRate*1.0*Begin),SEEK_SET);
        for(int j=0;j<floor((ceil(Begin)*1.0-Begin)*ptr->SampleRate);j++)
            for(int k=0;k<ptr->NumChannels;k++)
                fread(&Temp[j][k],ptr->BitsPerSample>>3,1,fp_res);
        for(int j=floor((ceil(Begin)*1.0-Begin)*ptr->SampleRate)-1;j>=0;j--)
            for(int k=0;k<ptr->NumChannels;k++)
                fwrite(&Temp[j][k],ptr->BitsPerSample>>3,1,fp_out);
    }

    //Put Latter Part
    fseek(fp_res,ptr->Location+floor(ptr->ByteRate*1.0*End),SEEK_SET);
    for(int i=floor(ptr->SampleRate*1.0*End);i<(ptr->DataSize)/(ptr->NumChannels*ptr->BitsPerSample>>3);i++)
        for(int j=0;j<ptr->NumChannels;j++)
        {
            short temp;
            fread(&temp,ptr->BitsPerSample>>3,1,fp_res);
            fwrite(&temp,ptr->BitsPerSample>>3,1,fp_out);
        }

    fclose(fp_res);
    fclose(fp_out);
    remove("audio\\temp.wav");
    return;
}

void CutOff(RIFF *ptr,double Begin,double End)
{
    system("copy audio\\output.wav audio\\temp.wav");
    fp_res=fopen("audio\\temp.wav","rb");
    int LostSize=ptr->ByteRate*1.0*(End-Begin);
    ptr->ChunkSize-=LostSize;
    ptr->DataSize-=LostSize;
    if(ptr->IsFact)ptr->TotalSample-=floor(ptr->SampleRate*1.0*(End-Begin));
    PutFile(ptr);
    fp_out=fopen("audio\\output.wav","rb+");
    fseek(fp_out,ptr->Location,SEEK_SET);

    //Put Former Part
    fseek(fp_res,ptr->Location,SEEK_SET);
    for(int i=0;i<floor(ptr->SampleRate*1.0*Begin);i++)
        for(int j=0;j<ptr->NumChannels;j++)
        {
            short temp;
            fread(&temp,ptr->BitsPerSample>>3,1,fp_res);
            fwrite(&temp,ptr->BitsPerSample>>3,1,fp_out);
        }

    //Put Latter Part
    fseek(fp_res,ptr->Location+floor(ptr->ByteRate*1.0*End),SEEK_SET);
    for(int i=floor(ptr->SampleRate*1.0*End);i<(ptr->DataSize+LostSize)/(ptr->NumChannels*ptr->BitsPerSample>>3);i++)
        for(int j=0;j<ptr->NumChannels;j++)
        {
            short temp;
            fread(&temp,ptr->BitsPerSample>>3,1,fp_res);
            fwrite(&temp,ptr->BitsPerSample>>3,1,fp_out);
        }
    fclose(fp_res);
    fclose(fp_out);
    remove("audio\\temp.wav");
    return;
}

void Merge(RIFF *ptr,RIFF *ptr1,double Location,double Begin,double End)
{
    system("copy audio\\output.wav audio\\temp.wav");
    fp_res=fopen("audio\\temp.wav","rb");
    fp_res1=fopen("audio\\res1.wav","rb");
    int ExtraSize=floor(ptr->ByteRate*1.0*(End-Begin));
    ptr->ChunkSize+=ExtraSize;
    ptr->DataSize+=ExtraSize;
    if(ptr->IsFact)ptr->TotalSample+=floor(ptr->SampleRate*1.0*(End-Begin));
    PutFile(ptr);
    fp_out=fopen("audio\\output.wav","rb+");
    fseek(fp_out,ptr->Location,SEEK_SET);

    //Merge Former Part
    fseek(fp_res,ptr->Location,SEEK_SET);
    for(int i=0;i<floor(ptr->SampleRate*1.0*Location);i++)
        for(int j=0;j<ptr->NumChannels;j++)
        {
            short temp;
            fread(&temp,ptr->BitsPerSample>>3,1,fp_res);
            fwrite(&temp,ptr->BitsPerSample>>3,1,fp_out);
        }

    //Merge Extra Part
    fseek(fp_res1,ptr1->Location+floor(ptr1->ByteRate*1.0*Begin),SEEK_SET);
    for(int i=0;i<floor(ptr1->SampleRate*1.0*(End-Begin));i++)
        for(int j=0;j<ptr->NumChannels;j++)
        {
            short temp;
            fread(&temp,ptr->BitsPerSample>>3,1,fp_res1);
            fwrite(&temp,ptr->BitsPerSample>>3,1,fp_out);
        }    

    //Merge Latter Part
    for(int i=floor(ptr->SampleRate*1.0*Location);i<(ptr->DataSize-ExtraSize)/(ptr->NumChannels*ptr->BitsPerSample>>3);i++)
        for(int j=0;j<ptr->NumChannels;j++)
        {
            short temp;
            fread(&temp,ptr->BitsPerSample>>3,1,fp_res);
            fwrite(&temp,ptr->BitsPerSample>>3,1,fp_out);
        }
    fclose(fp_res);
    fclose(fp_res1);
    fclose(fp_out);
    remove("audio\\temp.wav");
    remove("audio\\res1.wav");
    return;
}

void CutChannel(RIFF *ptr,double Begin,double End,int Arg)
{
    system("copy audio\\output.wav audio\\temp.wav");
    fp_res=fopen("audio\\temp.wav","rb");
    PutFile(ptr);
    fp_out=fopen("audio\\output.wav","rb+");
    fseek(fp_out,ptr->Location,SEEK_SET);

    //Put Former Part
    fseek(fp_res,ptr->Location,SEEK_SET);
    for(int i=0;i<floor(ptr->SampleRate*1.0*Begin);i++)
        for(int j=0;j<ptr->NumChannels;j++)
        {
            short temp;
            fread(&temp,ptr->BitsPerSample>>3,1,fp_res);
            fwrite(&temp,ptr->BitsPerSample>>3,1,fp_out);
        }

    //Put Cut Part
    for(int i=0;i<floor(ptr->SampleRate*1.0*(End-Begin));i++) 
    {
        int temp[2];
        for(int j=0;j<ptr->NumChannels;j++)
            fread(&temp[j],ptr->BitsPerSample>>3,1,fp_res);
        temp[Arg]=0;
        for(int j=0;j<ptr->NumChannels;j++)
            fwrite(&temp[j],ptr->BitsPerSample>>3,1,fp_out);   
    }

    //Put Latter Part
    for(int i=floor(ptr->SampleRate*1.0*End);i<ptr->DataSize/(ptr->NumChannels*ptr->BitsPerSample>>3);i++)
        for(int j=0;j<ptr->NumChannels;j++)
        {
            short temp;
            fread(&temp,ptr->BitsPerSample>>3,1,fp_res);
            fwrite(&temp,ptr->BitsPerSample>>3,1,fp_out);
        }    
    fclose(fp_res);
    fclose(fp_out);
    remove("audio\\temp.wav");
    return;
}

void Accelerate(RIFF *ptr,double Begin,double End,int Arg)
{
    system("copy audio\\output.wav audio\\temp.wav");
    fp_res=fopen("audio\\temp.wav","rb");
    int LostSize=floor(ptr->ByteRate*(1.0-1.0/Arg)*(End-Begin));
    ptr->ChunkSize-=LostSize;
    ptr->DataSize-=LostSize;
    ptr->TotalTime-=(1.0-1.0/Arg)*(End-Begin);
    if(ptr->IsFact)ptr->TotalSample-=floor(ptr->SampleRate*(1.0-1.0/Arg)*(End-Begin));
    PutFile(ptr);
    fp_out=fopen("audio\\output.wav","rb+");
    fseek(fp_out,ptr->Location,SEEK_SET);

    //Put Former Part
    fseek(fp_res,ptr->Location,SEEK_SET);
    for(int i=0;i<floor(ptr->SampleRate*1.0*Begin);i++)
        for(int j=0;j<ptr->NumChannels;j++)
        {
            short temp;
            fread(&temp,ptr->BitsPerSample>>3,1,fp_res);
            fwrite(&temp,ptr->BitsPerSample>>3,1,fp_out);
        }    

    //Put Accelerated Part
    for(int i=0;i<floor(ptr->SampleRate*1.0*(End-Begin));i+=Arg) 
    {
        int temp[2];
        for(int k=0;k<Arg;k++)
            for(int j=0;j<ptr->NumChannels;j++)
                fread(&temp[j],ptr->BitsPerSample>>3,1,fp_res);
        for(int j=0;j<ptr->NumChannels;j++)
            fwrite(&temp[j],ptr->BitsPerSample>>3,1,fp_out);
    }

    //Put Latter Part
    for(int i=floor(ptr->SampleRate*1.0*End);i<(ptr->DataSize+LostSize)/(ptr->NumChannels*ptr->BitsPerSample>>3);i++)
        for(int j=0;j<ptr->NumChannels;j++)
        {
            short temp;
            fread(&temp,ptr->BitsPerSample>>3,1,fp_res);
            fwrite(&temp,ptr->BitsPerSample>>3,1,fp_out);
        }    
    fclose(fp_res);
    fclose(fp_out);
    remove("audio\\temp.wav");
    return;
}

void Moderate(RIFF *ptr,double Begin,double End,int Arg)
{
    system("copy audio\\output.wav audio\\temp.wav");
    fp_res=fopen("audio\\temp.wav","rb");
    int ExtraSize=floor(ptr->ByteRate*(Arg-1.0)*(End-Begin));
    ptr->ChunkSize+=ExtraSize;
    ptr->DataSize+=ExtraSize;
    ptr->TotalTime+=(Arg-1.0)*(End-Begin);
    if(ptr->IsFact)ptr->TotalSample+=floor(ptr->SampleRate*(Arg-1.0)*(End-Begin));
    PutFile(ptr);
    fp_out=fopen("audio\\output.wav","rb+");
    fseek(fp_out,ptr->Location,SEEK_SET);

    //Put Former Part
    fseek(fp_res,ptr->Location,SEEK_SET);
    for(int i=0;i<floor(ptr->SampleRate*1.0*Begin);i++)
        for(int j=0;j<ptr->NumChannels;j++)
        {
            short temp;
            fread(&temp,ptr->BitsPerSample>>3,1,fp_res);
            fwrite(&temp,ptr->BitsPerSample>>3,1,fp_out);
        }

    //Put Moderated Part
    for(int i=0;i<floor(ptr->SampleRate*1.0*(End-Begin));i++) 
    {
        int temp[2];
        for(int j=0;j<ptr->NumChannels;j++)
            fread(&temp[j],ptr->BitsPerSample>>3,1,fp_res);
        for(int k=0;k<Arg;k++)
            for(int j=0;j<ptr->NumChannels;j++)
                fwrite(&temp[j],ptr->BitsPerSample>>3,1,fp_out);
    }

    //Put Latter Part
    for(int i=floor(ptr->SampleRate*1.0*End);i<(ptr->DataSize-ExtraSize)/(ptr->NumChannels*ptr->BitsPerSample>>3);i++)
        for(int j=0;j<ptr->NumChannels;j++)
        {
            short temp;
            fread(&temp,ptr->BitsPerSample>>3,1,fp_res);
            fwrite(&temp,ptr->BitsPerSample>>3,1,fp_out);
        }    
    fclose(fp_res);
    fclose(fp_out);
    remove("audio\\temp.wav");
    return;
}

void Combine(RIFF *ptr,RIFF *ptr1,double Location,double Begin,double End)
{
    system("copy audio\\output.wav audio\\temp.wav");
    fp_res=fopen("audio\\temp.wav","rb");
    fp_res1=fopen("audio\\res1.wav","rb");
    PutFile(ptr);
    fp_out=fopen("audio\\output.wav","rb+");
    fseek(fp_out,ptr->Location,SEEK_SET);

    //Put Former Part
    fseek(fp_res,ptr->Location,SEEK_SET);
    for(int i=0;i<floor(ptr->SampleRate*1.0*Location);i++)
        for(int j=0;j<ptr->NumChannels;j++)
        {
            short temp;
            fread(&temp,ptr->BitsPerSample>>3,1,fp_res);
            fwrite(&temp,ptr->BitsPerSample>>3,1,fp_out);
        }

    //Put Combined Part
    fseek(fp_res1,ptr1->Location+floor(ptr1->ByteRate*1.0*Begin),SEEK_SET);
    for(int i=0;i<floor(ptr1->SampleRate*1.0*(End-Begin));i++)
        for(int j=0;j<ptr->NumChannels;j++)
        {
            short temp,temp1,temp2;
            fread(&temp1,ptr->BitsPerSample>>3,1,fp_res);
            fread(&temp2,ptr1->BitsPerSample>>3,1,fp_res1);
            temp=temp1*0.5+temp2*0.5;
            fwrite(&temp,ptr->BitsPerSample>>3,1,fp_out);
        }   
    //Put Latter Part
    for(int i=floor(ptr->SampleRate*1.0*(Location+End-Begin));i<(ptr->DataSize)/(ptr->NumChannels*ptr->BitsPerSample>>3);i++)
        for(int j=0;j<ptr->NumChannels;j++)
        {
            short temp;
            fread(&temp,ptr->BitsPerSample>>3,1,fp_res);
            fwrite(&temp,ptr->BitsPerSample>>3,1,fp_out);
        }
    fclose(fp_res);
    fclose(fp_res1);
    fclose(fp_out);
    remove("audio\\temp.wav");
    remove("audio\\res1.wav");
    return;
}

void RaiseTone(RIFF *ptr,double Begin,double End,int Arg)
{
    system("copy audio\\output.wav audio\\temp.wav");
    fp_res=fopen("audio\\temp.wav","rb");
    PutFile(ptr);
    fp_out=fopen("audio\\output.wav","rb+");
    fseek(fp_out,ptr->Location,SEEK_SET);

    //Put Former Part
    fseek(fp_res,ptr->Location,SEEK_SET);
    for(int i=0;i<floor(ptr->SampleRate*1.0*Begin);i++)
        for(int j=0;j<ptr->NumChannels;j++)
        {
            short temp;
            fread(&temp,ptr->BitsPerSample>>3,1,fp_res);
            fwrite(&temp,ptr->BitsPerSample>>3,1,fp_out);
        }

    //Put Raised Part
    for(int i=0;i<floor(ptr->SampleRate*1.0*(End-Begin))-floor(ptr->SampleRate/25.0);i+=floor(ptr->SampleRate/25.0)) 
    {
        for(int j=0;j<floor(ptr->SampleRate/25.0);j++)
            for(int k=0;k<ptr->NumChannels;k++)
            {
                fread(&Temp[j>>1][k],ptr->BitsPerSample>>3,1,fp_res);
                Temp[(int)floor(ptr->SampleRate/25.0)+j>>1][k]=Temp[j>>1][k];
            }
        for(int j=0;j<floor(ptr->SampleRate/25.0);j++)
            for(int k=0;k<ptr->NumChannels;k++)
                fwrite(&Temp[j][k],ptr->BitsPerSample>>3,1,fp_out);            
    }

    //Put Latter Part
    for(int i=floor(ptr->SampleRate*1.0*End);i<ptr->DataSize/(ptr->NumChannels*ptr->BitsPerSample>>3);i++)
        for(int j=0;j<ptr->NumChannels;j++)
        {
            short temp;
            fread(&temp,ptr->BitsPerSample>>3,1,fp_res);
            fwrite(&temp,ptr->BitsPerSample>>3,1,fp_out);
        }    
    fclose(fp_res);
    fclose(fp_out);
    remove("audio\\temp.wav");
    if(Arg>1)RaiseTone(ptr,Begin,End,Arg-1);
    return;
}

void ModeratePro(RIFF *ptr,double Begin,double End,int Arg)
{
    RaiseTone(ptr,Begin,End,Arg>>1);
    Moderate(ptr,Begin,End,Arg);
    return;
}

void RaiseSample(RIFF *ptr,int Target)
{
    system("copy audio\\res1.wav audio\\temp.wav");
    fp_res=fopen("audio\\temp.wav","rb");
    int Origin=ptr->SampleRate;
    int ExtraSize=ptr->ByteRate*(Target-Origin);
    ptr->ChunkSize+=ExtraSize;   
    ptr->SampleRate=Target;
    ptr->ByteRate=Target*ptr->BlockAlign;
    if(ptr->IsFact)ptr->TotalSample=Target*ptr->TotalTime;
    ptr->DataSize+=ExtraSize;
    PutFile(ptr);
    fp_out=fopen("audio\\res1.wav","rb+");
    fseek(fp_out,ptr->Location,SEEK_SET);
    for(int i=0;i<ptr->TotalTime;i++)
        for(int k=1;k<=Origin;k++)
        {
            int temp[2];
            for(int j=0;j<ptr->NumChannels;j++)
            {   
                fread(&temp[j],ptr->BitsPerSample>>3,1,fp_res);
                fwrite(&temp[j],ptr->BitsPerSample>>3,1,fp_out);
            }
            if(k%(Origin/(Target-Origin))==0&&k<=(Origin/(Target-Origin))*(Target-Origin))
                for(int j=0;j<ptr->NumChannels;j++)
                    fwrite(&temp[j],ptr->BitsPerSample>>3,1,fp_out);
        }
    fclose(fp_res);
    fclose(fp_out);
    remove("audio\\temp.wav");
    return;
}

void LowerSample(RIFF *ptr,int Target)
{
    system("copy audio\\res1.wav audio\\temp.wav");
    fp_res=fopen("audio\\temp.wav","rb");
    int Origin=ptr->SampleRate;
    int LostSize=ptr->ByteRate*(Origin-Target);
    ptr->ChunkSize-=LostSize;   
    ptr->SampleRate=Target;
    ptr->ByteRate=Target*ptr->BlockAlign;
    if(ptr->IsFact)ptr->TotalSample=Target*ptr->TotalTime;
    ptr->DataSize-=LostSize;
    PutFile(ptr);
    fp_out=fopen("audio\\res1.wav","rb+");
    fseek(fp_out,ptr->Location,SEEK_SET);
    for(int i=0;i<ptr->TotalTime;i++)
        for(int k=1;k<=Origin;k++)
        {
            int temp[2]; 
            for(int j=0;j<ptr->NumChannels;j++)
                fread(&temp[j],ptr->BitsPerSample>>3,1,fp_res);        
            if(k%(Origin/(Origin-Target))==0&&k<=(Origin/(Origin-Target))*(Origin-Target))
                continue;
            for(int j=0;j<ptr->NumChannels;j++)
                fwrite(&temp[j],ptr->BitsPerSample>>3,1,fp_out);
        }
    fclose(fp_res);
    fclose(fp_out);
    remove("audio\\temp.wav");
    return;
}

void Repeat(RIFF *ptr,double Location,double Begin,double End)
{
    system("copy audio\\output.wav audio\\res1.wav");
    Merge(ptr,ptr,Location,Begin,End);
    return;
}

void Transfer(RIFF *ptr,double Location,double Begin,double End)
{
    if(Location<Begin)
    {
        system("copy audio\\output.wav audio\\res1.wav");
        CutOff(ptr,Begin,End);        
        Merge(ptr,ptr,Location,Begin,End);
    }        
    if(Location>End)
    {
        system("copy audio\\output.wav audio\\res1.wav");
        CutOff(ptr,Begin,End);        
        Merge(ptr,ptr,Location-End+Begin,Begin,End);
    }        
    return;
}

void EnvironmentEffect(RIFF *ptr,double Begin,double End,double Arg)
{
    EditVoice(ptr,Begin,End+Arg,0.5);
    system("copy audio\\output.wav audio\\res1.wav");
    Combine(ptr,ptr,Begin+Arg,Begin,End);
    return;
}