#include<io.h>
#include<vector>
#include<cstdio>
#include<cstdlib>
#include<string>

using namespace std;

vector<string> GetFileList(string path,string typ)
{
    vector<string> FileList;
    _finddata_t FileInfo;
    long Handle;
    (path+="\\*.")+=typ;
    const char *Path=path.c_str();
    if((Handle=_findfirst(Path,&FileInfo))!=-1)
    {
        do
        {
            if(!(FileInfo.attrib&_A_SUBDIR))
                FileList.push_back(FileInfo.name);
        } while (_findnext(Handle,&FileInfo)==0);
        _findclose(Handle);
    }
    return FileList;
}

const char *LastFile(string path,string typ)
{
    vector<string> FileList=GetFileList(path,typ);
    if(!FileList.size())return " ";
    const char *Ans=FileList.back().c_str();
    return Ans;
}