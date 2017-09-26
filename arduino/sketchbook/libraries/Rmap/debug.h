#ifndef _DEBUG_H
#define _DEBUG_H

#include <stdarg.h>
#include <stdio.h>
#include <LiquidCrystal_I2C.h>

// Debug level definitions
// #define SERIAL_TRACE_LEVEL_OFF          (0)
// #define SERIAL_TRACE_LEVEL_ERROR        (1)
// #define SERIAL_TRACE_LEVEL_WARNING      (2)
// #define SERIAL_TRACE_LEVEL_INFO         (3)
// #define SERIAL_TRACE_LEVEL_DEBUG        (4)
// #define SERIAL_TRACE_LEVEL_TRACE        (5)

#define INT8    (1)
#define INT16   (2)
#define INT32   (3)
#define UINT8   (4)
#define UINT16  (5)
#define UINT32  (6)
#define FLOAT   (7)

#define DEBUG_WAIT_FOR_SLEEP_MS              (10)

#define SERIAL_PRINTF_BUFFER_LENGTH          (256)
#define LCD_PRINTF_BUFFER_LENGTH             (20)

char *serial_printf(char *ptr, const char *fmt, ...);
char *serial_printf_array(void *data, int16_t length, uint8_t type, const char *fmt, ...);

// Default Debug level
#ifndef SERIAL_TRACE_LEVEL
   #define SERIAL_TRACE_LEVEL SERIAL_TRACE_LEVEL_OFF
#endif

// Debug output redirection
#if (SERIAL_TRACE_LEVEL > SERIAL_TRACE_LEVEL_OFF)
  #ifndef _SERIAL_PRINT
  #define _SERIAL_PRINT(...) Serial.print(serial_printf(__VA_ARGS__))
  #endif
  #ifndef _SERIAL_PRINT_ARRAY
  #define _SERIAL_PRINT_ARRAY(...) Serial.print(serial_printf_array(__VA_ARGS__))
  #endif
  #ifndef SERIAL_BEGIN
  #define SERIAL_BEGIN(...) Serial.begin(__VA_ARGS__)
  #endif
#else
  #ifndef SERIAL_BEGIN
    #define SERIAL_BEGIN(...)
  #endif
#endif

// Debugging macros
#if (SERIAL_TRACE_LEVEL >= SERIAL_TRACE_LEVEL_ERROR)
  #define SERIAL_ERROR(...) _SERIAL_PRINT(NULL, __VA_ARGS__)
  #define SERIAL_ERROR_ARRAY(...) _SERIAL_PRINT_ARRAY(__VA_ARGS__)
#else
  #define SERIAL_ERROR(...)
  #define SERIAL_ERROR_ARRAY(...)
#endif

#if (SERIAL_TRACE_LEVEL >= SERIAL_TRACE_LEVEL_WARNING)
  #define SERIAL_WARNING(...) _SERIAL_PRINT(NULL, __VA_ARGS__)
  #define SERIAL_WARNING_ARRAY(...) _SERIAL_PRINT_ARRAY(__VA_ARGS__)
#else
  #define SERIAL_WARNING(...)
  #define SERIAL_WARNING_ARRAY(...)
#endif

#if (SERIAL_TRACE_LEVEL >= SERIAL_TRACE_LEVEL_INFO)
  #define SERIAL_INFO(...) _SERIAL_PRINT(NULL, __VA_ARGS__)
  #define SERIAL_INFO_ARRAY(...) _SERIAL_PRINT_ARRAY(__VA_ARGS__)
#else
  #define SERIAL_INFO(...)
  #define SERIAL_INFO_ARRAY(...)
#endif

#if (SERIAL_TRACE_LEVEL >= SERIAL_TRACE_LEVEL_DEBUG)
  #define SERIAL_DEBUG(...) _SERIAL_PRINT(NULL, __VA_ARGS__)
  #define SERIAL_DEBUG_ARRAY(...) _SERIAL_PRINT_ARRAY(__VA_ARGS__)
#else
  #define SERIAL_DEBUG(...)
  #define SERIAL_DEBUG_ARRAY(...)
#endif

#if (SERIAL_TRACE_LEVEL >= SERIAL_TRACE_LEVEL_TRACE)
  #define SERIAL_TRACE(...) _SERIAL_PRINT(NULL, __VA_ARGS__)
  #define SERIAL_TRACE_ARRAY(...) _SERIAL_PRINT_ARRAY(__VA_ARGS__)
#else
  #define SERIAL_TRACE(...)
  #define SERIAL_TRACE_ARRAY(...)
#endif

// Default Debug level
#ifndef LCD_TRACE_LEVEL
   #define LCD_TRACE_LEVEL LCD_TRACE_LEVEL_OFF
#endif

void lcd_begin(LiquidCrystal_I2C *lcd, uint8_t max_cols, uint8_t max_rows);
char *lcd_printf(LiquidCrystal_I2C *lcd, bool do_clear, char *ptr, const char *fmt, ...);

// Debug output redirection
#if (LCD_TRACE_LEVEL > LCD_TRACE_LEVEL_OFF)

  #ifndef _LCD_PRINT
   #define _LCD_PRINT(lcd, do_clear, ...) (((LiquidCrystal_I2C *) lcd)->print(lcd_printf(lcd, do_clear, NULL, __VA_ARGS__)))
  #endif

  #ifndef LCD_BEGIN
   #define LCD_BEGIN(lcd, max_cols, max_rows) (lcd_begin(lcd, max_cols, max_rows))
  #endif
#else
  #ifndef LCD_BEGIN
   #define LCD_BEGIN(...)
  #endif
#endif

// Debugging macros
#if (LCD_TRACE_LEVEL >= LCD_TRACE_LEVEL_ERROR)
  #define LCD_ERROR(...) _LCD_PRINT(__VA_ARGS__)
#else
  #define LCD_ERROR(...)
#endif

#if (LCD_TRACE_LEVEL >= LCD_TRACE_LEVEL_WARNING)
  #define LCD_WARNING(...) _LCD_PRINT( __VA_ARGS__)
#else
  #define LCD_WARNING(...)
#endif

#if (LCD_TRACE_LEVEL >= LCD_TRACE_LEVEL_INFO)
  #define LCD_INFO(...) _LCD_PRINT(__VA_ARGS__)
#else
  #define LCD_INFO(...)
#endif

#if (LCD_TRACE_LEVEL >= LCD_TRACE_LEVEL_DEBUG)
  #define LCD_DEBUG(...) _LCD_PRINT( __VA_ARGS__)
#else
  #define LCD_DEBUG(...)
#endif

#if (LCD_TRACE_LEVEL >= LCD_TRACE_LEVEL_TRACE)
  #define LCD_TRACE(...) _LCD_PRINT(__VA_ARGS__)
#else
  #define LCD_TRACE(...)
#endif

#endif
