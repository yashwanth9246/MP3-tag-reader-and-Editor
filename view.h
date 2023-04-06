#ifndef VIEW_H
#define VIEW_H

#include "types.h"

typedef struct _View
{
    /* Information to be extracted */
    char *title;
    char *artist;
    char *album;
    char *year;
    char *comment;
    FILE *fptr_mp3;
    char *fname;
}View;

OperationType check_operation_type(char *argv[]);

Status read_and_validate_args(char *str,View *view);

Status open_files(View *view);

Status skip_header(View *view);

Status get_title(View *view);

Status get_artist(View *view);

Status get_album(View *view);

Status get_year(View *view);

Status get_comment(View *view);

Status get_it(char *tag, FILE *fptr);

int decode_to_size(FILE *fptr);

Status start_viewing(View *view);

void print_viewing(View *view);
#endif
