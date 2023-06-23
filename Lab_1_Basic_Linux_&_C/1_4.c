// Collin Paiz
// 5 January 2022
// Lab 1 - Steps 1-3
// The following C program takes an integer argument that specifies how many files are to be copied using standard fread and fwrite functions using threads.

#include <stdio.h>   // fprintf(), fread(), fwrite(), fopen(), fclose()
#include <stdlib.h>  // malloc(), free()
#include <pthread.h> // pthread_create()
#include <unistd.h>  // read(), write()
#include <fcntl.h>   // open(), close()
#include <errno.h>   // errno
#include <time.h>    // clock()

#define BUF_SIZE 2048 //buffer size

// data structure to hold copy
struct copy_struct {
	int thread_id; 
	char* src_filename;
	char* dst_filename; 
};
pthread_mutex_t m;

// copies a files from src_filename to dst_filename using functions fopen(), fread(), fwrite(), fclose()
int func_copy(char* src_filename, char* dst_filename) {
	FILE *src = fopen(src_filename, "r");	// opens a file for reading
	if (src == NULL) { // fopen() error checking
		fprintf(stderr, "unable to open %s for reading: %i\n", src_filename, errno);
		exit(0);
	}
	FILE *dst = fopen(dst_filename, "w");	// opens a file for writing; erases old file/creates a new file
	if (dst == NULL) { // fopen() error checking
		fprintf(stderr, "unable to open/create %s for writing: %i\n", dst_filename, errno);
		exit(0);
	}

	char store[2048];  // allocate a buffer to store read data
	int buf = malloc((size_t)BUF_SIZE);
	// reads content of file is loop iterations until end of file
	while(fread(store, 1, sizeof(buf), src)) {
		// writes bytes_read to dst_filename 
		fwrite(store, 1, sizeof(buf), dst);
	}
	
	// closes src file pointer
	fclose(src);

	// closes dst file pointer
	fclose(dst);
	return 0;
}

// thread function to copy one file
void* copy_thread(void* arg) {
	// lock critical region
	pthread_mutex_lock(&m);
	struct copy_struct params = *(struct copy_struct*)arg;  // cast/dereference void* to copy_struct

	// get file names from param struct
	char* src_filename = params.src_filename;
	char* dst_filename = params.dst_filename;

	printf("thread[%i] - copying %s to %s\n", params.thread_id, src_filename, dst_filename);
	
	// call copy func
	func_copy(src_filename, dst_filename);
	
	// unlock
	pthread_mutex_unlock(&m);
	pthread_exit(0);
}

int main(int argc, char *argv[]) {
	pthread_mutex_init(&m, NULL);
	 // check correct usage of arguments in command line
	 if(argc != 2) {
		 fprintf(stderr, "usage: %s <filecount>\n", argv[0]);
		exit(1);
	 }
	int num_threads;
	num_threads = atoi(argv[1]); // number of threads to create
	char* src_filename;
	char* dst_filename;
	char* src_filenames[num_threads]; // array of source files
	char* dst_filenames[num_threads]; // array of desintation files
	
	pthread_t threads[num_threads]; //initialize threads
	struct copy_struct thread_params[num_threads]; // structure for each thread
	int i = 0;

	// get src and dst file names using iterator
	for (i = 0; i < num_threads; i++) {
		char filename[20];
    	sprintf(filename, "%d.dat", i);

    	char filenameCopy[20];
    	sprintf(filenameCopy, "%dcopy.dat", i);

		thread_params[i].thread_id = i;
		thread_params[i].src_filename = strdup(filename);
		thread_params[i].dst_filename = strdup(filenameCopy);
	}

	// create threads for copying files
	for (i = 0; i < num_threads; i++) {
		pthread_create(&threads[i], NULL, copy_thread, thread_params + i);
	}

	// wait for all threads to finish
	for (i = 0; i < num_threads; i++) {
		pthread_join(threads[i], NULL);
	}

	pthread_mutex_destroy(&m); 
	return 0; 
}