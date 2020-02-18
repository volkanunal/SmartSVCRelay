#pragma once

#include "stdint.h"


typedef struct 
{
    const char *RegName;
    const char RequestArray[10];
    const int ucScale;

}RGKR_Params_t;

typedef struct RGKR
{
    uint8_t buffer[32];
    uint8_t idx;
    float value;

}RGKR_Uart_Params_t;



extern RGKR_Params_t RGKR_Params_Table[];
extern RGKR_Uart_Params_t RGKR_Uart_Params;

float  ParseProcess(char *pParseArr, int size, int whichReg);
  

