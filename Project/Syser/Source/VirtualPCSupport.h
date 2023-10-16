#ifndef _VIRTUALPC_SUPPORT_H_
#define _VIRTUALPC_SUPPORT_H_


void FlushVirtualPCScreenBuffer(int nleft,int ntop,int nright,int nbottom);
extern bool gInVirtualPC;
bool VirtualPCTest();

#endif /* _VIRTUALPC_SUPPORT_H_ */