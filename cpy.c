#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char * argv[])
{
	char destpath[100];

	int num = argc;

	FILE *fd, *dest;
	char buf[257];
	int len;

	if (argc < 3) {
		printf("Usage : %s <filename1> <filename2> \n", argv[0]);					// file copy
		printf("or\nUsage : %s <filename1> <filename2> ... <directory name> \n", argv[0]);		// file to folder copy
		return 0;
	}

	if (argc == 3){
		fd = fopen(argv[1], "r");
		dest = fopen(argv[2], "w");

		while (len = fread (buf, 1, 256, fd)){
			buf[len] = '\0';
			fwrite(buf, 1, len, dest);
			printf("Length : %d\n", len);
			printf("%s\n", buf);
		}
		
		fclose(dest);
		fclose(fd);
		return 0;
	}
	

	for(int i=1;i<=num-2;i++){
		strcpy(destpath, argv[num-1]);
		fd = fopen(argv[i], "r");
		strcat(destpath, argv[i]);

		dest = fopen(destpath, "w");

		while (len = fread(buf, 1, 256, fd))
		{
			buf[len] = '\0';
			fwrite(buf, 1, len, dest);
			printf("Copied Length : %d\n", len);
			printf("%s\n", buf);
		}
	}

	fclose(dest);
	fclose(fd);

	return 0;
}
