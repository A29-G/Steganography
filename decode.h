#include<stdio.h>
#ifndef DECODE_H
#define DECODE_H
#include"types.h"
typedef struct _DecodeInfo
{
	// Source Image info 
    char *src_image_fname;
    FILE *fptr_src_image;

	// Secret file info 
    char *secret_fname;
    FILE *fptr_secret;
    
} DecodeInfo;

/* Perform the encoding */
Status do_decoding(DecodeInfo *decInfo); 

/* Get file pointers for i/p and o/p files */
Status OPEN_files(DecodeInfo *decInfo);

/* Decode Magic string */
Status decode_magic_string(DecodeInfo *decInfo);

/* Decode a LSB into int of secret data */
Status decode_byte_to_int(char *buff, int *len);

/* Decode a LSB into byte of secret data */
Status decode_byte_to_lsb(char *buff, char *magic_str);

/* Decode secret file extenstion */
Status decode_secret_file_ext(DecodeInfo *decInfo);

/* Decode secret file data */
Status decode_secret_file_data(DecodeInfo *decInfo);

/* Validations for decode */
Status de_validations(DecodeInfo *decInfo);


#endif

