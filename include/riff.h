#ifndef RIFF_H
#define RIFF_H

struct RIFF
{
    //RIFF Chunk
    char ChunkID[4];
    int ChunkSize;
    char Format[4];

    //Format Chunk
    char FormatID[4];
    int FormatSize;
    short AudioFormat;
    short NumChannels;
    int SampleRate;
    int ByteRate;
    short BlockAlign; 
    short BitsPerSample;
    short FormatData[666];

    //Fact Chunk
    bool IsFact;
    char FactID[4];
    int FactSize;
    int TotalSample;

    //Data Chunk    
    char DataID[4];
    int DataSize;
    int Location;
    int TotalTime;
};

extern bool GetInfo(RIFF *,int);

extern void PutFile(RIFF *);

extern void Reset(RIFF *,int);

#endif
