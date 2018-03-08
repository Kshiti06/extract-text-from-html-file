#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//defining the basic node structure
typedef struct node
{
   char data[500];
   struct node *link;
} *NODE;

//function to obtain a new node
NODE getnode()
{
   NODE x;
   x=(NODE)malloc(sizeof(struct node));
   x->link=NULL;

   return x;
}

//function to inset a record at the rear
NODE insert_rear(NODE first,char line[])
{
   NODE temp;
   temp=getnode();
   strcpy(temp->data,line);
   NODE cur;
   cur=first;

   if(first==NULL)
      first=temp;
   else
   {
      while(cur->link!=NULL)
      {
         cur=cur->link;
      }
      cur->link=temp;
      temp->link=NULL;
   }
   return first;
}

//function to output data from the linked list into the final output file
 void opfile(NODE first)
 {
   FILE *ptr;
   ptr=fopen("file1.html","w");
   NODE temp;
   temp=first;
   int i;
   while(temp!=NULL)
   {
      int flag=0;
     for(i=0;temp->data[i]!='\0';i++)
     {
        if(temp->data[i]=='<')
        { flag=1; continue;}
      if(temp->data[i]=='>')
         {flag=0;continue;}

      if(!flag)
      {
         fputc(temp->data[i],ptr);

      }
     }
     temp=temp->link;
   }
   fclose(ptr);
 }

//function to print the data between the required tags from the file with all the textual content
 void TagText(NODE first, char tag[], char tage[]) {
   FILE * fp;

   char filename[] = "file1.html", line[200];

   fp = fopen(filename, "r");
   NODE temp;
   temp = first;
   int l = 0, k = 0;
   int flag = 0;
   int check = 0;

   if (!fp)

   {
    perror("could not find the file");

    exit(0);
   }

   while (temp != NULL) {

    if (strstr(temp -> data, tag)) {
     check = 1;

     while (fgets(line, sizeof line, fp) != NULL) {
      l++;
      if (k >= l)
       continue;

      if (strstr(temp -> data, tage) && strstr(temp -> data, tag)) {
       char * result1 = strstr(temp -> data, tag);
       int p1 = result1 - temp -> data;
       int len = strlen(tag);

       p1 = p1 + len;
       char * result2 = strstr(temp -> data, tage);
       int p2 = result2 - temp -> data;
       int i;
       for (i = p1; i < p2; i++) {

        if (temp -> data[i] == '<') {
         flag = 1;
         continue;
        }
        if (temp -> data[i] == '>') {
         flag = 0;
         continue;
        }

        if (!flag) {

         printf("%c", temp -> data[i]);
        }

       }
       break;
      } else {
       fputs(line, stdout);
       if (strstr(temp -> data, tage))
        break;
       temp = temp -> link;
      }
     }
    }
    k++;
    temp = temp -> link;
   }
fclose ( fp );

if(check==0)
  printf("Tag not found");

printf("\n");
}

int main ()
{
   NODE first=NULL;
   static const char filename[] = "file.html";
   FILE *file = fopen ( filename, "r" );
   if ( file != NULL )
   {
      char line [ 100 ];
      while ( fgets ( line, sizeof line, file ) != NULL )
      {
         first=insert_rear(first,line);
      }
   }
   else
   {
      perror ( filename );
   }
   fclose(file);
   opfile(first);
   printf("\nThe given html file is as follows\n\n");
   FILE *fptr = fopen("file.html","r");
  char line[100];
  while(!feof(fptr))
  {
    fgets(line,100,fptr);
    printf("%s\n",line);
  }
  printf("\nPrinting all textual contents of html file which have been stored in another file:\n");
   FILE *ptr1;
   ptr1=fopen("file1.html","r+");
      int i;
   if((i=fgetc(ptr1))==EOF)
    {
      printf("File empty\n");
    }
    else
    {
      while(i!=EOF)
      {
        printf("%c",i);
        i=fgetc(ptr1);
      }
    }
fclose(ptr1);
printf("_____________________________________________\n");
int ch;
printf("1:To list contents of a specified tag\n2:Exit\n");
  do
  {
    printf("Enter your choice\n");
    scanf("%d",&ch);
      switch(ch)
    {
      case 1:printf("Enter start tag and end tag\nFor eg:<a> and </a>\n");
      char tag[20],tage[20];
      scanf("%s",tag);
      scanf("%s",tage);
      TagText(first,tag,tage);
      break;
      case 2:break;
      default:printf("Invalid choice\n");
    }
  }
    while(ch!=2);
    return 0;
}
