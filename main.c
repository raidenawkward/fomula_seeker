#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "fomula_seek.h"

#define CALCULATED_TARGET 24

static void show_help_info(const char* program_name) {
	char* pname = NULL;
	if (program_name) {
		pname = (char*)malloc(strlen(program_name) * sizeof(char));
		strcpy(pname,program_name);
	}
	else {
		pname = (char*)malloc(6 * sizeof(char));
		strcpy(pname,"seeker");
	}
	printf("this program is used for getting every integer fomula with target mathematical calculation result by using the given numbers\n");
	printf("usage : %s [-t target] num1 num2 num3 ...\n",pname);
}

static Boolean append_input_num(int num, int **input, int *count) {
	if (!input || !count)
		return false;
	if (!*input)
		return false;

	if (*count <= 0) {
		*count = 0;
		*input = (int*)malloc(sizeof(int));
		if (!input)
			return false;
	} else {
		int *new_ptr = (int*)realloc(*input,(*count + 1) * sizeof(int));
		if (new_ptr)
			*input = new_ptr;
		else
			return false;
	}

	(*input)[(*count)++] = num;

	return true;
}

typedef enum {
	ARG_NUM = 0,
	ARG_OPT_TARGET,
	ARG_UNKNOWN
} ArgType;

static Boolean is_num(const char* arg) {
	if (!arg)
		return false;
	int i;
	for (i = 0; i < strlen(arg); ++i) {
		if (!isdigit(arg[i])) {
			return false;
		}
	}
	return true;
}

static ArgType detect_arg_type(const char* arg) {
	if (!arg)
		return ARG_UNKNOWN;

	if (strcmp(arg,"-t") == 0 || strcmp(arg,"--target") == 0) {
		return ARG_OPT_TARGET;
	}

	if (is_num(arg))
		return ARG_NUM;

	return ARG_UNKNOWN;
}

int main(int argc, char** argv) {
	if (argc < 2) {
		printf("error : no input\n");
		show_help_info(argv[0]);
		exit(0);
	}

	int *input, input_count = 0;
	int target = CALCULATED_TARGET;

	int argi = 1;
	while(argi < argc) {
		switch (detect_arg_type(argv[argi])) {
		case ARG_NUM:
			if (!append_input_num(atoi(argv[argi++]),&input,&input_count)){
				printf("error : unknown mistake\n");
				exit(1);
			}
			break;
		case ARG_OPT_TARGET:
			++argi;
			if (argi <= argc) {
				if (is_num(argv[argi])) {
					target = atoi(argv[argi++]);
				} else {
					printf("error : invalid param '%s' for option %s\n",argv[argi]?argv[argi]:"null",argv[argi - 1]);
					show_help_info(argv[0]);
					exit(0);
				}
			}
			break;
		default:
		case ARG_UNKNOWN:
			printf("error : invalid input (%s)\n",argv[argi]);
			show_help_info(argv[0]);
			exit(0);
			break;
		}
	}

	int i;
	char** ret;
	int result_count = seek_fomula(target,input,input_count,&ret);

	if (result_count > 0) {
		printf("there are %d results for input ", result_count);
		int j;
		for (j = 0; j < input_count; ++j)
			printf("%d ",input[j]);
		printf(",\nthey are : \n");
		for (i = 0; i < result_count; ++i) {
			if (ret[i])
				printf("%s;\n",ret[i]);
		}
	} else if (result_count == 0) {
		printf("no result found for input ");
		int j;
		for (j = 0; j < input_count; ++j)
			printf(" %d",input[j]);
		printf("\n");

	} else {
		printf("error : error code %d\n",result_count);
	}

	return result_count;
}
