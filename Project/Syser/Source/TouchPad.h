#ifndef _TOUCHPAD_H_
#define _TOUCHPAD_H_
void TestTouchPad();
extern bool gTouchPad;
extern BYTE gTouchPadMode;
void AnalyzerTouchPadPackage();
void AlpsAnalyzerTouchPadPackage();
extern bool gbSynapticsTouchPad;
extern bool gbAlpsTouchPad;
bool IsAlpsTouchPad();
bool IsSynapticsTouchPad();
#endif //_TOUCHPAD_H_