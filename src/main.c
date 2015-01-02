#include "filter/filter_substring.h"
#include "filter/filter_glob.h"
#include "tpb/torrent_print.h"
#include "tpb/parser.h"

#include <stdio.h>
#include <string.h>
#include <getopt.h>

enum output_type {
    YAML, XML
};

enum output_type get_output_type(const char *str)
{
    if (strcmp(str, "yaml") == 0) {
        return YAML;
    } else if (strcmp(str, "xml") == 0) {
        return XML;
    } else {
        fputs("Invalid output type provided. Using defaul: yaml.", stderr);
        return YAML;
    }
}

enum filter_type {
    SUBSTRING, GLOB
};

enum filter_type get_filter_type(const char *str)
{
    if (strcmp(str, "substring") == 0) {
        return SUBSTRING;
    } else if (strcmp(str, "glob") == 0) {
        return GLOB;
    } else {
        fputs("Invalid filter type provided. Using defaul: substring.", stderr);
        return SUBSTRING;
    }
}

struct program_options_t {
    FILE *input;
    const char *filter_expression;
    enum output_type output_type;
    enum filter_type filter_type;
};

static void print_usage(const char *program_name) {
    fprintf(stderr, "Usage: %s [options] pattern [xml-file]\n", program_name);
    fputs("\n", stderr);
    fputs("Command-line utility for searching thepiratebay.org XML archives.\n", stderr);
    fputs("\n", stderr);
    fputs("Options:\n", stderr);
    fputs("  -h, --help     show this help message and exit\n", stderr);
    fputs("  -o OUTPUT_TYPE, --output-type=OUTPUT_TYPE\n", stderr);
    fputs("                 Output type for search. Can be either 'xml' or 'yaml', and\n", stderr);
    fputs("                 this makes the application print either XML in the tpb archive\n", stderr);
    fputs("                 format or human-readable YAML. Defaults to YAML output.\n", stderr);
    fputs("  -f FILTER_TYPE, --filter-type=FILTER_TYPE\n", stderr);
    fputs("                 Type of filter expression. Supported filter operation types\n", stderr);
    fputs("                 are 'substring' and 'glob'. First checks whether torrent title\n", stderr);
    fputs("                 contains passed sutring, second evaluates glob expresion, e.g.\n", stderr);
    fputs("                 '*gogol?bordello*'. Defaults to substring matching.\n", stderr);
}

static bool process_optional_arguments(struct program_options_t *opts,
                                       int argc, char **argv)
{
    static struct option long_options[] = {
        {"help",        no_argument,       0, 'h'},
        {"output-type", required_argument, 0, 'o'},
        {"filter-type", required_argument, 0, 'f'},
        {0, 0, 0, 0}
    };

    // optional arguments
    while (true) {
        int choice, option_index = 0;

        choice = getopt_long(argc, argv, "ho:f:", long_options, &option_index);

        if (choice == -1) break;

        switch (choice) {
            case 'h':
                // print help and exit
                print_usage(argv[0]);
                exit(EXIT_SUCCESS);

            case 'o':
                opts->output_type = get_output_type(optarg);
                break;

            case 'f':
                opts->filter_type = get_filter_type(optarg);
                break;

            case '?':
                break;

            default:
                // should never happen
                return false;
        }
    }

    return true;
}

static bool process_positional_arguments(struct program_options_t *opts,
                                       int argc, char **argv)
{
    // positional arguments
    int remaining_argc = argc - optind;
    if (remaining_argc == 0) {
        fputs("You must specify filter expression.", stderr);
        return false;
    }

    if (remaining_argc >= 1) {
        opts->filter_expression = argv[optind + 0];
    }

    if (remaining_argc == 2) {
        opts->input = fopen(argv[optind + 1], "r");
    } else {
        opts->input = stdin;
    }

    return true;
}

static bool initialize_program_options(struct program_options_t *opts,
                                       int argc, char **argv)
{
    return process_optional_arguments(opts, argc, argv) &&
        process_positional_arguments(opts, argc, argv);
}

static struct filter_t *create_filter(struct program_options_t *opts)
{
    switch (opts->filter_type) {
    case SUBSTRING:
        return filter_substring_create(opts->filter_expression);

    case GLOB:
        return filter_glob_create(opts->filter_expression);

    default:
        // should never happen
        return NULL;
    }
}

static void print_torrents(enum output_type output_type,
                           struct list_t *torrents)
{
    switch (output_type) {
    case XML:
        tpb_xml_print_torrents(stdout, torrents);
        break;

    default: //YAML
        tpb_yaml_print_torrents(stdout, torrents);
    }
}

static void run_search(struct program_options_t *opts)
{
    struct filter_t *filter = create_filter(opts);

    struct list_t *torrents = tpb_parse_and_filter_file(opts->input, filter);
    fclose(opts->input);

    print_torrents(opts->output_type, torrents);

    list_free_with_data(torrents, tpb_torrent_free);
    filter_free(filter);

    xmlCleanupParser();
    xmlMemoryDump();
}

int main(int argc, char **argv)
{
    struct program_options_t opts;
    memset(&opts, 0, sizeof(struct program_options_t));

    if (!initialize_program_options(&opts, argc, argv)) {
        return EXIT_FAILURE;
    }

    if (!opts.input) {
        fputs("Error while reading the input file.", stderr);
        return EXIT_FAILURE;
    }

    run_search(&opts);

    return EXIT_SUCCESS;
}
