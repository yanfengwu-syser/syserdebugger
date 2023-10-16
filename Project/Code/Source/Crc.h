#ifndef __CRC__H__
#define __CRC__H__

unsigned int crc16_ccitt(const char *buffer, unsigned int length);
unsigned int crc32(const char* buffer, unsigned int length);
unsigned int crc16(const char* buffer, unsigned int length);
extern const unsigned int crc32_table[256];
extern const unsigned int  crc16_table[256];
extern const unsigned short crc16table_ccitt[256];
#endif //__CRC__H__