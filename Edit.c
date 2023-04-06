
#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include "Edit.h"
#include "types.h"

Status read_and_validate_edit_args(char *argv[],MP3Edit *edit)		//read and validation function
{
    int count=0;

    if(argv[2]!=NULL && argv[3]!=NULL)
    {
	if(strcmp(argv[2],"-t")==0)
	{
	    edit->TAG="TIT2";
	    edit->Data_size=strlen(argv[3]);
	    strcpy(edit->Data,argv[3]);
	    edit->Tag_rep="Tittle";
	    count++;
	}
	else if(strcmp(argv[2],"-a")==0)
	{
	    edit->TAG="TPE1";
	    edit->Data_size=strlen(argv[3]);
	    strcpy(edit->Data,argv[3]);
	    edit->Tag_rep="Artist";
	    count++;
	}
	else if(strcmp(argv[2],"-A")==0)
	{
	    edit->TAG="TALB";
	    edit->Data_size=strlen(argv[3]);
	    strcpy(edit->Data,argv[3]);
	    edit->Tag_rep="Album";
	    count++;
	}
	else if(strcmp(argv[2],"-y")==0)
	{
	    edit->TAG="TYER";
	    edit->Data_size=strlen(argv[3]);
	    strcpy(edit->Data,argv[3]);
	    edit->Tag_rep="Year";
	    count++;
	}
	else if(strcmp(argv[2],"-c")==0)
	{
	    edit->TAG="TCON";
	    edit->Data_size=strlen(argv[3]);
	    strcpy(edit->Data,argv[3]);
	    edit->Tag_rep="Comment";
	    count++;
	}
	else
	{
	    printf("------------------SELECT EDIT DETAILS-----------------\n");
	    printf("Please pass tag arguments which you want to edit\n");
	    printf("Example: ./a.out -e -t/-a/-A/-y/-c <MP3 File Name>\n");
	    return e_failure;
	}

	if(strstr(argv[4],".mp3")!=NULL)						//check if 3rd CLA is with .bmp extension 
	{
	    edit->mp3_file_original_name=argv[4];
	    edit->mp3_file_editted_name="edited_song.mp3";
	    count++;
	}

    }
    if(count==2)
    {
	return e_success;
    }
    return e_failure;
}

Status open_files_edit(MP3Edit *edit)
{
    										 // Src Image file open in read mode
    edit->fptr_original_mp3 = fopen(edit->mp3_file_original_name, "r");
    										// Do Error handling
    if (edit->fptr_original_mp3 == NULL)
    {
    	perror("fopen");
    	fprintf(stderr, "ERROR: Unable to open original file %s\n", edit->mp3_file_original_name);

    	return e_failure;
    }
    edit->fptr_editted_mp3 = fopen(edit->mp3_file_editted_name, "w");
    										// Do Error handling
    if (edit->fptr_editted_mp3 == NULL)
    {
    	perror("fopen");
    	fprintf(stderr, "ERROR: Unable to open editting file %s\n", edit->mp3_file_original_name);

    	return e_failure;
    }
    return e_success;

}

Status copy_mp3_header(MP3Edit *edit)
{
    char header[10];
    fread(header,10,1,edit->fptr_original_mp3);
    fwrite(header,10,1,edit->fptr_editted_mp3);
    return e_success;
}

Status copy_flag(MP3Edit *edit)
{
    char flag[3];
    fread(flag,3,1,edit->fptr_original_mp3);
    fwrite(flag,3,1,edit->fptr_editted_mp3);
    return e_success;
}
Status search_tag(MP3Edit *edit)
{
    char search;

    int temp=1,i,count=0;
    while(temp)
    {
	count=0;
	for(i=0;i<4;i++)
	{
	    fread(&search,1,1,edit->fptr_original_mp3);
	    fwrite(&search,1,1,edit->fptr_editted_mp3);
	    if(edit->TAG[i]==search)
	    {
		count++;
		continue;
	    }
	    break;
	}
	if(count==4)
	{
	    return e_success;
	}
    
    }

}

void swap_for_size(void *buffer)
{
    char temp;
    temp=((char*)buffer)[3];
    ((char*)buffer)[3]=((char*)buffer)[0];
    ((char*)buffer)[0]=temp;
}

Status original_size(MP3Edit *edit)
{
    char buffer[4];
    fread(buffer,4,1,edit->fptr_original_mp3);						//read from mp3 file
    swap_for_size(buffer);
    edit->original_size=buffer[0];
    return e_success;
}

Status edit_size(MP3Edit *edit)
{
    int size=edit->Data_size+1;
    swap_for_size(&size);
    fwrite(&size,4,1,edit->fptr_editted_mp3);
    return e_success;
}

Status copy_data(MP3Edit *edit)
{
    int size=edit->Data_size;
    fwrite(edit->Data,size,1,edit->fptr_editted_mp3);
    return e_success;
}

Status skip_bytes_from_original(MP3Edit *edit)
{
    fseek(edit->fptr_original_mp3,(edit->original_size-1),SEEK_CUR);
}

Status edit_rest_data(FILE *fptr_src, FILE *fptr_dest)
{
    char buffer;
    while( fread(&buffer,1,1,fptr_src) > 0 )					//read data till reaches FEOF
	fwrite(&buffer,1,1,fptr_dest);    //write to output image
    fclose(fptr_dest);
    fclose(fptr_src);
    return e_success;
}

Status view_editted_data(MP3Edit *edit)
{
    int i=35;
	while(i)
	{
	    printf("-");
	    i--;
	}
	printf("Select Edit Option");
	i=40;
	while(i)
	{
	    printf("-");
	    i--;
	}
	putchar('\n');

	i=30;
	while(i)
	{
	    printf("-");
	    i--;
	}
	printf("Select %s Changed Option",edit->Tag_rep);
	i=30;
	while(i)
	{
	    printf("-");
	    i--;
	}
	putchar('\n');
	putchar('\t');
	printf("%s  %-2s%s",edit->Tag_rep,":",edit->Data);

	putchar('\n');
	i=30;
	while(i)
	{
	    printf("-");
	    i--;
	}
	printf("%s Changed Successfully",edit->Tag_rep);
	i=30;
	while(i)
	{
	    printf("-");
	    i--;
	}
	putchar('\n');
	return e_success;
}

Status do_edit(MP3Edit *edit)
{
    if(open_files_edit(edit)==e_success)
    {
	if(copy_mp3_header(edit)==e_success)
	{
	    if(search_tag(edit)==e_success)
	    {
		if(original_size(edit)==e_success)
		{
		    if(edit_size(edit)==e_success)
		    {
			if(copy_flag(edit)==e_success)
			{
			    if(copy_data(edit)==e_success)
			    {
				if(skip_bytes_from_original(edit)==e_success)
				{
				    if(edit_rest_data(edit->fptr_original_mp3,edit->fptr_editted_mp3)==e_success)
				    {
					char buf[50];
					sprintf(buf,"mv %s %s",edit->mp3_file_editted_name,edit->mp3_file_original_name);
					system(buf);
					//sprintf(buf,"rm %s",edit->mp3_file_editted_name);
					//system(buf);

					if(view_editted_data(edit)==e_success)
					{
					    return e_success;
					}
				    }
				}
			    }
			}
		    }
		}
	    }
	}
	else
	{
	    printf("::::COPY HEADER ERROR:::::\n");
	}
    }

}
