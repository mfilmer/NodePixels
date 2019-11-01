#include "WiFiUtil.h"



/*
 * @brief Read a single byte from the client
 */
static bool readByte(WiFiClient &client, char *byte, unsigned int timeout)
{
  return readBytes(client, byte, 1, timeout);
}


/*
 * @brief Read a specified number of bytes from the client
 */
static bool readBytes(WiFiClient &client, char* bytes, char nBytes, unsigned int timeout)
{
  unsigned long currentTime = millis();
  unsigned long startTime = currentTime;
  unsigned int i = 0;
  while (client.connected() && currentTime - startTime < TIMEOUT && i < nBytes) {
    if(client.available()) {
      bytes[i] = client.read();
      i++;
    }
    currentTime = millis();
  }

  if (i == nBytes) {
    return true;
  } else {
    return false;
  }
}
