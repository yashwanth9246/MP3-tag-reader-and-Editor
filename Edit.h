#ifndef EDIT_H
#define EDIT_H

#include "types.h" // Contains user defined types

/* 
 * Structure to store information required for
 */

#define MAX_SECRET_BUF_SIZE 1
#define MAX_IMAGE_BUF_SIZE (MAX_SECRET_BUF_SIZE * 8)
#define MAX_FILE_SUFFIX 4

typedef struct _MP3Edit
{
    
    int Data_size;
    char Data[50];
    char *TAG;
    int original_size;
    char *Tag_rep;
    
    FILE *fptr_original_mp3;
    char *mp3_file_original_name;
        
    FILE *fptr_editted_mp3;
    char *mp3_file_editted_name;
    

} MP3Edit;


/* Perform EDIT operation */
Status do_edit(MP3Edit *edit);

/* Check operation type
OperationType check_operation_type(char *argv[]);*/

/* Insert and validate edit args from argv */
Status read_and_validate_edit_args(char *argv[], MP3Edit *edit);

/* Get File pointers for i/p and o/p files */
Status open_files_edit(MP3Edit *edit);

/*Copy header*/
Status copy_mp3_header(MP3Edit *edit);

/*SWAP*/
void swap_for_size(void *buffer);

/*Size of original data*/
Status original_size(MP3Edit *edit);

/*Skip unnecesary bytes*/
Status skip_bytes_from_original(MP3Edit *edit);

/*Copy FLAG*/
Status copy_flag(MP3Edit *edit);

/*Search tag data*/
Status search_tag(MP3Edit *edit);

/*Edit size*/
Status edit_size(MP3Edit *edit);

/*Copy Data*/
Status copy_data(MP3Edit *edit);

/*Insert rest of the data*/
Status edit_rest_data(FILE *fptr_src, FILE *fptr_dest);

/*read data*/
Status view_editted_data(MP3Edit *edit);

#endif
