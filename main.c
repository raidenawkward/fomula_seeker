#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "24.h"

static void show_help_info(const char* program_name) {
	char* pname = NULL;
	if (program_name) {
		pname = (char*)malloc(strlen(program_name) * sizeof(char));
		strcpy(pname,program_name);
	}
	else {
		pname = (char*)malloc(2 * sizeof(char));
		strcpy(pname,"24");
	}
	printf("usage : %s num1 num2 num3 ...\n",pname);
}

int main(int argc, char** argv) {
	if (argc < 2) {
		printf("error : no input\n");
		show_help_info(argv[0]);
		exit(0);
	}

	int* input = (int*)malloc((argc - 1) * sizeof(int));
	if (!input) {
		printf("memory error\n");
		exit(1);
	}

	int i;
	for (i = 1; i < argc; ++i) {
		input[i - 1] = atoi(argv[i]);
	}
	char** ret;
	int result_count = seek_24_fomula(input,argc - 1,&ret);

	if (result_count > 0) {
		printf("there are %d results for input ");
		int j;
		for (j = 0; j < argc - 1; ++j)
			printf("%d ",input[j]);
		printf(",\nthey are : \n");
		for (i = 0; i < result_count; ++i) {
			if (ret[i])
				printf("%s;\n",ret[i]);
		}
	} else if (result_count == 0) {
		printf("no result found for input ");
		int j;
		for (j = 0; j < argc - 1; ++j)
			printf(" %d",input[j]);
		printf("\n");

	} else {
		printf("some error happened while program running, error code %d\n",result_count);
	}

	return result_count;
}
