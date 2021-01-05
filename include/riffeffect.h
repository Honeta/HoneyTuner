#ifndef RIFFEFFECT_H
#define RIFFEFFECT_H

struct RIFF;

extern void EditVoice(RIFF *,double,double,double);

extern void Reverse(RIFF *,double,double);

extern void CutOff(RIFF *,double,double);

extern void Merge(RIFF *,RIFF *,double,double,double);

extern void CutChannel(RIFF *,double,double,int);

extern void Accelerate(RIFF *,double,double,int);

extern void Moderate(RIFF *,double,double,int);

extern void EnvironmentEffect(RIFF *,double,double,double);

extern void Combine(RIFF *,RIFF *,double,double,double);

extern void RaiseTone(RIFF *,double,double,int);

extern void ModeratePro(RIFF *,double,double,int);

extern void RaiseSample(RIFF *,int);

extern void LowerSample(RIFF *,int);

extern void Repeat(RIFF *,double,double,double);

extern void Transfer(RIFF *,double,double,double);

#endif
