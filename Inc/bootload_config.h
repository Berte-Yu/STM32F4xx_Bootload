#ifndef _BOOTLOAD_CONFIG_H
#define _BOOTLOAD_CONFIG_H

typedef struct
{
    uint32_t Status;
    uint32_t APP_ADD;               //APP的起始地址
    uint32_t APP_SIZE;              //APP的大小
    uint32_t DOWN_LOAD_ADD;         //下载区的起始地址
    uint32_t DOWN_LOAD_SIZE;        //下载区的大小
}BootLoad_PARAM;

#define default_APP_ADD             0x08008000  //默认的APP区起始地址
#define default_APP_SIZE            224*1024    //默认的APP大小是224KB
#define default_DOWN_LOAD_ADD       0x080C0000  //默认的下载区起始地址
#define default_DOWN_LOAD_SIZE      256*1024    //默认的下载区大小


#define GOTO_APP                    0x1122aabb  //运行APP
#define COPY_APP                    0x2233ccdd  //需要从下载区拷贝程序到APP区

#define BOOTLOAD_PARAM_ADD          0x08004000


#endif
