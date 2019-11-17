#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h> // memset

#include "common.h"
#include "args_parser.h"

int main(int argc, char **argv) 
{
    input_args_t input_args;
    memset(&input_args, 0, sizeof(input_args));

    args_parse(&input_args, argc, argv);

    // test
    if(input_args.filepath[0] != '\0') {fprintf(debug_info(), "filepath: %s\n", input_args.filepath);}
    if(input_args.ip_address[0] != '\0') {fprintf(debug_info(), "ip_address: %s\n", input_args.ip_address);}
    if(input_args.user[0] != '\0') {fprintf(debug_info(), "user: %s\n", input_args.user);}
    if(input_args.pass[0] != '\0') {fprintf(debug_info(), "pass: %s\n", input_args.pass);}
    fprintf(debug_info(), "PORT: %d\n", input_args.port);

    return 0;
}
