#include "RGKR.h"
#include <string.h>
#include <stdio.h>

RGKR_Uart_Params_t RGKR_Uart_Params;

RGKR_Params_t RGKR_Params_Table[] = {

    //  Parametre Adi ,         Sorgu Istegi                                                        ,  Scale    
	{"ACTE_IM_L1" ,{'\x4D' ,'\x01' ,'\x03' ,'\x00' ,'\x00' ,'\x00' ,'\x02' ,'\xC1' ,'\xE1' ,'\x42'} ,1000},
	{"ACTE_IM_L2" ,{'\x4D', '\x01' ,'\x03' ,'\x00' ,'\x01' ,'\x00' ,'\x02' ,'\x01' ,'\xB0' ,'\x42'} ,1000},
	{"ACTE_IM_L3" ,{'\x4D', '\x01' ,'\x03' ,'\x00' ,'\x02' ,'\x00' ,'\x02' ,'\x01' ,'\x40' ,'\x42'} ,1000},
	{"INDE_L1" ,{'\x4D' ,'\x01' ,'\x03' ,'\x00' ,'\x06' ,'\x00' ,'\x02' ,'\xC0' ,'\x01' ,'\x42'} ,1000},
	{"INDE_L2" ,{'\x4D' ,'\x01' ,'\x03' ,'\x00' ,'\x07' ,'\x00' ,'\x02' ,'\x00' ,'\x50' ,'\x42'} ,1000},
	{"INDE_L3" ,{'\x4D' ,'\x01' ,'\x03' ,'\x00' ,'\x08' ,'\x00' ,'\x02' ,'\x03' ,'\x60' ,'\x42'} ,1000}, 
	{"CAPE_L1" ,{'\x4D' ,'\x01' ,'\x03' ,'\x00' ,'\x09' ,'\x00' ,'\x02' ,'\xC3' ,'\x31' ,'\x42'} ,1000},
	{"CAPE_L2" ,{'\x4D' ,'\x01' ,'\x03' ,'\x00' ,'\x0A' ,'\x00' ,'\x02' ,'\xC3' ,'\xC1' ,'\x42'} ,1000},
	{"CAPE_L3" ,{'\x4D' ,'\x01' ,'\x03' ,'\x00' ,'\x0B' ,'\x00' ,'\x02' ,'\x03' ,'\x90' ,'\x42'} ,1000},
	{"ACTPWR_L1" ,{'\x4D' ,'\x01' ,'\x03' ,'\x00' ,'\x0C' ,'\x00' ,'\x02' ,'\xC2' ,'\x21' ,'\x42'} ,1000},
	{"ACTPWR_L2" ,{'\x4D' ,'\x01' ,'\x03' ,'\x00' ,'\x0D' ,'\x00' ,'\x02' ,'\x02' ,'\x70' ,'\x42'} ,1000},
	{"ACTPWR_L3" ,{'\x4D' ,'\x01' ,'\x03' ,'\x00' ,'\x0E' ,'\x00' ,'\x02' ,'\x02' ,'\x80' ,'\x42'} ,1000},
	{"INDPWR_L1" ,{'\x4D' ,'\x01' ,'\x03' ,'\x00' ,'\x0F' ,'\x00' ,'\x02' ,'\xC2' ,'\xD1' ,'\x42'} ,1000},
	{"INDPWR_L2" ,{'\x4D' ,'\x01' ,'\x03' ,'\x00' ,'\x10' ,'\x00' ,'\x02' ,'\x04' ,'\xE0' ,'\x42'} ,1000},
	{"INDPWR_L3" ,{'\x4D' ,'\x01' ,'\x03' ,'\x00' ,'\x11' ,'\x00' ,'\x02' ,'\xC4' ,'\xB1' ,'\x42'} ,1000},
	{"CAPPWR_L1" ,{'\x4D' ,'\x01' ,'\x03' ,'\x00' ,'\x12' ,'\x00' ,'\x02' ,'\xC4' ,'\x41' ,'\x42'} ,1000},
	{"CAPPWR_L2" ,{'\x4D' ,'\x01' ,'\x03' ,'\x00' ,'\x13' ,'\x00' ,'\x02' ,'\x04' ,'\x10' ,'\x42'} ,1000},
	{"CAPPWR_L3" ,{'\x4D' ,'\x01' ,'\x03' ,'\x00' ,'\x14' ,'\x00' ,'\x02' ,'\xC5' ,'\xA1' ,'\x42'} ,1000},
	{"CosPhi_L1" ,{'\x4D' ,'\x01' ,'\x03' ,'\x00' ,'\x15' ,'\x00' ,'\x00' ,'\xC4' ,'\x71' ,'\x42'} ,100},
	{"CosPhi_L2" ,{'\x4D' ,'\x01' ,'\x03' ,'\x00' ,'\x16' ,'\x00' ,'\x00' ,'\xC4' ,'\x81' ,'\x42'} ,100},
	{"CosPhi_L3" ,{'\x4D' ,'\x01' ,'\x03' ,'\x00' ,'\x17' ,'\x00','\x00' ,'\x04' ,'\xD0' ,'\x42'} ,100},
	{"REACHIND" ,{'\x4D' ,'\x01' ,'\x03' ,'\x00' ,'\x18' ,'\x00' ,'\x00' ,'\x07' ,'\xE0' ,'\x42'} ,10},
	{"REACHCAP" ,{'\x4D' ,'\x01' ,'\x03' ,'\x00' ,'\x19' ,'\x00' ,'\x00' ,'\xC7' ,'\xB1' ,'\x42'} ,10},
	{"THDL1" ,{'\x4D' ,'\x01' ,'\x03' ,'\x00' ,'\x1D' ,'\x00' ,'\x00' ,'\x06' ,'\xF0' ,'\x42'} ,1},
	{"THDL2" ,{'\x4D' ,'\x01' ,'\x03' ,'\x00' ,'\x1E' ,'\x00' ,'\x00' ,'\x06' ,'\x00' ,'\x42'} ,1},
	{"THDL3" ,{'\x4D' ,'\x01' ,'\x03' ,'\x00' ,'\x1F' ,'\x00' ,'\x00' ,'\xC6' ,'\x51' ,'\x42'} ,1},
	{"VOLT_L1" ,{'\x4D' ,'\x01' ,'\x03' ,'\x00' ,'\x23' ,'\x00' ,'\x00' ,'\xCA' ,'\x91' ,'\x42'} ,1},
	{"VOLT_L2" ,{'\x4D' ,'\x01' ,'\x03' ,'\x00' ,'\x24' ,'\x00' ,'\x00' ,'\x0B' ,'\x20' ,'\x42'} ,1},
	{"VOLT_L3" ,{'\x4D' ,'\x01' ,'\x03' ,'\x00' ,'\x25' ,'\x00' ,'\x00' ,'\xCB' ,'\x71' ,'\x42'} ,1},
	{"CURRENT_L1" ,{'\x4D' ,'\x01' ,'\x03' ,'\x00' ,'\x26' ,'\x00' ,'\x00' ,'\xCB' ,'\x81' ,'\x42'} ,100},
	{"CURRENT_L2" ,{'\x4D' ,'\x01' ,'\x03' ,'\x00' ,'\x27' ,'\x00' ,'\x00' ,'\x0B' ,'\xD0' ,'\x42'} ,100},
	{"CURRENT_L3" ,{'\x4D' ,'\x01' ,'\x03' ,'\x00' ,'\x28' ,'\x00' ,'\x00' ,'\x08' ,'\xE0' ,'\x42'} ,100},
	{0 ,{'0'} ,0},

};

float ParseProcess(char *pParseArr, int size, int whichReg)
{
    float fCalculated = 0;

    if (pParseArr[size] == 0x42 && pParseArr[0] == 0x4D)
    {
        if (pParseArr[5] == 0x04)
        {
            fCalculated = (pParseArr[6] << 24) | (pParseArr[7] << 16 ) | (pParseArr[8] << 8 ) | (pParseArr[9] & 0xff);
        }
            
        else if (pParseArr[5] == 0x02)
        {
            fCalculated = (pParseArr[6] << 8) | (pParseArr[7] & 0xff);
        }
        
            
        fCalculated = fCalculated / RGKR_Params_Table[whichReg].ucScale;
    }

    return fCalculated;
}
