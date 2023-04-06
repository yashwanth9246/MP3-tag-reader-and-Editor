/*
Name: Yashwanth Pola
Date:23/03/2023
 */
#include<stdio.h>
#include "view.h"
#include "Edit.h"
#include "types.h"
int main(int argc, char *argv[])
{
    if(argc<=5)
    {
	if(argc>=2)
	{
	    if(check_operation_type(argv)==e_view)
	    {
		View view;
	       	if(read_and_validate_args(argv[2],&view)==e_success)
	       	{
		    if(open_files(&view)==e_success)
		    {
			if(start_viewing(&view)==e_success)
			{
			  print_viewing(&view);
			}
		    }
		}
	    }
	    else if(check_operation_type(argv)==e_edit)
	    {
		MP3Edit edit;
		if(read_and_validate_edit_args(argv,&edit)==e_success)
		{
		    if(open_files_edit(&edit)==e_success)
		    {
			if(do_edit(&edit)==e_success)
			{
			    return 0;
			}
		    }
		}
	    }
	    else if(check_operation_type(argv)==e_help)
	    {
		printf("%s\n","Usage: ./a.out -[taAyc] \"value\" filename");
		printf("%7s%10s\n"," ","./a.out -v");
		printf("%s%6s%10s\n","-t"," ","Modifies a Title tag");
		printf("%s%6s%10s\n","-a"," ","Modifies a Artist tag");
		printf("%s%6s%10s\n","-A"," ","Modifies a Album tag");
		printf("%s%6s%10s\n","-y"," ","Modifies a Year tag");
		printf("%s%6s%10s\n","-c"," ","Modifies a Comment tag");

	    }
	    else if(check_operation_type(argv)==e_unsupported)
	    {
		printf("unsupported usage\n");
	    }
	}
    }
    if(argc ==1)
    {
	printf("----------------------------------------------------------------------------------\n");
	printf("ERROR: ./a.out : INVALID ARGUMENTS\n");
	printf("USAGE :\n");
	printf("To view please pass like:  ./a.out -v <MP3 file name>\n");
	printf("To edit please pass like: ./a.out -e -t/-a/-A/-y/-c <edited name> <MP3 File name>\n");
	printf("----------------------------------------------------------------------------------\n");
    }
    return 0;
}

