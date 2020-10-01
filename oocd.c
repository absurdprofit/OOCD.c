#include<stdio.h>

#include<stdlib.h>

struct file{
	
	FILE * ptr;//This is a file pointer
	//char * (*center)(char * a, int b)
	const char * (*read)(FILE * f);//Here, you must read entire file
	void * (*close)(FILE * f);
	void * (*truncate)(struct file * f);
	void * (*write)(FILE * f, const char * string);
	const char * filename;
	const char * mode;
	const char * __repr__;
};

FILE * open(const char * filename,  const char * mode, struct file * f);
const char * read(FILE * f);
const char * read_err(FILE * f);
void * close(FILE * f);
void * truncate(struct file * f);
void __init__(struct file * f, const char * mode, const char * filename);
void * write(FILE * f, const char * string);
void * write_err(FILE * f, const char * string);

int main(){
	struct file f;
	FILE*file;
	const char * string;
	file = open("C:/Users/nayja/Desktop/vid.mp4", "rb", &f);
	string = f.read(file);
	printf("%s", string);
	f.close(file);
}

void * truncate(struct file * f){
	fclose(f -> ptr);
	FILE*ptr = fopen(f -> filename, "w");
	if(ptr == NULL){
		printf("Result: File is Not Found!");
	}
	else{
		fprintf(ptr, "%s", "");
		fclose(ptr);
	}
	f -> ptr = fopen(f -> filename, f -> mode);
}

void * write(FILE * f, const char * string){
	fprintf(f, "%s", string);
}

void * write_err(FILE * f, const char * string){
	printf("\nHere, Cannot Write To File In Read Mode!\n");
}

void __init__(struct file * f, const char * mode, const char * filename){
	if(mode == "wb" || mode == "w"){
		f -> read = read_err;
	}
	else{
		f -> read = read;
	}
	f -> close = close;
	if(mode == "rb" || mode == "r"){
		f -> write = write_err;
	}
	else{
		f -> write = write;
	}
	f -> truncate = truncate;
	f -> mode = mode;
	f -> __repr__ = "\n[__init__(), __repr__, close(), filename, read(), truncate(), write()]\n";
	f -> filename = filename;
}

void * close(FILE * f){
	fclose(f);
}

const char * read(FILE * f){
	char * c;
	long length;
	if(f == NULL){
		printf("File Not Found!");
		exit(1);
	}
	else{
		fseek(f, 0, SEEK_END);
		length = ftell(f);
		fseek(f, 0, SEEK_SET);
		c = malloc(length);
		if(c){
			fread(c, 1, length, f);
		}
	}
	return c;
}

const char * read_err(FILE * f){
	printf("Cannot Read From File In Write Mode!");
}

FILE * open(const char * filename, const char * mode, struct file * f){
	FILE*ptr = fopen(filename, mode);
	__init__(f, mode, filename);
	return ptr;
}
