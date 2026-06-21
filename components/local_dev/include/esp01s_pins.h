
// pin definitions for the esp01s module, see
// here: https://academy.cba.mit.edu/classes/networking_communications/ESP8266/esp01.pdf


// numeric definitions
#define ESP01S_GPIO0_NUM 0
#define ESP01S_TX_NUM 1
#define ESP01S_GPIO2_NUM 2
#define ESP01S_RX_NUM 3

// bitmask definitions
#ifndef BIT
#define BIT(x) (1 << (x))
#endif

#define ESP01S_GPIO0_BIT BIT(ESP01S_GPIO0_NUM)
#define ESP01S_TX_BIT BIT(ESP01S_TX_NUM)
#define ESP01S_GPIO2_BIT BIT(ESP01S_GPIO2_NUM)
#define ESP01S_RX_BIT BIT(ESP01S_RX_NUM)
