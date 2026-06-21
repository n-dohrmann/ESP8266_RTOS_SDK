
// other definitions
#ifndef GPIO_HIGH
#define GPIO_HIGH 1
#endif

#ifndef GPIO_LOW
#define GPIO_LOW 0
#endif

// definitions for dev (not build) environment on mac
#ifdef __APPLE__

#ifndef CONFIG_FREERTOS_HZ
#define CONFIG_FREERTOS_HZ 1000
#endif // CONFIG_FREERTOS_HZ

#ifndef _U32_T_IMPL
#define _U32_T_IMPL
typedef unsigned int u32_t;
#endif // _U32_T_IMPL

#ifndef _LOCAL_ESP_FILE_DEF
#define _LOCAL_ESP_FILE_DEF
#define __ESP_FILE__ "null"
#endif

#endif // __APPLE__
