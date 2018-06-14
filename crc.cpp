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

#include<iostream>
#define MAX_PAYLOADSIZE 1000
using namespace std;
const int LEN_PARITY = 24;
bool gParityAddedpayLoad[MAX_PAYLOADSIZE+LEN_PARITY];
// cce to reg mapping

void CrcAttach (bool payLoad[],int len_payLoad, bool rnti[]);

int main()
{
   bool payload[] = {1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0};
   
   int len_payLoad = 32;
   bool output[LEN_PARITY+len_payLoad];
   bool rnti[] = {1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0};
   //bool *p;
   CrcAttach(payload,len_payLoad, rnti);
   for (int i = 0;i<LEN_PARITY+len_payLoad;i++)
   {
      output[i] = gParityAddedpayLoad[i];
      cout << gParityAddedpayLoad[i] ; 
   }
   cout << endl;
   return 0;
}

void CrcAttach (bool payLoad[],int len_payLoad, bool rnti[])
{
    bool payLoadDash[len_payLoad+(2*LEN_PARITY)];
    
    for (int index = 0;index<len_payLoad+(2*LEN_PARITY);index++)
    {
        if (index<LEN_PARITY)
        {
            payLoadDash[index] = 1;
        }
        else if (index<len_payLoad+LEN_PARITY)
        {
            payLoadDash[index] = payLoad[index-LEN_PARITY];
        }
        else
        {
            payLoadDash[index] = 0;
        }
        
    }
    
    bool gCRC24c[] = {1, 1, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1};
    
    for (int pos = 0;pos< len_payLoad+4;pos++)
    {
        if (payLoadDash[pos] == 1)
        {
            for (int count = 0;count<LEN_PARITY+1;count++)
            {
                payLoadDash[pos+count] = payLoadDash[pos+count] ^ gCRC24c[count];
            }
        }
    }
    
    for (int pos = 0;pos<len_payLoad+LEN_PARITY;pos++)
    {
        if (pos<len_payLoad)
        {
            gParityAddedpayLoad[pos] = payLoad[pos];

        }
        else if (pos<len_payLoad+8)
        {
            gParityAddedpayLoad[pos] = payLoadDash[pos+LEN_PARITY];
        }
        else
        {
            gParityAddedpayLoad[pos] = payLoadDash[pos+LEN_PARITY] ^ rnti[pos-len_payLoad];
        }
    }
}
