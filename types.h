#ifndef TYPES_H
#define TYPES_H

/* User defined types */
typedef unsigned int uint;

/* Status will be used in fn. return type */
typedef enum
{
    e_success,
    e_failure
} Status;

typedef enum
{
    e_view,
    e_edit,
    e_help,
    e_unsupported
} OperationType;

typedef enum
{
    e_title,
    e_artist,
    e_album,
    e_year,
    e_comment
}Tag;

#endif
