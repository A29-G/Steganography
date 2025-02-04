#include<stdio.h>
#include<string.h>
#include"decode.h"
#include"types.h"
#include"common.h"

//checking validations 
Status de_validations(DecodeInfo *decInfo)
{
  	//checking the src_image_fname and .bmp with strstr
    if(strstr(decInfo->src_image_fname,".bmp") == NULL)
    {
        printf("INFO: Invalid Entries..!\n");
	    return e_failure;
    }
   return e_success;
}

//opening the files for decoding
Status OPEN_files(DecodeInfo *decInfo)
{
    printf("INFO: Opening required files\n");
    //encoded image file
    decInfo->fptr_src_image = fopen(decInfo->src_image_fname, "r");

    printf("INFO: Opened steged_img.bmp\n");
    //Do error handling
    if(decInfo->fptr_src_image == NULL)
    {

   		 //print true statement
		printf("INFO: The source_img file was not opened successfully\n");
   		//if source image file is not opened return e_failure
		return e_failure;
    }
    //if source image file is opened return e_success
    return e_success;
}

//decode the lsb to the len
Status decode_byte_to_int(char *buff, int *len)
{
    //loop runs for 32 times
    for(int i=0;i<32;i++)
    {
		//logic to decode the 32 bytes of data 
		if(buff[i]&(1<<0))
			*len = (*len) | (1<<(32-i-1));
		else
	    	*len = (*len) & ~(1<<(32-i-1));
    }
    return e_success;
}

//decode the lsb to the byte
Status decode_byte_to_lsb(char *buff, char *str)
{
    //loop runs for 8 times
    for(int i=0;i<8;i++)
    {
    //logic to decode one byte of data
	if(buff[i]&(1<<0))
	    *str = (*str | (1<<(8-i-1)));
	else
	    *str = (*str & ~(1<<(8-i-1)));
    }
}

//decoding the magic string fuction defination
Status decode_magic_string(DecodeInfo *decInfo)
{
    printf("INFO: Decoding Magic String Signature\n");
    int magic_len=0;
    //declaration of buffers
    char buff[32],magic_str[magic_len];
    //reading the 32 bytes of data to the buffer
    fread(buff,32,1,decInfo->fptr_src_image);
	//calling the byte_to_int function
    decode_byte_to_int(buff,&magic_len);

    //loop runs length of magic string times
    for(int i=0;i<magic_len;i++)
    {

   		//reading the 8 bytes of data to the buffer
		fread(buff,8,1,decInfo->fptr_src_image);
		//calling the byte_to_lsb fuction
		decode_byte_to_lsb(buff, &magic_str[i]);
    }
    magic_str[magic_len] = '\0';
    //printf("Magic string is %s\n",magic_str);
	//comparing the magic string
    if((strcmp(MAGIC_STRING,magic_str) != 0))
	return e_failure;

    return e_success;
}

//decode the file extension
Status decode_secret_file_ext(DecodeInfo *decInfo)
{
    printf("INFO: Decoding Output File Extension\n");
    //declaration of buffers
    char buff[32];
    int ext_len=0;	
	//reading the 32 bytes of data from src_image
    fread(buff,32,1,decInfo->fptr_src_image);
	//calling the byte_to_int function
    decode_byte_to_int(buff,&ext_len);
    //printf("Done\n");
    char ext[ext_len];

	//loop reu upto ext_len times
    for(int i=0;i<ext_len;i++)
    {
    //read 8 bytes of data to the buffer
	fread(buff,8,1,decInfo->fptr_src_image);
	//calling the byte_to_lsb function
	decode_byte_to_lsb(buff,&ext[i]);
    }
    //storing null character
    ext[ext_len]='\0';

    char op_file[strlen(decInfo->secret_fname)+ext_len];

    //copying the data from op_file to secret_fname
    strcpy(op_file,decInfo->secret_fname);
    strcat(op_file,ext);
    decInfo->fptr_secret = fopen(op_file,"w");
    return e_success;
}

//decode the secret file data
Status decode_secret_file_data(DecodeInfo *decInfo)
{
    printf("INFO: Decoding File Size\n");
    //declaration of variables
    char buff[32];
    int f_size;
    //copying the 32 bytes of data from the encoded image to the buffer
    fread(buff,32,1,decInfo->fptr_src_image);

	//calling the byte_to_int function
    decode_byte_to_int(buff, &f_size);

    printf("INFO: Done\n");
    //printf("the file size is %d\n",f_size);
   
    printf("INFO: Decoding File Data\n");
    char secret_msg[f_size];

	//loop run upto f_size times
    for(int i=0;i<f_size;i++)
    {
    //copying the 8 bytes of data from the encoded image to the buffer
	fread(buff,8,1,decInfo->fptr_src_image);

    //calling the decode lsb to byte
	decode_byte_to_lsb(buff,&secret_msg[i]);
	fputc(secret_msg[i],decInfo->fptr_secret);
    }
    //storing null character
    secret_msg[f_size]='\0';

	return e_success;
}

Status do_decoding(DecodeInfo *decInfo) 
{
    if(de_validations(decInfo) == e_failure)
	return e_failure;
    //printing decoding started message
    printf("INFO:***Decoding Procedure Started***\n");
    if(OPEN_files(decInfo) != e_success)
    {
  	 	//if file is not open print open file failure
		printf("INFO: open file failure..!\n");

   	    //if file is not open return e_failure
		return e_failure;
    }

    fseek(decInfo->fptr_src_image,54,SEEK_SET);
    
	//checking the decode magic string data
    if(decode_magic_string(decInfo) == e_success)
    //if decoding done print true statement
	printf("INFO: Done\n");
    else
    {
   // print error message
   printf("INFO: Image file is not stegged..!!\n");
	return e_failure;
    }
	
	//checking the secret file extenstion
    if(decode_secret_file_ext(decInfo) == e_success)
		//printing a meaasage
		printf("INFO: Done\n");
    else
    {
		//printfing a error statement
		printf("INFO: Decoding extnsion failed\n");
		return e_failure;
    }
	
	//comparing the secret_fname and decoded.txt
    if(strcmp(decInfo->secret_fname,"decoded.txt") ==0)
	printf("INFO: Output File not mentioned. Creating decoded.txt as default\n");

    printf("INFO: Opened %s\n",decInfo->secret_fname);
	//printing the statement
    printf("INFO: Done. Opened all required files\n");
    
	//check the secret_file_data
    if(decode_secret_file_data(decInfo) == e_success)

    //if decoding secret message successfully print done message
	printf("INFO: Done\n");

    else
    {
    //if decoding secret message not done print error message
	printf("INFO: Decoding secret msg failed\n");

    //if decoding secret message failed return e failure
	return e_failure;
    }
     //closing source image file 
    fclose(decInfo->fptr_src_image);
    fclose(decInfo->fptr_secret);
	   

    return e_success;

}

