#include <stdint.h>
#include <string.h>

uint8_t String_Compare(char* String1, char* String2);
uint8_t String_Check_Data_In_String(char * String, char *Data);
int8_t String_Find_Index_Of_Character(char *String, char *Character);
int16_t String_Convert_String_To_Number(char *String);
void String_Convert_Number_To_String(char *String_Result, float Number);
void String_Assign_Value_To_String(char *Data,char *String);
void String_Append_String(char *Data, char *String);
void String_Insert_Data_To_String(char *Data, char *String, int8_t Index);