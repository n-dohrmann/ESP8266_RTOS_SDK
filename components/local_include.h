
// misc defines that were not pre-included anywhere else

#ifndef CONFIG_FREERTOS_HZ
#define CONFIG_FREERTOS_HZ 1000
#endif // CONFIG_FREERTOS_HZ

#ifndef _U32_T_IMPL
#define _U32_T_IMPL
typedef unsigned int u32_t;
#endif // _U32_T_IMPL

#ifndef _LOCAL_ESP_FILE_DEF
#define __ESP_FILE__ "null"
#endif _LOCAL_ESP_FILE_DEF
