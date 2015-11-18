

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int boolean;

int nextLine(char c,FILE* fd,unsigned int file_size,int in_function)
{
  if (in_function)
      printf("%c",c);

  while(c!='\n' && (unsigned)ftell(fd)<file_size)
  {
    fread(&c,1,sizeof(char),fd);
    if (in_function)
      printf("%c",c);
  }

  fseek(fd,-1,SEEK_CUR);
  return ftell(fd);
}

int processFile(char* pattern, char* filename, boolean file_is_alone)
{
  FILE* fd;
  unsigned int file_size;
  int pattern_length;
  char c = ' ';
  char c2 = ' ';
  unsigned int file_pos = 0;
  int nb_brackets = 0;
  boolean in_function = 0;
  boolean in_comment = 0;
  boolean in_quotation_marks = 0;
  boolean in_quotation_marks2 = 0;
  boolean already_found = 0;
  boolean do_not_display_return = 0;

  pattern_length = strlen(pattern);

  fd = fopen(filename,"r");

  if (fd == NULL)
  {
    printf("-------could not open file %s for reading.\n",filename);
    return -1;
  }

  fseek(fd,0,SEEK_END);
  file_size=ftell(fd);

  while(file_pos<file_size)
  {
    int i;

    fseek(fd,file_pos,SEEK_SET);
    fread(&c,1,sizeof(char),fd);
    fread(&c2,1,sizeof(char),fd);

    if (in_function)
    {
#ifdef WIN32
    	if (do_not_display_return && c=='\n')
    		do_not_display_return = 0;
    	else
#endif
    		printf("%c",c);
#ifdef WIN32
    	if (c2=='\n') do_not_display_return = 1;
#endif
    }

    if (c=='/' && c2=='*' && !in_quotation_marks && !in_quotation_marks2)
	   in_comment = 1;
    else if (c=='*' && c2=='/')
		  in_comment = 0;
    else if (c=='/' && c2=='/' && !in_quotation_marks && !in_quotation_marks2)
		  file_pos = nextLine(c2,fd,file_size,in_function);
    else if (c=='"' && !in_comment && !in_quotation_marks2)
      in_quotation_marks = !in_quotation_marks;
    else if (c=='\'' && !in_comment && !in_quotation_marks)
		  in_quotation_marks2 = !in_quotation_marks2;
    else if (c=='#' && !in_comment && !in_quotation_marks && !in_quotation_marks2)
		  file_pos = nextLine(c2,fd,file_size,in_function);

    if (!in_comment && !in_quotation_marks && !in_quotation_marks2)
    {
      if (nb_brackets == 0 && !in_function)
	    {
	      fseek(fd,file_pos,SEEK_SET);
	      for (i=0;i<pattern_length;i++)
        {
          if (fread(&c2,1,sizeof(char),fd)==-1)
		        break;
          if (c2!=pattern[i])
            break;
        }
        if (i==pattern_length) // pattern found
        {
  		    int i=0;
  		    char tmp;
  		    file_pos--;
          if (!already_found && !file_is_alone)
  		    {
  		      printf("-------file %s :\n",filename);
  		      already_found=1;
  		    }

  		    fseek(fd,1,SEEK_CUR);
    		  while(tmp!='\n') // back to the beginning of the line
    	    {
            if ((unsigned)ftell(fd)<=1) {fseek(fd,-1,SEEK_CUR);break;}
    	      fseek(fd,-2,SEEK_CUR);
    	      fread(&tmp,1,sizeof(char),fd);
            i++;
    	    }

          while((unsigned)ftell(fd)<file_pos+1) //show the beginning of the line
  		    {
  		      fread(&tmp,1,sizeof(char),fd);
  		      printf("%c",tmp);
  		    }
  		    in_function=1;
  		  }
      }

  	  if (c==';' && nb_brackets==0 && in_function) // find a ';' closing the function
      {
        printf("\n");
        in_function=0;
      }

      if (c=='{')
      {
  	    nb_brackets++;
      }
      else if (c=='}')
      {
        nb_brackets--;
  	    if (nb_brackets==0 && in_function)
  		  {
  		    printf("\n");
  		    in_function=0;
  		  }
  	    if (nb_brackets<0)
  		  {
  		    printf("-------file %s : Error : too much characters '}' compared to '{'\n",filename);
  		    return -1;
        }
  	  }
  	}

    file_pos++;
  }
  return 0;
}

void usage(char *nom)
{
  printf("Usage : %s <function> <files>\n",nom);
  exit(EXIT_FAILURE);
};

int main(int argc, char *argv[])
{
  int i;

  if (argc<3)
    usage(argv[0]);

  if (strcmp(argv[1],"")==0)
  {
    printf("Error: the pattern to find is empty.\n");
    return EXIT_FAILURE;
  }

  for (i=2;i<argc;i++)
  {
    processFile(argv[1], argv[i], argc-2 == 1);
  }

  return EXIT_SUCCESS;
}
