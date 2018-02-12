/*
	Write a program which accept file name which contains data of all file. We have to create all file again.
*/

#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>
#include<string.h>
#include<fcntl.h>
#include<stdlib.h>
#include<errno.h>
int main(int argc, char *argv[]) 
{
	DIR *dir;
	struct dirent *entry;
	struct stat filestat;
	char name[100] = {'\0'};
	char *ptr = NULL;
	int fd,fdnew,retread,ret;
	// Structure which maintain information of file
	typedef struct
	{
		char name[50];
		int size;
	}FILEINFO;

	FILEINFO obj;

	if(argc!= 2)
	{
		printf("Error: Not sufficient arguments\n");
		return -1;
	}

	fd = open(argv[1],O_RDONLY);
	if(fd == -1)
	{
		printf("Unable to open file\n");
		return -1;
	}

	// Read the contents of that file which contains all files data
	while ((ret = read(fd,&obj,sizeof(obj)))!=0)
	{
		// Create new file with its name
		fdnew = creat(obj.name,0666);
		
		// Allocate memory to read the data of that file
		ptr = (char*)malloc(obj.size*sizeof(char));
		read(fd,ptr,obj.size);			
		
		// Write the contents in newly created file
		write(fdnew,ptr,obj.size);
		close(fdnew);

		// Free the allocated memory
		free(ptr);
	}

	close(fd);
	return 0;
}
