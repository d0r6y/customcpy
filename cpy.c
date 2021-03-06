#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char * argv[])
{
	char destpath[100];

	int num = argc;												// num = number of inputs

	FILE *fd, *dest;
	char buf[257];
	int len;

	if (argc < 3) {	
		printf("Usage : %s <filename1> <filename2> \n", argv[0]);					// Case1 : file copy
		printf("OR\nUsage : %s <filename1> <filename2> ... <directory name> \n", argv[0]);		// Case2 : files to folder copy
		printf("Ex1) ./customcpy srcfile destfile\n");
		printf("Ex2) ./customcpy targetfile1 targetfile2 targetfile3 /home/d0r6y/dest/\n");		// Example
		return 0;
	}

	if (argc == 3){												// Case1
		fd = fopen(argv[1], "r");
		dest = fopen(argv[2], "w");

		while (len = fread (buf, 1, 256, fd)){
			buf[len] = '\0';									// add NULL at the end
			fwrite(buf, 1, len, dest);
			printf("Copied Length : %d\n", len);
			printf("Copied Content : %s\n", buf);
		}
		
		fclose(dest);
		fclose(fd);
		return 0;
	}
	
	for(int i=1;i<=num-2;i++){										// Case2
		strcpy(destpath, argv[num-1]);									// destpath = destination folder path
		
		int destlen = strlen(destpath);
		if(destpath[destlen-1] != '/'){									// if destpath is not terminated with /, add /
			strcat(destpath,"/");
		}
			
		fd = fopen(argv[i], "r");									// open input files
		
		strcat(destpath, argv[i]);									// new files path = destination folder path + original file name
		dest = fopen(destpath, "w");

		while (len = fread(buf, 1, 256, fd))								// Same as Case1
		{
			buf[len] = '\0';
			fwrite(buf, 1, len, dest);
			printf("File No.%d\n",i);
			printf("Copied Length : %d\n", len);
			printf("Copied Content : %s\n", buf);
		}
	}

	fclose(dest);
	fclose(fd);

	return 0;
}
