#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"types.h"
#include "view.h"

OperationType check_operation_type(char *argv[])
{
    if(strcmp(argv[1],"-v")==0)
    {
	return e_view;
    }
    else if(strcmp(argv[1],"-e")==0)
    {
	return e_edit;
    }
    else if(strcmp(argv[1],"--h")==0)
    {
	return e_help;
    }
    else
	return e_unsupported;
}

Status read_and_validate_args(char *str,View *view)
{
    if(strstr(str,".mp3")!=NULL)
    {
	view->fname=str;
    }
    return e_success;
}

Status open_files(View *view)
{
    view->fptr_mp3=fopen(view->fname,"r");
    return e_success;
}

Status skip_header(View *view)
{
    fseek(view->fptr_mp3,10,SEEK_SET);
    return e_success;
}

Status get_title(View *view)
{
    if(get_it("TIT2",view->fptr_mp3)==e_success)
    {
	int size=decode_to_size(view->fptr_mp3);
	view->title=malloc(size);
	fread(view->title,size-1,1,view->fptr_mp3);
	return e_success;
    }
}

Status get_artist(View *view)
{
    if(get_it("TPE1",view->fptr_mp3)==e_success)
    {
        int size=decode_to_size(view->fptr_mp3);
        view->artist=malloc(size);
        fread(view->artist,size-1,1,view->fptr_mp3);
        return e_success;
    }
}
Status get_album(View *view)
{
    if(get_it("TALB",view->fptr_mp3)==e_success)
    {
        int size=decode_to_size(view->fptr_mp3);
        view->album=malloc(size);
        fread(view->album,size-1,1,view->fptr_mp3);
        return e_success;
    }
}
Status get_year(View *view){
    //printf("%d",get_it("TYER",view->fptr_mp3));
    if(get_it("TYER",view->fptr_mp3)==e_success)
    {
        int size=decode_to_size(view->fptr_mp3);
        view->year=malloc(size);
        fread(view->year,size-1,1,view->fptr_mp3);
        return e_success;
    }
}
Status get_comment(View *view)
{
    if(get_it("TCON",view->fptr_mp3)==e_success)
    {
        int size=decode_to_size(view->fptr_mp3);
        view->comment=malloc(size);
        fread(view->comment,size-1,1,view->fptr_mp3);
        return e_success;
    }
}

Status get_it(char *tag, FILE *fptr)
{
    char *str;
    str=malloc(5);
    fread(str,4,1,fptr);
    if((strcmp(tag,str))==0)
    {
	return e_success;
    }
}

int decode_to_size(FILE *fptr)
{
    int *ptr=malloc(sizeof(int*));
    fread(ptr,4,1,fptr);
    char temp;
        temp=*((char *)ptr);
        *((char *)ptr)=*((char *)ptr+3);
        *((char *)ptr+3)=temp;

        temp=*((char *)ptr+1);
        *((char *)ptr+1)=*((char *)ptr+2);
        *((char *)ptr+2)=temp;
	fseek(fptr,3,SEEK_CUR);
    return *ptr;
}
    
Status start_viewing(View *view)
{
    if((skip_header(view))==e_success)
    {
	if((get_title(view))==e_success)
	{
	    if(get_artist(view)==e_success)
	    {
		if(get_album(view)==e_success)
		{
		    if(get_year(view)==e_success)
		    {
			if(get_comment(view)==e_success)
			{
			    return e_success;
			}
		    }
		}
	    }
	}
    }
    //else
	//printf("Not done");
}

void print_viewing(View *view)
{
     printf("-----------------------------------------------------------------------------------\n");
     printf("MP3 Tag Reader and Editor for ID3v2\n");
     printf("-----------------------------------------------------------------------------------\n");
     printf("%-15s %-15s %-15s\n","Title",":",view->title);
     printf("%-15s %-15s %-15s\n","Artist",":",view->artist);
     printf("%-15s %-15s %-15s\n","Album",":",view->album);
     printf("%-15s %-15s %-15s\n","Year",":",view->year);
     printf("%-15s %-15s %-15s\n","Comment",":",view->comment);
     printf("-----------------------------------------------------------------------------------\n");
}
