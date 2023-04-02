/*
 * Project MemStoreTestingv2
 * Description:
 * Author:
 * Date:
 */


#include <math.h>

int color;
byte data [] = {0x23, 0x42, 0x41, 0x34, 0x32, 0x35, 0x44, 0x39, 0x35};
byte buf [6];


 /* memcpy () - copy from specific memory locations to new locations
 * memcpy (to , from , size );
 * to -> pointer to starting address of where to copy to
 * from -> pointer to starting address of where to copy from
 * size -> number of bytes to copy
 */

SYSTEM_MODE(SEMI_AUTOMATIC);



void setup()
{


 memcpy(buf, & data[1], 6); // copy bytes 1 through 6 and place in buf
}

void loop () {
 /* ( char *) - typecasting a data type to a char - type pointer */

 Serial.printf(" Converting the data array to ascii symbols returns %s ,\n" ,(char *) data);

 delay(3000);


 /* strtol () - string to long - similar to atoi ()
 * strtol ( charString , end , base )
 * charString -> string that contains number to be converted
 * end -> character to end conversion on ( set to NULL )
 * base -> base of integer (16 for hex )
 */

 color = strtol((char*) buf, NULL, 16); // convert string to int (hex)
}