#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifndef PROJECT1_FILE_READER_H
#define PROJECT1_FILE_READER_H

struct disk_t{

    FILE *disk;

};

struct  __attribute__((packed)) reserved_area{
    //Boot sector 0-35
    char assembly_code[3];
    char name[8];
    uint16_t bytes;
    uint8_t sector_per_cluster;
    uint16_t size_reserved_area;
    uint8_t number_of_fats;
    uint16_t max_num;
    uint16_t num_of_sectors;
    uint8_t media_type;
    uint16_t size_of_each_fat;
    uint16_t sectors_per_truck;
    uint16_t num_of_heads;
    uint32_t num_of_sectors_b_start;
    uint32_t num_of_sectors_in_file;
    //Boot sector 36-511
    uint8_t bios;
    uint8_t not_used;
    uint8_t extended_boot;
    uint32_t volume_serial;
    char volume_label[11];
    char file_system_type[8];
    char xxx[448];
    uint16_t signature_value;
};
struct  __attribute__((packed)) volume_t{
    struct reserved_area *reserved;
    struct disk_t *disk;

    uint16_t *fat_area;

    uint16_t total_sectors;
    int32_t fat_size;
    uint16_t root_dir_sectors;
    uint16_t first_data_sector;
    uint16_t first_fat_sector;
    uint32_t data_sectors;
    uint32_t total_clusters;
};

struct __attribute__((packed)) file_t{
    char name[11];
    uint8_t flag;
    uint8_t reserved;
    uint8_t time_sec;
    uint16_t time_hours;
    uint16_t creation_date;
    uint16_t access_date;
    uint16_t high_order;
    uint16_t modified_time;
    uint16_t modified_date;
    uint16_t low_order;
    uint32_t file_size;
    uint8_t f_beginning;
    struct disk_t *disk;
    struct volume_t *vol;
    int is_reading;
    int cluster_read;
};

struct dir_t{
    uint16_t dir_sectors;
    struct disk_t *disk;
    struct volume_t *vol;
};
struct dir_entry_t{

    uint8_t flag;
    uint8_t reserved;
    uint8_t time_sec;
    uint16_t time_hours;
    uint16_t creation_date;
    uint16_t access_date;
    uint16_t high_order;
    uint16_t modified_time;
    uint16_t modified_date;
    uint16_t low_order;
    uint32_t file_size;
    char name[13];
};

struct disk_t* disk_open_from_file(const char* volume_file_name);
int disk_read(struct disk_t* pdisk, int32_t first_sector, void* buffer, int32_t sectors_to_read);
int disk_close(struct disk_t* pdisk);


struct volume_t* fat_open(struct disk_t* pdisk, uint32_t first_sector);
int fat_close(struct volume_t* pvolume);

struct file_t* file_open(struct volume_t* pvolume, const char* file_name);
int file_close(struct file_t* stream);
size_t file_read(void *ptr, size_t size, size_t nmemb, struct file_t *stream);
int32_t file_seek(struct file_t* stream, int32_t offset, int whence);

struct dir_t* dir_open(struct volume_t* pvolume, const char* dir_path);
int dir_read(struct dir_t* pdir, struct dir_entry_t* pentry);
int dir_close(struct dir_t* pdir);
#endif //PROJECT1_FILE_READER_H
