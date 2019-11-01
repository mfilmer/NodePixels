#ifndef __WIFIUTIL_H__
#define __WIFIUTIL_H__


static bool readByte(WiFiClient &client, char *byte, unsigned int timeout);
static bool readBytes(WiFiClient &client, char* bytes, char nBytes, unsigned int timeout);


#endif
