#include<cstdio>
#include<cstdlib>
#include"include/riff.h"

static FILE *fp_res,*fp_out;

bool GetInfo(RIFF *ptr,int Arg)
{
    Arg?fp_res=fopen("res1.wav","rb"):fp_res=fopen("res.wav","rb");

    //Get Chunk
    fread(ptr->ChunkID,4,1,fp_res);
    if(ptr==NULL||ptr->ChunkID[0]!='R'||ptr->ChunkID[1]!='I'||ptr->ChunkID[2]!='F'||ptr->ChunkID[3]!='F')
    {
        fclose(fp_res);
        return 0;
    }        
    fread(&ptr->ChunkSize,4,1,fp_res);
    fread(ptr->Format,4,1,fp_res);

    //Get Format
    fread(ptr->FormatID,4,1,fp_res);
    fread(&ptr->FormatSize,4,1,fp_res);
    fread(&ptr->AudioFormat,2,1,fp_res);
    fread(&ptr->NumChannels,2,1,fp_res);
    fread(&ptr->SampleRate,4,1,fp_res);
    fread(&ptr->ByteRate,4,1,fp_res);
    fread(&ptr->BlockAlign,2,1,fp_res);
    fread(&ptr->BitsPerSample,2,1,fp_res);
    for(int i=0;i<ptr->FormatSize-16>>1;i++)
        fread(&ptr->FormatData[i],2,1,fp_res);

    //Get Fact
    fread(ptr->FactID,4,1,fp_res); 
    if(ptr->FactID[0]=='f')
    {
        ptr->IsFact=true;
        fread(&ptr->FactSize,4,1,fp_res);
        fread(&ptr->TotalSample,4,1,fp_res);
    }
    else
    {
        ptr->IsFact=false;
        fseek(fp_res,-4,SEEK_CUR);
    }

    //Get Data
    fread(ptr->DataID,4,1,fp_res);
    fread(&ptr->DataSize,4,1,fp_res);
    ptr->Location=ptr->ChunkSize-ptr->DataSize+8;
    ptr->TotalTime=ptr->DataSize/ptr->ByteRate;
    fclose(fp_res);
    return 1;
}

void PutInfo(RIFF *ptr)
{
    //Put Chunk
    printf("[Chunk]\n");
    printf("ChunkID=%s\n",ptr->ChunkID);
    printf("ChunkSize=%d\n",ptr->ChunkSize);
    printf("Format=%s\n",ptr->Format);

    //Put Format
    printf("[Format]\n"); 
    printf("FormatID=%s\n",ptr->FormatID);
    printf("FormatSize=%d\n",ptr->FormatSize);
    printf("AudioFormat=%hd\n",ptr->AudioFormat);
    printf("NumChannels=%hd\n",ptr->NumChannels);
    printf("SampleRate=%d\n",ptr->SampleRate);
    printf("ByteRate=%d\n",ptr->ByteRate);
    printf("BlockAlign=%hd\n",ptr->BlockAlign);
    printf("BitsPerSample=%hd\n",ptr->BitsPerSample);

    //Put Fact
    if(ptr->IsFact==true)
    {
        printf("[Fact]\n");
        printf("FactID=%s\n",ptr->FactID);
        printf("FactSize=%d\n",ptr->FactSize);
        printf("TotalSample=%d\n",ptr->TotalSample);
    }

    //Put Data
    printf("[Data]\n");
    printf("DataID=%s\n",ptr->DataID);
    printf("DataSize=%d\n",ptr->DataSize);
    printf("Location=%d\n",ptr->Location);
    printf("TotalTime=%d\n",ptr->TotalTime);
    return;
}

void PutFile(RIFF *ptr)
{
    fp_out=fopen("output.wav","wb");

    //Put Chunk
    fwrite(ptr->ChunkID,4,1,fp_out);
    fwrite(&ptr->ChunkSize,4,1,fp_out);
    fwrite(ptr->Format,4,1,fp_out);

    //Put Format
    fwrite(ptr->FormatID,4,1,fp_out);
    fwrite(&ptr->FormatSize,4,1,fp_out);
    fwrite(&ptr->AudioFormat,2,1,fp_out);
    fwrite(&ptr->NumChannels,2,1,fp_out);
    fwrite(&ptr->SampleRate,4,1,fp_out);
    fwrite(&ptr->ByteRate,4,1,fp_out);
    fwrite(&ptr->BlockAlign,2,1,fp_out);
    fwrite(&ptr->BitsPerSample,2,1,fp_out);
    for(int i=0;i<ptr->FormatSize-16>>1;i++)
        fwrite(&ptr->FormatData[i],2,1,fp_out);

    //Put Fact
    if(ptr->IsFact==true)
    {
        fwrite(ptr->FactID,4,1,fp_out);
        fwrite(&ptr->FactSize,4,1,fp_out);
        fwrite(&ptr->TotalSample,4,1,fp_out);
    }

    //Put Data
    fwrite(ptr->DataID,4,1,fp_out);
    fwrite(&ptr->DataSize,4,1,fp_out);
    fclose(fp_out);
    return;
}

void Reset(RIFF *ptr,int Arg)
{
    GetInfo(ptr,Arg);
    if(Arg==0)system("copy res.wav output.wav");
    return;
}
