//Authors: Yunus Güngör, Cem Karagöz
//ITU System programing class BLG413E-2017
//mails:yunusgnr@gmail.com, cem.duhan@gmail.com

//Compile with: gcc -Wall -o pcm postalCodeMapper.c `pkg-config fuse --cflags --libs`
//Run with: pcm /mountpath /csv_file_path

#ifdef DEBUG
#define DEBUGMODE(code) code
#else
#define DEBUGMODE(code)
#endif

#define FUSE_USE_VERSION 26
#define EVENT_SIZE  ( sizeof (struct inotify_event) )
#define EVENT_BUF_LEN     ( 1024 * ( EVENT_SIZE + 16 ) )

#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <fuse.h>
#include <libgen.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/inotify.h>
#include <string.h>


#ifdef HAVE_SYS_XATTR_H
#include <sys/xattr.h>
#endif

static const char *name = "/NAMES";
static const char *code = "/CODES";
static const char *fileExtension = ".txt\0";
static const char *codeAtt = "code: ";
static const char *hoodAtt = "neighborhood: ";
static const char *cityAtt = "city: ";
static const char *districtAtt = "district: ";
static const char *latAtt = "latitude: ";
static const char *longAtt = "longitude: ";

#define CITYCOLUMN 2
#define POSTCOLUMN 0
#define DISTRICTCOLUMN 3
#define HOODCOLUMN 1
#define LATCOLUMN 4
#define LONGCOLUMN 5

struct state {
  char ***table;
  int row_count;
  int column_count;
  char *path;
  char *mpath;
};

static int pcm_readdir(
  const char *path,
  void *buf,
  fuse_fill_dir_t filler,
  off_t offset,
  struct fuse_file_info *fi
){
    printf("-------------------------------\n Read Directory\n");
    char tmp[200];
    int row=0;
    struct state * data = ((struct state *) fuse_get_context()->private_data);
    filler(buf, ".", NULL, 0);
    filler(buf, "..", NULL, 0);
    //Add subdirectories under here
    if (strcmp(path,"/")==0) {
      filler(buf,name+1,NULL,0);
      filler(buf,code+1,NULL,0);
    }else if(strcmp(path,name)==0){
      while(row<data->row_count){
        //push city
        strcpy(tmp,data->table[row][CITYCOLUMN]);
        filler(buf,tmp,NULL,0);
        row++;
        //bypass same cities
        while (row<data->row_count && !strcmp(tmp,data->table[row][CITYCOLUMN]))
          row++;
      }
    }
    else if(strcmp(path,code)==0){
      while(row<data->row_count){
        //push first two number of code
        tmp[0]=data->table[row][POSTCOLUMN][0];
        tmp[1]=data->table[row][POSTCOLUMN][1];
        tmp[2]='\0';
        filler(buf,tmp,NULL,0);
        row++;
        //bypass same codes
        while (row<data->row_count
          && tmp[0]==data->table[row][POSTCOLUMN][0]
          && tmp[1]==data->table[row][POSTCOLUMN][1])
          row++;
      }
    }else{
      //Either city,district or code
      char *tPath=NULL;
      char *tPath1;
      char *tPath2;
      tPath=malloc(200 * sizeof *tPath);
      strcpy(tPath,path);
      tPath1=tPath;
      tPath2=tPath1;
      tPath1=strchr(tPath+1,'/');
      if(tPath1==NULL)
        return -ENOENT;
      *tPath1='\0'; //Put end of string instead of first back slash
      tPath1++; //Now tpath1 has path starting from city name or first two numbers
      printf("tPath:%s\ntPath1:%s\ntPath2:%s\n",tPath,tPath1,tPath2);
      if(!strcmp(tPath, name)){
        //Check for city name
        tPath2=tPath1;
        tPath2=strchr(tPath1,'/');
        if(tPath2!=NULL){
          *tPath2='\0'; //now tpath1 has only city name
          tPath2++; //Now tpath2 has path starting from district name
        }
        while(row<data->row_count && strcmp(tPath1,data->table[row][CITYCOLUMN]))
          row++;
        if(row!=data->row_count){
          printf("its a city! %d\n",row);
          if(tPath2==NULL){
            //no district name
            printf("Push districts\n");
            while(row<data->row_count && !strcmp(tPath1,data->table[row][CITYCOLUMN])) {
              //push district
              strcpy(tmp,data->table[row][DISTRICTCOLUMN]);
              filler(buf,tmp,NULL,0);
              row++;
              //bypass same districts
              while (row<data->row_count && !strcmp(tmp,data->table[row][DISTRICTCOLUMN]))
                row++;
            }
          }else{
            //Check for district name
            printf("Checking for district!\n");
            printf("asdadfas tPath:%s\ntPath1:%s\ntPath2:%s\n",tPath,tPath1,tPath2);
            while(row<data->row_count && strcmp(tPath2,data->table[row][DISTRICTCOLUMN]))
              row++;
            if(row!=data->row_count){
              printf("It's a district!\n");
              //push neighboorhood files
              while(row<data->row_count && !strcmp(tPath2,data->table[row][DISTRICTCOLUMN])) {
                //push neighboorhood
                strcpy(tmp,data->table[row][HOODCOLUMN]);
                strcpy(strchr(tmp,'\0'),fileExtension);
                filler(buf,tmp,NULL,0);
                row++;
              }
            }
          }
        }
      }else if(!strcmp(tPath, code)){
        //check for double digits
        while(row<data->row_count
          && (*tPath1!=data->table[row][POSTCOLUMN][0]
          || *(tPath1+1)!=data->table[row][POSTCOLUMN][1]))
            row++;
        if(row!=data->row_count){
          printf("It's a double digit postcode!\n");
          //push postcode files
          while(row<data->row_count
           && (*tPath1==data->table[row][POSTCOLUMN][0]
           && *(tPath1+1)==data->table[row][POSTCOLUMN][1])) {
             //push postcode
             strcpy(tmp,data->table[row][POSTCOLUMN]);
             strcpy(strchr(tmp,'\0'),fileExtension);
             filler(buf,tmp,NULL,0);
             row++;
          }
        }
      }
    }
    return 0;
}

int findData(const char *path, struct state* data){

  char *tPath=NULL;
  char *tPath1;
  char *tPath2;
  char *tPath3;
  int row=0;

  tPath=malloc(200 * sizeof *tPath);
  strcpy(tPath,path);
  tPath1=tPath;
  tPath1=strchr(tPath+1,'/');
  tPath2=tPath;
  tPath3=tPath;

  printf("-------------------------------\n Find data\n");

  if(tPath1==NULL)
    return -1;
  *tPath1='\0'; //Put end of string instead of first back slash
  tPath1++; //Now tpath1 has path starting from city name or first two numbers
  printf("tPath:%s\ntPath1:%s\n",tPath,tPath1);
  tPath2=strchr(tPath1,'/');
  if(tPath2!=NULL){
    *tPath2='\0'; //now tpath1 has only city name
    tPath2++; //Now tpath2 has path starting from district name
    printf("tPath2:%s\n",tPath2);
  }
  if(!strcmp(tPath, name)){
    //Check for city name
    while(row<data->row_count && strcmp(tPath1,data->table[row][CITYCOLUMN]))
      row++;
    printf("row:%d\n",row );
    if(row!=data->row_count){
      if(tPath2==NULL){
        //no district name
        printf("It's a city!\n");
        free(tPath);
        return row;
      }else{
        //Check for district name
        tPath3=strchr(tPath2,'/');
        if(tPath3!=NULL){
          *tPath3='\0';
          tPath3++;
        }
        printf("tPath:%s\ntPath1:%s\ntPath2:%s\n",tPath,tPath1,tPath2);
        row=0;
        while(row<data->row_count && strcmp(tPath2,data->table[row][DISTRICTCOLUMN]))
          row++;
        if(row!=data->row_count){
          printf("It's a district!\n");
          //Check for hood
          if(tPath3!=NULL){
            *(strchr(tPath3,'.'))='\0'; //remove file extension
            printf("tPath:%s\ntPath1:%s\ntPath2:%s\n,tPath3:%s\n",tPath,tPath1,tPath2,tPath3);
            while(row<data->row_count && strcmp(tPath3,data->table[row][HOODCOLUMN]))
              row++;
            if(row!=data->row_count){
              printf("It's a hood!\n");
              free(tPath);
              return row;
            }
          }
          free(tPath);
          return row;
        }
      }
    }
  }
  else if(!strcmp(tPath, code) && *tPath1>='0' && *tPath1<='9'
    && *(tPath1+1)>='0' && *(tPath1+1)<='9' && *(tPath1+2)=='\0'){
    printf("Found code!\ntPath:%s\ntPath1:%s\ntPath2:%s\n",tPath,tPath1,tPath2);
    //check for first two digits
    printf("1:%c 2:%c\n",*tPath1,*(tPath1+1));
    while(row<data->row_count
      && (*tPath1!=data->table[row][POSTCOLUMN][0]
      || *(tPath1+1)!=data->table[row][POSTCOLUMN][1]))
        row++;
    printf("%s\n",data->table[row][POSTCOLUMN] );
    if(row!=data->row_count){
      if(tPath2!=NULL){
        *(strchr(tPath2,'.'))='\0'; //remove file extension
        printf("275:tPath:%s\ntPath1:%s\ntPath2:%s\n",tPath,tPath1,tPath2);
        while(row<data->row_count && strcmp(tPath2,data->table[row][POSTCOLUMN]))
          row++;
        if(row!=data->row_count){
          printf("It's a code!\n");
          free(tPath);
          return row;
        }else{
          free(tPath);
          return -1;
        }
      }
      free(tPath);
      return row;
    }
    free(tPath);
    return -1;
    }
  free(tPath);
  return -1;
  }

int isDirectory(const char *path){
  char *tPath=NULL;
  char *tPath1;
  char *tPath2;
  struct state * data = ((struct state *) fuse_get_context()->private_data);
  int row=0;
  if(strcmp(path, "/") == 0
  || strcmp(path, name) == 0
  || strcmp(path, code) == 0
  )
    return 1;
  else{
    printf("----------------------------------------------------\nChecking directory:%s\n",path);
    tPath=malloc(200 * sizeof *tPath);
    strcpy(tPath,path);
    tPath1=tPath;
    tPath1=strchr(tPath+1,'/');
    tPath2=tPath1;
    if(tPath1==NULL)
      return 0;
    *tPath1='\0'; //Put end of string instead of first back slash
    tPath1++; //Now tpath1 has path starting from city name or first two numbers
    printf("tPath:%s\ntPath1:%s\ntPath2:%s\n",tPath,tPath1,tPath2);
    if(!strcmp(tPath, name)){
      //Check for city name
      tPath2=strchr(tPath1,'/');
      if(tPath2!=NULL){
        *tPath2='\0'; //now tpath1 has only city name
        tPath2++; //Now tpath2 has path starting from district name
      }
      while(row<data->row_count && strcmp(tPath1,data->table[row][CITYCOLUMN]))
        row++;
      printf("row:%d\n",row );
      if(row!=data->row_count){
        if(tPath2==NULL){
          //no district name
          printf("It's a directory!\n");
          free(tPath);
          return 1;
        }else{
          printf("It's a district!\n");
          //Check for district name
          printf("tPath:%s\ntPath1:%s\ntPath2:%s\n",tPath,tPath1,tPath2);
          row=0;
          while(row<data->row_count && strcmp(tPath2,data->table[row][DISTRICTCOLUMN]))
            row++;
          if(row!=data->row_count){
            printf("It's a directory!\n");
            free(tPath);
            return 1;
          }
        }

      }
    }
    else if(!strcmp(tPath, code) && *tPath1>='0' && *tPath1<='9'
      && *(tPath1+1)>='0' && *(tPath1+1)<='9' && *(tPath1+2)=='\0'){
      //check for first two digits
      printf("1:%c 2:%c\n",*tPath1,*(tPath1+1));
      while(row<data->row_count
        && (*tPath1!=data->table[row][POSTCOLUMN][0]
        || *(tPath1+1)!=data->table[row][POSTCOLUMN][1]))
          row++;
      printf("%s\n",data->table[row][POSTCOLUMN] );
      if(row!=data->row_count){
        free(tPath);
        return 1;
      }
      //TODO add file check and return -1 for errors maybe
    }
  }
  if(tPath!=NULL)
    free(tPath);
  return 0;
}

static int pcm_getattr(
  const char *path,
  struct stat *stbuf
){

    printf("-------------------------------\n Get attributes\n");

    memset(stbuf, 0, sizeof(struct stat));

    if (isDirectory(path)
  ){
      //Directories
      stbuf->st_mode = S_IFDIR | 0755;
      stbuf->st_nlink = 2;
    }else{
      //Files
      stbuf->st_mode = S_IFREG | 0444;
      stbuf->st_nlink = 1;
      stbuf->st_size = 1024;
    }
    return 0;
}

static int pcm_read(
  const char *path,
  char *buf,
  size_t size,
  off_t offset,
  struct fuse_file_info *finfo
){
    int len,row;
    struct state * data = ((struct state *) fuse_get_context()->private_data);
    char *s;
    printf("-----------------------------------------------\n%s\n",path);
    //Parse path

    row=findData(path,data);
    printf("Found row:%d\n",row);
    if(row<0 || row>=data->row_count)
      return -ENOENT;

    s = malloc(200 * sizeof (char));

    strcpy(s,codeAtt);
    strcpy(s+strlen(s),data->table[row][POSTCOLUMN]);
    *(s+strlen(s)+1)='\0';
    *(s+strlen(s))='\n';

    strcpy(s+strlen(s),hoodAtt);
    strcpy(s+strlen(s),data->table[row][HOODCOLUMN]);
    *(s+strlen(s)+1)='\0';
    *(s+strlen(s))='\n';

    strcpy(s+strlen(s),cityAtt);
    strcpy(s+strlen(s),data->table[row][CITYCOLUMN]);
    *(s+strlen(s)+1)='\0';
    *(s+strlen(s))='\n';

    strcpy(s+strlen(s),districtAtt);
    strcpy(s+strlen(s),data->table[row][DISTRICTCOLUMN]);
    *(s+strlen(s)+1)='\0';
    *(s+strlen(s))='\n';

    strcpy(s+strlen(s),latAtt);
    strcpy(s+strlen(s),data->table[row][LATCOLUMN]);
    *(s+strlen(s)+1)='\0';
    *(s+strlen(s))='\n';

    strcpy(s+strlen(s),longAtt);
    strcpy(s+strlen(s),data->table[row][LONGCOLUMN]);
    *(s+strlen(s)+1)='\0';
    *(s+strlen(s))='\n';

    printf("%s\n%d\n",s,strlen(s));

    len = strlen(s);
    if (offset < len){
      if (offset + size > len)
        size = len - offset;
      memcpy(buf, s + offset, size);
    }else
      size = 0;
    return size;
}

static int pcm_rmdir(const char *path)
{	
      return -EROFS;   
}

static int pcm_unlink(const char *path)
{	
	struct state * data = ((struct state *) fuse_get_context()->private_data);
	char * str=strrchr(path, '/');
	char * end=strrchr(path, '.');
	char * name;
		
	int newSize= strlen(path)  + strlen(data->mpath) + 1; 
	char * newBuffer = (char *)malloc(newSize);
	strcpy(newBuffer,data->mpath);
    strcat(newBuffer,path);	
	
	printf("File Path:%s\n", newBuffer);
	int rm=0;
	rm=unlink(newBuffer);
	if(rm == -1)
	{	
		
		printf("Unable to delete the file\n");
		perror("Error");
		return -errno;
	}
	else
	{
		printf("File Deleted\n");
	}	
	
	int row_un=0;
	row_un = findData(path, data);
	data->table[row_un][POSTCOLUMN]="-1";
	writeCVS(data);
	refreshData(data);
    return 1;		
}

static int pcm_rename(const char *from, const char *to)
{	
	struct state * data = ((struct state *) fuse_get_context()->private_data);
	char * str_f=strrchr(from, '/');
	str_f=str_f+1;
	char * end_f=strrchr(from, '.');
	char * name_f;
	copy_to_pointer(name_f, str_f, end_f);
	
	char * str_t=strrchr(to, '/');
	str_t=str_t+1;
	char * end_t=strrchr(to, '.');
	char * name_t;
	copy_to_pointer(name_t, str_t, end_t);
	printf("From: %s, To:%s", name_f, name_t);
	char * ptr;
	char * ptr_name;	
	char * ptr_start;
	char * ptr_hold;
	char * ptr_end;
	char ret= '/';
	
	
	int newSize_f= strlen(from)  + strlen(data->mpath) + 1; 
	int newSize_t= strlen(to)  + strlen(data->mpath) + 1; 
	
	char * newBuffer_f = (char *)malloc(newSize_f);
	char * newBuffer_t = (char *)malloc(newSize_t);
	
	strcpy(newBuffer_f,data->mpath);
	strcpy(newBuffer_t,data->mpath);
	
    strcat(newBuffer_f,from);	
    strcat(newBuffer_t,to);	
    printf("From Path:%s, To Path:%s", newBuffer_f, newBuffer_t);
	int rn=0;
	rn=rename(newBuffer_f, newBuffer_t);
	if(rn == -1)
	{
		return -errno;
	}
	int row_rn;	
	ptr = malloc(200 * sizeof *from);
	strcpy(ptr,from);
		row_rn = findData(from, data);
		ptr_start=strrchr(from, ret);
		ptr_start=ptr_start+1;
		int isa=ptr_start[0];		
		ptr_end=strrchr(from, '.');		
		if(ptr_start==NULL)
			return EROFS;
		copy_to_pointer(ptr_name, ptr_start, ptr_end);
		if(isalpha(isa))
		{
		data->table[row_rn][POSTCOLUMN]=ptr_name;
		}
		else
		{			
		data->table[row_rn][HOODCOLUMN]=ptr_name;
		}
		
	writeCVS(data);
	refreshData(data);
	return 1;
}

int copy_to_pointer(char * ptr_name, char * ptr_s, char * ptr_e)
{	
	char * ptr3;
	ptr3=ptr_s;
	int k=0;
    while(1)
    {
		if(ptr3==ptr_e)
		{
			break;
		}
		
		k++;
		ptr3=ptr3+1;
	}
    ptr_name = (char *)malloc(k+1);
	strncpy(ptr_name,ptr_s,k);
	
	return 1;
}

void cleanup(struct state* data){
	int i=0;
	int j=0;
  if(data->table){
    for(i=0;i<data->row_count;i++){
      for(j=0;j<data->column_count;j++){
        free(data->table[i][j]);
      }
      free(data->table[i]);
    }
    free(data->table);
  }

  if(data->path)
    free(data->path);
}


static void pcm_exit(void *data){
  cleanup((struct state*)data);
}

static struct fuse_operations pcm_oper = {
  //pcm stands for postal code mapper
  .getattr = pcm_getattr,
  .readdir = pcm_readdir,
  .read = pcm_read,
  .unlink = pcm_unlink,
  .rmdir = pcm_rmdir,
  .rename = pcm_rename,
  .destroy = pcm_exit,
};

int refreshData(struct state* data){
    printf("Refreshing Data\n");
    int j=0;
    int i=0;
    int k=0;
    int column_start,column_length;
    int row=0;
    char* line=NULL;
    size_t l=0;
    ssize_t length;

    FILE *file;
    file = fopen(data->path, "r++");
    if (file==NULL) {
      printf("Can not open file");
      return  -1;
    }

    while ((length = getline(&line, &l, file)) != -1) {
      data->row_count++;
    }

    data->table=malloc(data->row_count * sizeof *(data->table));

    if(data->table==NULL){
      return -1;
    }
    if (line)
        free(line);
    l=0;
    rewind(file);

    while ((length = getline(&line, &l, file)) != -1) {
        j=-1;
        data->table[row]=malloc(data->column_count * sizeof *(data->table[row]));
        if(data->table[row]==NULL){
          return -1;
        }
        for(i=0;i<data->column_count;i++){
          j++;//pass tab
          column_start=j;
          while(j<length && line[j]!='\t')
            j++;
          column_length=j-column_start;
          //printf("row_count:%d,row:%d,column_start:%d,column_length:%d,j:%d,i:%d,length:%d\n",data->row_count,row,column_start,column_length,j,i,length );
          data->table[row][i]=malloc(column_length * sizeof *(data->table[row][i]));
          if(data->table[row][i]==NULL){
            return -1;
          }
          for(k=0;k<column_length;k++){
            data->table[row][i][k]=line[k+column_start];
          }
        }
        row++;
    }

    fclose(file);
    if (line)
        free(line);

    return 0;
}

int writeCVS(struct state* data)
{
	FILE *file;
    file = fopen(data->path, "w+");
    if (file==NULL) {
      printf("Can not open file");
      return  -1;
    }
    printf("Writing To File\n");
	int i,j,k=0;
	for(i=0;i<data->row_count;i++)
	{
		for(j=0;i<data->column_count;j++)
		{
			if(strcmp(data->table[i][POSTCOLUMN], "-1"))
				break;
			
			fprintf(file, "%s", data->table[i][j]);	
		}
		fprintf(file, "\n");	
	}
	fclose(file);
	return 1;
}

int main(int argc, char *argv[])
{

	int length, i = 0;
	int fd;
	int wd;
	char buffer[EVENT_BUF_LEN];
	int mSize= strlen(argv[1]) + 1; 
    struct state *data;
    data=malloc(sizeof *data);

    data->table=NULL;
    data->row_count=0;
    data->column_count=6;
    data->path=NULL;
	data->mpath=(char *)malloc(mSize);	
	strcpy(data->mpath,argv[1]);
    int j=0;

    if(argc<3){
      printf("Wrong arguments");
      return 0;
    }

    //get path
    while(argv[argc-1][j]!='\0')
      j++;
    data->path=malloc(j* sizeof *(data->path));
    if(data->path==NULL){
      cleanup(data);
      return -1;
    }
    for(i=0;i<j;i++){
      data->path[i]=argv[argc-1][i];
    }

    if(refreshData(data)<0){
      cleanup(data);
      return -1;
    }

    argc--;
    j=fuse_main(argc, argv, &pcm_oper, data);
    if(j<0){
      cleanup(data);
      return -1;
    }

  	fd = inotify_init();
  	wd = inotify_add_watch( fd, data->path, IN_MODIFY);
  	length = read( fd, buffer, EVENT_BUF_LEN );

  	if(refreshData(data)<0){
        cleanup(data);
        return -1;
    }

  return 0;
}
