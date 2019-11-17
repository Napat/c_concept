#include <string.h>
#include <getopt.h>

#include "common.h"
#include "args_parser.h"

static bool is_numberstr(char *text)
{
    int j = strlen(text);
    while(j--)
    {
        if(text[j] >= '0' && text[j] <= '9')
            continue;
        return false;
    }
    return true;
}

// strsplit_util https://stackoverflow.com/a/34957656/3616311
static int strsplit_util(const char *txt, char delim, char ***tokens)
{
    int *tklen, *t, count = 1;
    char **arr, *p = (char *) txt;

    while (*p != '\0') if (*p++ == delim) count += 1;
    t = tklen = calloc (count, sizeof (int));
    for (p = (char *) txt; *p != '\0'; p++) *p == delim ? *t++ : (*t)++;
    *tokens = arr = malloc (count * sizeof (char *));
    t = tklen;
    p = *arr++ = calloc (*(t++) + 1, sizeof (char *));
    while (*txt != '\0')
    {
        if (*txt == delim)
        {
            p = *arr++ = calloc (*(t++) + 1, sizeof (char *));
            txt++;
        }
        else *p++ = *txt++;
    }
    free (tklen);
    return count;
}

void help(int argc, char **argv)
{
    printf(
        "Example %s\r\n"
        "\t %s --help\r\n"
        "\t %s -i 127.0.0.1 -p 21 -c napat:123456 -i 127.0.0.1 -f test.txt\r\n"
        , ""
        , argv[0]
        , argv[0]
    );
    exit(1);
}

int args_parse(input_args_t *pinput_args, int argc, char **argv)
{
    // See
    // - https://www.gnu.org/software/libc/manual/html_node/Getopt-Long-Options.html#Getopt-Long-Options 
    // - https://www.gnu.org/software/libc/manual/html_node/Getopt-Long-Option-Example.html#Getopt-Long-Option-Example
    char getopt_argv[] = "hc:f:i:p:";
    int c;

    while (1)
    {
        struct option long_options[] =
        {
            // These options auto set a flag(set value to variable).
            {"verbose",     no_argument,       &pinput_args->verbose_flag, 1},  // ./a.out --verbose
            {"brief",       no_argument,       &pinput_args->verbose_flag, 0},  // ./a.out --brief
            // These options don’t set a flag. We distinguish them by their indices.
            {"help",        no_argument,       0, 'h'},                         // ./a.out --help, ./a.out -h
            {"file",        required_argument, 0, 'f'},                         // ./a.out --file test.txt, ./a.out -f test.txt
            {"ip",          required_argument, 0, 'i'},                         // ./a.out --ip 127.0.0.1, ./a.out -i 127.0.0.1
            {"port",        required_argument, 0, 'p'},                         // ./a.out --port 21, ./a.out -i test.txt
            {"credential",  required_argument, 0, 'c'},                         // ./a.out --credential foo:bar, ./a.out -c foo:bar
            {0, 0, 0, 0}
        };
        // getopt_long stores the option index here.
        int option_index = 0;

        c = getopt_long(argc, argv, getopt_argv, long_options, &option_index);

        // Detect the end of the options.
        if (c == -1)
            break;

        switch (c)
        {
            case 0:
                // If this option set a flag, do nothing else now.
                if (long_options[option_index].flag != 0)
                    break;
                fprintf(debug_info(), "option %s", long_options[option_index].name);
                if (optarg)
                    printf (" with arg %s", optarg);
                printf ("\n");
                break;

            case 'h':
                help(argc, argv);
                break;

            case 'c':
                fprintf(debug_info(), "option -c with value %s'\n", optarg);      
                
                {
                    char **tokens;
                    int count, i;

                    // optarg --> "user:pass"
                    count = strsplit_util(optarg, ':', &tokens);
                    // for (i = 0; i < count; i++) printf ("%s\n", tokens[i]);

                    switch(count)
                    {
                        case 2:
                            snprintf(pinput_args->pass, sizeof(pinput_args->pass), "%s", tokens[1]);
                        case 1:
                            snprintf(pinput_args->user, sizeof(pinput_args->user), "%s", tokens[0]);
                            break;
                        default:
                            fprintf(debug_error(), "Bad creadential input(%d): %s\n", count, optarg);
                            
                            // freeing tokens
                            for (i = 0; i < count; i++) free (tokens[i]);
                            free (tokens);

                            help(argc, argv);
                    }
                    
                    // freeing tokens
                    for (i = 0; i < count; i++) free (tokens[i]);
                    free (tokens);
                }
                break;

            case 'f':
                fprintf(debug_info(), "option -f with value %s\n", optarg);
                snprintf(pinput_args->filepath, sizeof(pinput_args->filepath), "%s", optarg);
                break;
            
            case 'i':
                fprintf(debug_info(), "option -i with value %s\n", optarg);
                snprintf(pinput_args->ip_address, sizeof(pinput_args->ip_address), "%s", optarg);
                break;

            case 'p':
                fprintf(debug_info(), "option -p with value %s\n", optarg);
                if(is_numberstr(optarg))
                {                
                    pinput_args->port = (int)strtol(optarg, (char **)NULL, 10);
                }
                else
                {
                    help(argc, argv);
                }
                break;

            case '?':
                // getopt_long already printed an error message.
                help(argc, argv);
                break;

            default:
                help(argc, argv);
        }
    }

    // Instead of reporting ‘--verbose’
    //     and ‘--brief’ as they are encountered,
    //     we report the final status resulting from them.
    if (pinput_args->verbose_flag)
        puts ("verbose flag is set");

    // Print any remaining command line arguments (not options).
    if (optind < argc)
    {
        printf ("non-option ARGV-elements: ");
        while (optind < argc)
            printf ("%s ", argv[optind++]);
        putchar ('\n');

        help(argc, argv);
    }
    return 0;
}
