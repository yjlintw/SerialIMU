#ifndef SerialPrint_h
#define SerialPrint_h

#include "Arduino.h"
#include "avr/pgmspace.h"
#include <stdarg.h>

static void StreamPrint_progmem(Print &out, PGM_P format, ...) {
    // program memory version of printf - copy of format string and result share a buffer
    // so as to avoid too much memory use
    char formatString[128], *ptr;
    strncpy_P( formatString, format, sizeof(formatString) ); // copy in from program mem
    // null terminate - leave last char since we might need it in worst case for result's \0
    formatString[ sizeof(formatString)-2 ]='\0'; 
    ptr=&formatString[ strlen(formatString)+1 ]; // our result buffer...
    va_list args;
    va_start (args,format);
    vsnprintf(ptr, sizeof(formatString)-1-strlen(formatString), formatString, args );
    va_end (args);
    formatString[ sizeof(formatString)-1 ]='\0'; 
    out.print(ptr);
}

// static void Serialprint(PGM_P format, ...) {
//     va_list args;
//     va_start(args, format);
//     StreamPrint_progmem(Serial, format, args);
//     va_end(args);
// }

#define Serialprint(format, ...) StreamPrint_progmem(Serial,PSTR(format),##__VA_ARGS__)
#define Streamprint(stream,format, ...) StreamPrint_progmem(stream,PSTR(format),##__VA_ARGS__)


#endif
