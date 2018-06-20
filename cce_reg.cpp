/*  ============================================================================
 *
 * CEWiT CONFIDENTIAL
 * __________________
 *
 * All Rights Reserved © 2018 CEWiT, India
 *
 * NOTICE: All information contained herein is, and remains the property of Centre
 * of Excellence in Wireless Technology (CEWiT). The intellectual and technical concepts
 * contained herein may be proprietary to CEWiT. Unauthorized use, duplication, reverse
 * engineering, any form of redistribution, or use in part or in whole other than by prior,
 * express, printed and signed license for use is strictly forbidden.
 *
 */

#include <iostream>
using namespace std;

class CCE {
private:
    int regs[6];
    int cceNum;
public:
    void mDisplay(){
        cout<<cceNum<<"  ";
        for(int i=0;i<6;i++){
            cout<<regs[i]<<' ';
        }
        cout<<endl;
    }
    void mAssignCceNum(int num){
        cceNum=num;
    }
    void mAssignRegNum(bool interleaved,int coresetFreqDom,int coresetTimeDur,int coresetREGbundleSize,int R,int cellID,int coresetShiftIndex,bool flagPBCH)
    {
        int nShift,L;
        if(flagPBCH){
            L=6;
            R=2;
            nShift=cellID;
        }
        else{
            nShift=coresetShiftIndex;
        }
        if(interleaved){
            L=coresetREGbundleSize;
        }
        else{
            L=6;
        }
        int regBundleNums[6/L];
        if(!interleaved){
            regBundleNums[0]=cceNum;
        }
        else{
            int C=coresetFreqDom*coresetTimeDur/(L*R);
            for(int index=0;index<6/L;index++){
               int r=((6*cceNum/L)+index)%R;
               int c=((6*cceNum/L)+index)/R; 
               regBundleNums[index]=((r*C)+c+nShift)%(coresetFreqDom*coresetTimeDur/L);
            }
        }
        for(int index=0;index<6/L;index++){
            for(int num=0;num<L;num++){
                regs[(index*L)+num]=(regBundleNums[index]*L)+num;
            }
        }
        
    }
};

int main()
{
    bool interleaved=1;
    int coresetFreqDom=6;
    int coresetTimeDur=2;
    int coresetREGbundleSize=2;
    int R=3;
    int cellID=329;
    int coresetShiftIndex=1;
    bool flagPBCH=1;
    CCE cce[coresetFreqDom*coresetTimeDur/6];
    for(int count=0;count<(coresetFreqDom*coresetTimeDur/6);count++){
        cce[count].mAssignCceNum(count);
        cce[count].mAssignRegNum(interleaved,coresetFreqDom,coresetTimeDur,coresetREGbundleSize,R,cellID,coresetShiftIndex,flagPBCH);
        cce[count].mDisplay();
    }
    return 0;
}
