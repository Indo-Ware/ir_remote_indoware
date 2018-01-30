/*
Data remot Indo-Ware

HEADER :
1C 61 DC

DATA :
1 	: 07 F8 //ANGKA 1
2 	: 0B F4 //ANGKA 2
3 	: 0F F0 //ANGKA 3
4 	: 13 EC //ANGKA 4
5 	: 17 E8 //ANGKA 5
6 	: 1B E4 //ANGKA 6
7 	: 1F E0 //ANGKA 7
8 	: 23 DC //ANGKA 8
9 	: 27 D8 //ANGKA 9
10	: 03 FC //ANGKA 10
11	: 7F 80 //SYS
12	: 67 98 //P.P
13	: 6F 90 //DISP
14	: 2F d0 //TV/AV
15	: 5B A4 //MUTE
16	: 4B B4 //POWER
17	: 37 C8 //MUSIC
18	: 3F C0 //SLEEP
19	: 3B C4 //MENU
20	: 73 8C //GAME
21	: 63 9C //ZOOM
22	: 4F B0 //P+
23	: 5F A0 //P-
24	: 43 BC	//V+
25	: 53 AC //V-
26	: 2B D4 // --/-
27	: 6B 94 // recall
*/

#include <IRLibAll.h>

char baca_data_remot() {
  int i; uint32_t Extent; int interval;
  int LowSpace = 32767; int LowMark =  32767;
  int HiSpace = 0; int HiMark =  0; int k=0; int x=0;
  int byte_ke = 0;
  int bit_ke = 0;
  int timestamp[100];
  uint8_t data_remot[5];
  int data_decode;
  
  for(x=0;x<101;x++){
	  timestamp[x]=0;
  }
	
  for (i = 3; i < recvGlobal.decodeLength; i++) {
    Extent += (interval = recvGlobal.decodeBuffer[i]);
    if (i % 2) {
      LowMark = min(LowMark, interval);  HiMark = max(HiMark, interval);
	  }
    else {
      if (interval > 0)LowSpace = min(LowSpace, interval);  HiSpace = max (HiSpace, interval);
      timestamp[k]=interval;
      k++;  
    }
  }
  
  for(x=0;x<41;x++){
    if(timestamp[x]<800 && timestamp[x]>500){ //logika 0
        data_remot[byte_ke] &= ~(1<< bit_ke);
        }
    else if(timestamp[x]<2000 && timestamp[x]>1600){ // logika 1
        data_remot[byte_ke] |= 1<<bit_ke;
        }
    bit_ke++;
    if(bit_ke>7){byte_ke++;bit_ke=0;}
    if(byte_ke>4){byte_ke=0;bit_ke=0;break;}
    }
	
	//Serial.print(data_remot[3],HEX);Serial.println(data_remot[4],HEX);
	
	data_decode= (data_remot[3]<<8) | data_remot[4];
	
	switch(data_decode){
		case 0x07f8:return 1;	break;
		case 0x0bf4:return 2;	break;
		case 0x0ff0:return 3;	break;
		case 0x13ec:return 4;	break;
		case 0x17e8:return 5;	break;
		case 0x1be4:return 6;	break;
		case 0x1fe0:return 7;	break;
		case 0x23dc:return 8; 	break;
		case 0x27d8:return 9; 	break;
		case 0x03fc:return 10;	break;
		case 0x7f80:return 11;	break;
		case 0x6798:return 12;	break;
		case 0x6f90:return 13;	break;
		case 0x2fd0:return 14;	break;
		case 0x5ba4:return 15;	break;
		case 0x4bb4:return 16;	break;
		case 0x37c8:return 17;	break;
		case 0x3fc0:return 18;	break;
		case 0x3bc4:return 19;	break;
		case 0x738c:return 20;	break;
		case 0x639c:return 21; 	break;
		case 0x4fb0:return 22; 	break;
		case 0x5fa0:return 23;	break;
		case 0x43bc:return 24; 	break;
		case 0x53ac:return 25;	break;
		case 0x2bd4:return 26;	break;
		case 0x6b94:return 27;	break;
		default:	return 0;	break;
	}
	
}
