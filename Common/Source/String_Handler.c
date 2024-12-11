#include "String_Handler.h"
#include <stdlib.h>
#include <stdio.h>

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

int16_t String_Convert_String_To_Number(char *String)
{
    uint16_t Value = strtod(String,NULL);
    return Value;
}

void String_Convert_Number_To_String(char *String_Result, float Number)
{
    sprintf(String_Result,"%f", Number);
}

void String_Assign_Value_To_String(char *Data,char *String)
{
    uint8_t index = 0;
    while(*(String + index) != 0x00)
    {
        *(String + index) = 0x00;
        index++;
    }
    uint8_t Lenght_Of_Data = strlen(Data);
    for (index = 0; index < Lenght_Of_Data; index ++)
    {
        *(String + index) = *(Data + index);
    }

}

void String_Append_String(char *Data, char *String)
{
    uint8_t Length_Of_String = strlen(String);
    uint8_t Length_Of_Data = strlen(Data);
    for (uint8_t Data_Index = 0; Data_Index < Length_Of_Data; Data_Index ++)
    {
        *(String + Data_Index + Length_Of_String) = *(Data + Data_Index);
    }
}


void String_Insert_Data_To_String(char *Data, char *String, int8_t Index)
{
    uint8_t Length_Of_String = strlen(String);
    uint8_t Length_Of_Data = strlen(Data);
    uint8_t String_Index = 0;
    uint8_t Data_Index = 0;
    char *Temp_Buffer =(char *) calloc(Length_Of_String + 1, sizeof(char));

    if (Index < 0)
    {
        Index = Length_Of_String + Index;
    }
    for (String_Index = 0; String_Index < Length_Of_String; String_Index ++)
    {
        *(Temp_Buffer + String_Index) = *(String + String_Index);
    } 

    String_Index = Index;
    for (Data_Index = 0; Data_Index < Length_Of_Data; Data_Index++)
    {
        *(String + String_Index + Data_Index) = *(Data + Data_Index);
    }
    String_Index = Index + Length_Of_Data;
    for (uint8_t Remain_Index = 0; Remain_Index < Length_Of_String - Index; Remain_Index ++)
    {
        *(String + String_Index + Remain_Index) = *(Temp_Buffer + Index + Remain_Index);
    }

}