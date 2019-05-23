//
// Created by 민지우 on 2019-04-12.
//
#include <sys/shm.h>
#include <stdio.h>
#include <string.h>

#include "shared_memory.h"
#include "../log/log.h"

#define SHM_KEY 980218
#define SIZE    1024

static int shmid = -1;
static void * shmaddr = NULL;

/**
 * detach and remove shared memory
 * @return
 */
int remove_shm () {
    if (shmid == -1) return SHM_SUCCESS;

    if (shmaddr != NULL) {
        if (shmdt(shmaddr) == -1) {
            LOG_ERROR("shm:: Fail to detach shared memory");
        } else {
            shmaddr = NULL;
        }
    }

    if (shmctl(shmid, IPC_RMID, 0) == -1) {
        LOG_ERROR("shm:: Fail to remove shared memory");
        return SHM_ERROR;
    }

    LOG_INFO("shm:: Success to remove shared memory");
    return SHM_SUCCESS;
}

/**
 * create shared memory
 * @return
 */
void* create_shm() {
    if (shmaddr != NULL) return shmaddr;

    shmid = shmget(SHM_KEY, SIZE, IPC_CREAT | 0666);

    if (shmid == -1) {
        LOG_ERROR("shm:: Fail to create shared memory");
        return NULL;
    }

    shmaddr = shmat(shmid, (void *)0, 0);

    if (shmaddr == (void *)-1) {
        LOG_ERROR("shm:: Fail to add shared memory");
        remove_shm();
        return NULL;
    }

    LOG_INFO("shm:: Success to create and attach shared memory");
    return shmaddr;
}

int write_shm (int addr, char* data, int size) {
    memcpy(shmaddr+addr, data, size);
    return SHM_SUCCESS;
}

char* get_shm_addr() {
    return (char *)shmaddr;
}