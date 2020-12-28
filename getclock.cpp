#include<time.h>

static time_t temp;
static struct tm *now;

int GetYear()
{
    time(&temp);
    now=gmtime(&temp);
    return 1900+now->tm_year;
}

int GetMonth()
{
    time(&temp);
    now=gmtime(&temp);
    return 1+now->tm_mon;
}

int GetDay()
{
    time(&temp);
    now=gmtime(&temp);
    return now->tm_mday;
}

int GetHour()
{
    time(&temp);
    now=gmtime(&temp);
    return 8+now->tm_hour;
}

int GetMinute()
{
    time(&temp);
    now=gmtime(&temp);
    return now->tm_min;
}

int GetSecond()
{
    time(&temp);
    now=gmtime(&temp);
    return now->tm_sec;
}
