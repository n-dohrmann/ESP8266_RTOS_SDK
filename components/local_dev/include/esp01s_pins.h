
// pin definitions for the esp01s module, see
// here: https://academy.cba.mit.edu/classes/networking_communications/ESP8266/esp01.pdf


// numeric definitions
#define ESP01S_GND_NUM 1
#define ESP01S_GPIO2_NUM 2
#define ESP01S_GPIO0_NUM 3
#define ESP01S_RX_NUM 4
#define ESP01S_VCC_NUM 5
#define ESP01S_RST_NUM 6
#define ESP01S_EN_NUM 7 // also called CH_PD
#define ESP01S_TX_NUM 8

// bitmask definitions
#ifndef BIT
#define BIT(x) (1 << (x))
#endif

#define ESP01S_GND_BIT BIT(1)
#define ESP01S_GPIO2_BIT BIT(2)
#define ESP01S_GPIO0_BIT BIT(3)
#define ESP01S_RX_BIT BIT(4)
#define ESP01S_VCC_BIT BIT(5)
#define ESP01S_RST_BIT BIT(6)
#define ESP01S_EN_BIT BIT(7)
#define ESP01S_TX_BIT BIT(8)
