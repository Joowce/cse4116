//
// Created by 민지우 on 2019-04-12.
//

#ifndef EMBEDED_SHARED_MEMORY_H
#define EMBEDED_SHARED_MEMORY_H

#define SHM_ERROR   -1
#define SHM_SUCCESS 1

int write_shm (int, char*, int );
int remove_shm ();
void* create_shm();
char* get_shm_addr();

#endif //EMBEDED_SHARED_MEMORY_H
