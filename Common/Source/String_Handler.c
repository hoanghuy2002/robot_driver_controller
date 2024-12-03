#include "String_Handler.h"
#include <stdlib.h>

uint8_t String_Compare(char* String1, char* String2)
{
    uint8_t String_Length_1 = strlen(String1);
    uint8_t String_Length_2 = strlen(String2);
    if(String_Length_1 != String_Length_2)
    {
        return 0;
    }
    else
    {
        for (uint8_t String_Index = 0; String_Index < String_Length_1; String_Index++)
        {
            if (*(String1 + String_Index) != *(String2 + String_Index))
            {
                return 0;
            }
            else
            {
                continue;
            }
            
        }
        return 1;
        
    }
}

uint8_t String_Check_Data_In_String(char * String, char *Data)
{
    uint8_t Data_Length = strlen(Data);
    for (uint8_t  String_Index = 0; String_Index < Data_Length; String_Index++)
    {
        if (*(Data + String_Index) != *(String + String_Index)) return 0;
        else continue;
    }
    return 1;
    
}

int8_t String_Find_Index_Of_Character(char *String, char *Character)
{
    uint8_t String_Length = strlen(String);
    for (uint8_t String_Index = 0; String_Index < String_Length; String_Index ++)
    {
        if (*Character == *(String + String_Index)) return String_Index;
        else continue;
    }
    return -1;
    
}

int16_t String_Convert_String_To_IntergerNumber(char *String)
{
    uint16_t Value = atoi(String);
    return Value;
}