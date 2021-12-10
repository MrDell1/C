#include "file_reader.h"
#include <errno.h>
#include "tested_declarations.h"
#include "rdebug.h"
#include "tested_declarations.h"
#include "rdebug.h"


int disks_open = 0;
int files_open = 0;
int dirs_open = 0;
int entry_open = 0;

struct disk_t *disk_open_from_file(const char *volume_file_name) {
    if(volume_file_name == NULL){
        errno = EFAULT;
        return NULL;
    }
    struct disk_t *disk_struct;

    disk_struct = (struct disk_t *) calloc(disks_open + 1, sizeof(struct disk_t));

    if(disk_struct == NULL){
        errno = ENOMEM;
        return NULL;
    }
    disk_struct->disk = fopen(volume_file_name, "rb");
    if (disk_struct->disk) {

        return (disk_struct + disks_open);
    }
    free(disk_struct);
    errno = ENOENT;
    return NULL;
}

int disk_read(struct disk_t* pdisk, int32_t first_sector, void* buffer, int32_t sectors_to_read){
    if(pdisk == NULL || buffer == NULL){
       errno = EFAULT;
        return -1;
    }

    FILE *disk = pdisk->disk;
    fseek(disk, first_sector * 512,SEEK_SET);
    fread(buffer, sectors_to_read * 512, 1, disk);
    return sectors_to_read;
}

int disk_close(struct disk_t* pdisk){
    if (pdisk != NULL){
        fclose(pdisk->disk);
        free((pdisk+disks_open));
        return 0;
    }
    errno = EFAULT;
    return -1;
}

struct volume_t* fat_open(struct disk_t* pdisk, uint32_t first_sector){
    if(pdisk != NULL){
        if(first_sector == 0) {
            struct volume_t *volume;
            volume = (struct volume_t *) calloc(disks_open + 1, sizeof(struct volume_t));
            if(volume == NULL){
                errno = ENOMEM;
                return NULL;
            }
            struct reserved_area *reserved = calloc(disks_open + 1, sizeof(struct reserved_area));
            if(reserved == NULL){
                free(volume);
                errno = ENOMEM;
                return NULL;
            }
            struct volume_t *vol = (volume + disks_open);
            vol->reserved = reserved + disks_open;
            disk_read(pdisk,0,vol->reserved, 1);
            if( reserved->signature_value != 0xaa55 || reserved->bytes <= 0){
                free(vol);
                free(reserved);
                errno = EINVAL;
                return NULL;
            }

            fseek(pdisk->disk,(reserved->bytes * reserved->size_reserved_area), SEEK_SET);
            //vol->fat_area = (uint8_t *) ftell(pdisk->disk);
            if(reserved->num_of_sectors == 0){
                vol->total_sectors = reserved->num_of_sectors_in_file;
            }
            else {
                vol->total_sectors = reserved->num_of_sectors;
            }
            vol->disk = pdisk;
            vol->fat_size = (reserved->bytes * reserved->size_of_each_fat * reserved->number_of_fats);
            vol->root_dir_sectors = reserved->size_reserved_area * reserved->bytes + vol->fat_size;
            vol->first_data_sector = vol->fat_size + vol->root_dir_sectors - vol->fat_size + reserved->max_num * 32;
            vol->first_fat_sector = vol->reserved->size_reserved_area;
            vol->data_sectors = reserved->max_num;
            vol->total_clusters = vol->total_sectors/vol->reserved->sector_per_cluster;

            //int32_t sec_to_read = reserved->number_of_fats * reserved->size_of_each_fat;
            vol->fat_area = calloc(vol->reserved->number_of_fats * vol->reserved->size_of_each_fat * vol->reserved->bytes, sizeof(uint16_t));
            if(vol->fat_area == NULL){
                free(vol);
                free(reserved);
                errno = EINVAL;
                return NULL;
            }
            disk_read(pdisk,vol->first_fat_sector, vol->fat_area,(int32_t)(vol->reserved->number_of_fats * vol->reserved->size_of_each_fat));
            /*fseek(pdisk->disk, vol->first_fat_sector, SEEK_SET);
            for(int i = 0; i < sec_to_read * reserved->bytes; i++){
                fread(&vol->fat_area[i], 16, 1,pdisk->disk);

            }*/
            return vol;
        }
    }
    errno = EFAULT;
    return NULL;
}

int fat_close(struct volume_t* pvolume){
    if(pvolume != NULL){
        free(pvolume->reserved);
        free(pvolume->fat_area);
        free(pvolume);
        return 0;
    }
    errno = EFAULT;
    return -1;
}

char *remove_white_spaces(char *str)
{
    int i = 0, j = 0;
    while (str[i])
    {
        if (str[i] != ' ')
        str[j++] = str[i];
        i++;
    }
    str[j] = '\0';
    return str;
}

struct file_t* file_open(struct volume_t* pvolume, const char* file_name){
    if(pvolume != NULL && file_name != NULL){
        struct file_t *file = calloc(files_open + 1, sizeof(struct file_t));
        if(file == NULL){
            errno = ENOMEM;
            return NULL;
        }
        fseek(pvolume->disk->disk, pvolume->root_dir_sectors, SEEK_SET);
        char name[13];
        if(strchr(file_name,'.') != NULL) {
            fread(name, 7, 1, pvolume->disk->disk);
            name[7] = '.';
            for (int i = 0; i < 4; i++) {
                name[8 + i] = (char) fgetc(pvolume->disk->disk);
            }

            name[12] = '\0';
        }
        else{
            fread(name,11,1,pvolume->disk->disk);
            name[11] = '\0';
        }
        while(strcmp(remove_white_spaces(name), file_name) != 0){
            fseek(pvolume->disk->disk, 32 - 11, SEEK_CUR);
            if(ftell(pvolume->disk->disk) > pvolume->first_data_sector){
                free(file);
                errno = ENOENT;
                return NULL;
            }
            if(strchr(file_name,'.') != NULL) {
                fread(name, 8, 1, pvolume->disk->disk);
                name[8] = '.';
                for (int i = 0; i < 3; i++) {
                    name[9 + i] = (char) fgetc(pvolume->disk->disk);
                }

                name[12] = '\0';
            }
            else{
                fread(name,11,1,pvolume->disk->disk);
                name[11] = '\0';
            }

        }
        struct file_t *f = (file + files_open);
        f->disk = pvolume->disk;
        f->vol = pvolume;
        fseek(pvolume->disk->disk, - 11, SEEK_CUR);
        f->f_beginning = ftell(pvolume->disk->disk);
        fread(f, 32, 1, pvolume->disk->disk);
        if(f->flag >= 0x10 && f->file_size == 0){
            free(f);
            errno = EISDIR;
            return NULL;
        }
        f->is_reading=0;
        f->cluster_read = 0;
        int32_t f_sector = (int32_t)((f->low_order * f->vol->reserved->sector_per_cluster )+ (f->vol->first_data_sector/f->vol->reserved->bytes))  ;
        fseek(f->disk->disk, (f_sector-(2 * f->vol->reserved->sector_per_cluster)) * f->vol->reserved->bytes, SEEK_SET);
        return f;
    }
    errno = EFAULT;
    return NULL;
}

int file_close(struct file_t* stream){
    if(stream != NULL){
        if(stream->vol->fat_area != NULL) {
            free(stream->vol->fat_area);
            stream->vol->fat_area = NULL;
        }
        if(stream->vol->reserved != NULL) {
            free(stream->vol->reserved);
            stream->vol->reserved = NULL;
        }
        free(stream);
        return 0;
    }
    errno = EFAULT;
    return -1;
}

size_t file_read(void *ptr, size_t size, size_t nmemb, struct file_t *stream){
    if(ptr != NULL && stream != NULL){
        if(stream->flag ==  0x10){
            errno = EFAULT;
            return -1;
        }



        if((int)(size * nmemb ) < 0){
            errno = EFAULT;
            return -1;
        }
        else if(size * nmemb >= stream->file_size){
            int j = 0;
            unsigned int id = stream->low_order;

            while(stream->vol->fat_area[id] < 0xfff8){


                int32_t f_sector = (int32_t)((id * stream->vol->reserved->sector_per_cluster )+ (stream->vol->first_data_sector/stream->vol->reserved->bytes))  ;
                disk_read(stream->disk, f_sector - (2 * stream->vol->reserved->sector_per_cluster), ((char*)ptr + (stream->vol->reserved->bytes * stream->vol->reserved->sector_per_cluster * j)), stream->vol->reserved->sector_per_cluster);

                uint16_t value = stream->vol->fat_area[id];
                id = value;
                if(stream->vol->fat_area[id] >= 0xfff8){
                    j++;
                    f_sector = (int32_t)((id * stream->vol->reserved->sector_per_cluster )+ (stream->vol->first_data_sector/stream->vol->reserved->bytes));
                    fseek(stream->disk->disk, (f_sector -(2 * stream->vol->reserved->sector_per_cluster))* stream->vol->reserved->bytes, SEEK_SET);
                    fread(((char*)ptr + (stream->vol->reserved->bytes * stream->vol->reserved->sector_per_cluster * j)), stream->file_size - (stream->vol->reserved->bytes * stream->vol->reserved->sector_per_cluster * j), 1,stream->disk->disk);
                    //disk_read(stream->disk, f_sector - 2, ((char*)ptr + (stream->vol->reserved->bytes * stream->vol->reserved->sector_per_cluster * j)), (int32_t)(stream->file_size - (stream->vol->reserved->bytes * stream->vol->reserved->sector_per_cluster * (j-1)))*(1/stream->vol->reserved->bytes));
                    return stream->file_size;
                }

                j++;
            }
            if(stream->vol->fat_area[id] >= 0xfff8){
                int32_t f_sector = (int32_t)((id * stream->vol->reserved->sector_per_cluster )+ (stream->vol->first_data_sector/stream->vol->reserved->bytes));
                fseek(stream->disk->disk, (f_sector -(2 * stream->vol->reserved->sector_per_cluster))* stream->vol->reserved->bytes, SEEK_SET);
                fread(((char*)ptr + (stream->vol->reserved->bytes * stream->vol->reserved->sector_per_cluster * j)), stream->file_size - (stream->vol->reserved->bytes * stream->vol->reserved->sector_per_cluster * j), 1,stream->disk->disk);

            }

            return stream->file_size;

        }
        else if(nmemb*size == 1){
            if(stream->is_reading == 0){
               /* int32_t f_sector = (int32_t)((stream->low_order * stream->vol->reserved->sector_per_cluster )+ (stream->vol->first_data_sector/stream->vol->reserved->bytes))  ;
                fseek(stream->disk->disk, (f_sector-2) * stream->vol->reserved->bytes, SEEK_SET);
                */stream->is_reading ++;
            }
            else if(stream->is_reading != 1 && (uint32_t)stream->is_reading < stream->file_size && (stream->is_reading-1) % (stream->vol->reserved->bytes * stream->vol->reserved->sector_per_cluster)  == 0){
                int32_t tell = ftell(stream->disk->disk);
                tell -= (stream->vol->reserved->bytes * stream->vol->reserved->sector_per_cluster);
                int32_t cluster = tell/(stream->vol->reserved->bytes * stream->vol->reserved->sector_per_cluster) - (stream->vol->first_data_sector/stream->vol->reserved->bytes / stream->vol->reserved->sector_per_cluster);
                if(stream->vol->fat_area[cluster + 2] >= 0xfff8){
                    return 0;
                }
                int32_t f_sector = (int32_t)(((stream->vol->fat_area[cluster + 2] ) * stream->vol->reserved->sector_per_cluster )+ (stream->vol->first_data_sector/stream->vol->reserved->bytes))  ;
                fseek(stream->disk->disk, (f_sector-(2 * stream->vol->reserved->sector_per_cluster)) * stream->vol->reserved->bytes, SEEK_SET);

            }
            else if((uint32_t)stream->is_reading > stream->file_size){
                return 0;
            }
            stream->is_reading++;
            return fread(ptr,size,nmemb,stream->disk->disk);
        }
        else if(nmemb*size <= stream->vol->reserved->bytes){
            if(stream->is_reading != 0 && (uint32_t)stream->is_reading < stream->file_size && (stream->is_reading) % (stream->vol->reserved->bytes * stream->vol->reserved->sector_per_cluster) == 0){
                int32_t tell = ftell(stream->disk->disk);
                tell -= (stream->vol->reserved->bytes * stream->vol->reserved->sector_per_cluster);
                int32_t cluster = tell/(stream->vol->reserved->bytes * stream->vol->reserved->sector_per_cluster) - (stream->vol->first_data_sector/stream->vol->reserved->bytes / stream->vol->reserved->sector_per_cluster);
                if(stream->vol->fat_area[cluster + 2] >= 0xfff8){
                    return 0;
                }
                int32_t f_sector = (int32_t)(((stream->vol->fat_area[cluster + 2] ) * stream->vol->reserved->sector_per_cluster )+ (stream->vol->first_data_sector/stream->vol->reserved->bytes))  ;
                fseek(stream->disk->disk, (f_sector-(2 * stream->vol->reserved->sector_per_cluster)) * stream->vol->reserved->bytes, SEEK_SET);

            }
            else if((uint32_t)stream->is_reading + size*nmemb > stream->file_size){
                return 0;
            }

            else if((uint32_t)stream->is_reading + size*nmemb > stream->vol->reserved->bytes * stream->vol->reserved->sector_per_cluster){
                int read =(stream->vol->reserved->bytes * stream->vol->reserved->sector_per_cluster-stream->is_reading);
                int32_t tell_v2 = ftell(stream->disk->disk);
                fread(ptr, 1, read, stream->disk->disk);
                int32_t tell = ftell(stream->disk->disk);
                int read_v2 = tell - tell_v2;
                tell -= (stream->vol->reserved->bytes * stream->vol->reserved->sector_per_cluster);
                int32_t cluster = tell/(stream->vol->reserved->bytes * stream->vol->reserved->sector_per_cluster) - (stream->vol->first_data_sector/stream->vol->reserved->bytes / stream->vol->reserved->sector_per_cluster);
                if(stream->vol->fat_area[cluster + 2] >= 0xfff8){
                    return 0;
                }
                int32_t f_sector = (int32_t)(((stream->vol->fat_area[cluster + 2] ) * stream->vol->reserved->sector_per_cluster )+ (stream->vol->first_data_sector/stream->vol->reserved->bytes))  ;
                fseek(stream->disk->disk, (f_sector-(2 * stream->vol->reserved->sector_per_cluster)) * stream->vol->reserved->bytes, SEEK_SET);
                stream->cluster_read += stream->vol->reserved->bytes * stream->vol->reserved->sector_per_cluster;
                stream->is_reading = (size*nmemb) - read_v2 ;

                return fread((char*)ptr + read_v2, (size*nmemb)-read_v2, 1,stream->disk->disk);
            }
            stream->is_reading += size*nmemb;
            if((uint32_t)stream->cluster_read + stream->is_reading >= stream->file_size){
                fread(ptr,stream->file_size - ((uint32_t)stream->cluster_read + stream->is_reading - size*nmemb),1,stream->disk->disk);
                return 0;
            }


            return fread(ptr,size,nmemb,stream->disk->disk);
        }

    }
    errno = EFAULT;
    return -1;
}

int32_t file_seek(struct file_t* stream, int32_t offset, int whence){
    if(stream != NULL){
        if(whence != SEEK_SET && whence != SEEK_CUR && whence != SEEK_END){
            errno = EINVAL ;
            return -1;
        }
        if(whence == SEEK_END){
            if(offset < 0) {
                int32_t off = stream->file_size + offset;
                int32_t cluster = off / (stream->vol->reserved->bytes * stream->vol->reserved->sector_per_cluster);
                unsigned int id = stream->low_order;

                for (int i = 0; i < cluster; i++) {

                    uint16_t value = stream->vol->fat_area[id];
                    id = value;
                }
                int32_t f_sector = (int32_t) ((id * stream->vol->reserved->sector_per_cluster) +
                                              (stream->vol->first_data_sector / stream->vol->reserved->bytes));
                f_sector -= (2 * stream->vol->reserved->sector_per_cluster);
                fseek(stream->disk->disk, f_sector * stream->vol->reserved->bytes, SEEK_SET);
                int32_t rest_off;
                if(stream->file_size >= stream->vol->reserved->bytes * stream->vol->reserved->sector_per_cluster) {
                    rest_off = off - (stream->vol->reserved->bytes * stream->vol->reserved->sector_per_cluster * cluster);

                }
                else{
                    rest_off = stream->file_size;
                    rest_off += offset;
                }
                fseek(stream->disk->disk, rest_off, SEEK_CUR);
                return offset;
            }
            errno = ENXIO;
            return -1;
        }
        if(whence == SEEK_SET){
            SET:;
            if(offset >= stream->vol->reserved->sector_per_cluster * stream->vol->reserved->bytes){

                int32_t cluster = offset / (stream->vol->reserved->bytes * stream->vol->reserved->sector_per_cluster);
                unsigned int id = stream->low_order;

                for (int i = 0; i < cluster; i++) {

                    uint16_t value = stream->vol->fat_area[id];
                    id = value;
                }
                int32_t f_sector = (int32_t) ((id * stream->vol->reserved->sector_per_cluster) +
                                              (stream->vol->first_data_sector / stream->vol->reserved->bytes));

                fseek(stream->disk->disk, (f_sector - (2 * stream->vol->reserved->sector_per_cluster)) * stream->vol->reserved->bytes, SEEK_SET);
                int32_t rest_off;
                rest_off = offset - (stream->vol->reserved->bytes * stream->vol->reserved->sector_per_cluster * cluster);

                fseek(stream->disk->disk, rest_off , SEEK_CUR);
                stream->is_reading = offset;
                return offset;

            }
            else{
                unsigned int id = stream->low_order;
                int32_t f_sector = (int32_t) ((id * stream->vol->reserved->sector_per_cluster) +
                                              (stream->vol->first_data_sector / stream->vol->reserved->bytes));
                f_sector -= (2 * stream->vol->reserved->sector_per_cluster);
                fseek(stream->disk->disk, f_sector * stream->vol->reserved->bytes, SEEK_SET);
                fseek(stream->disk->disk, offset, SEEK_CUR);
                return offset;
            }
        }
        if(whence == SEEK_CUR){
            //int32_t temp_offset = offset;
            offset += stream->is_reading;
            goto SET;
        }


        if(fseek(stream->disk->disk, offset, whence) != 0){
            errno = ENXIO;
            return -1;
        }
        int32_t tell = ftell(stream->disk->disk);
        if(tell < stream->vol->first_data_sector){
            errno = ENXIO;
            return -1;
        }
        else{
            return tell;
        }
    }
    errno = EFAULT;
    return -1;
}

struct dir_t* dir_open(struct volume_t* pvolume, const char* dir_path){
    if(pvolume != NULL && strcmp(dir_path, "\\") == 0){
        struct dir_t *dir = calloc(dirs_open + 1, sizeof(struct dir_t));
        if(dir == NULL){
            errno = ENOMEM;
            return NULL;
        }
        fseek(pvolume->disk->disk, pvolume->root_dir_sectors, SEEK_SET);
        dir->dir_sectors = pvolume->root_dir_sectors;
        dir->disk = pvolume->disk;
        dir->vol = pvolume;
        /*char name[11];
        fread(name, 11, 1, pvolume->disk->disk);
        while(strcmp(name, dir_path) != 0){
            fseek(pvolume->disk->disk, 32 - 11, SEEK_CUR);
            if(ftell(pvolume->disk->disk) > pvolume->first_data_sector){
                errno = ENOENT;
                return NULL;
            }
            fread(name, 11, 1, pvolume->disk->disk);
        }
        struct dir_t *d = (dir + dirs_open);
        fseek(pvolume->disk->disk, - 11, SEEK_CUR);
        d->f_beginning = ftell(pvolume->disk->disk);
        fread(d, sizeof(struct dir_t) - sizeof(d->f_beginning) - sizeof(d->disk) - sizeof(d->vol), 1, pvolume->disk->disk);
        if(d->flag != 0x10){
            errno = ENOTDIR;
            return NULL;
        }*/
        return dir;
    }
    errno = EFAULT;
    return NULL;
}

int dir_read(struct dir_t* pdir, struct dir_entry_t* pentry){
    if(pdir != NULL && pentry != NULL){


        if(entry_open == 0) {
            fseek(pdir->disk->disk, pdir->dir_sectors, SEEK_SET);
        }
        char name[13];
        for(int x = 1; x < pdir->vol->reserved->max_num - entry_open; x++) {
            fread(name, 11, 1, pdir->disk->disk);
            if (name[0] == 0 || name[0] == -27) {
                goto next;
            } else if (name[8] != 32) {
                fseek(pdir->disk->disk, -11, SEEK_CUR);
                fread(name, 8, 1, pdir->disk->disk);
                name[8] = '.';
                for (int j = 0; j < 3; j++) {
                    name[9 + j] = (char) fgetc(pdir->disk->disk);
                }
                name[12] = '\0';
            } else {
                name[8] = '\0';
            }
            char *n = remove_white_spaces(name);
            strcpy(pentry->name, n);
            fread(pentry, 32 - 11, 1, pdir->disk->disk);
            entry_open++;
            return 0;

            next:;
            fseek(pdir->disk->disk, 32 - 11, SEEK_CUR);
            int32_t tell = ftell(pdir->disk->disk);
            if(tell >= pdir->vol->first_data_sector){
                return 1;
            }
        }
        return 1;


    }
    errno = EFAULT;
    return -1;
}
int dir_close(struct dir_t* pdir){
    if(pdir != NULL){
        free(pdir);
    }
    errno = EFAULT;
    return -1;
}






