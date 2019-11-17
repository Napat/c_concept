#ifndef __ARGS_PARSER_H__
#define __ARGS_PARSER_H__

#include "common.h"

void help(int argc, char **argv);
int args_parse(input_args_t *pinput_args, int argc, char **argv);

#endif /* __ARGS_PARSER_H__ */
