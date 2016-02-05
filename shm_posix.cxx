/*
 * shm_posix.cxx
 * 
 * Copyright 2016 olegartys <olegartys@olegartys-HP-Pavilion-15-Notebook-PC>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


#include <iostream>

#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

#define MB 1024*1024

int main(int argc, char **argv)
{
	int shm_id = shm_open("/test.shm", O_CREAT | O_RDWR, 0666);
	if (shm_id < 0) {
		perror("shm_open");
		exit(errno);
	}
	
	int ret = ftruncate(shm_id, 1*MB);
	if (ret < 0) {
		perror("ftruncate");
		exit(errno);
	}
	
	void* membase = mmap(NULL, 1*MB, PROT_WRITE, MAP_SHARED, shm_id, 0);
	if (membase == MAP_FAILED) {
		perror("mmap");
		exit(errno);
	}
	
	for (int i = 0; i < MB; ++i)
		*((char*)membase+i) = 13;
	
	munmap(membase, 1*MB);
	//shm_unlink("/test.shm");
	return 0;
}

