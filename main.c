/*-------------------------------------------------------------------------------------------------------------------
 Project name :- IMAGE STEGANOGRAPHY
 Author				:- Aishwarya Giriyal
 -------------------------------------------------------------------------------------------------------------------*/
#include<stdio.h>
#include<string.h>
#include"encode.h"
#include"decode.h"

int main(int argc,char *argv[])
{
    EncodeInfo encInfo;
    DecodeInfo decInfo;
    if(argc > 1)
    {
      if(strcmp(argv[1],"-e") == 0)
			{
				if(argc >= 4)
				{
					encInfo.src_image_fname = argv[2];
					encInfo.secret_fname = argv[3];
					if(argc == 4)	    
					encInfo.stego_image_fname = "steged_img.bmp";
					else
					encInfo.stego_image_fname = argv[4];

					if(do_encoding(&encInfo) == e_success)
					printf("***Encoding done successfully***\n");
					else
					return 0;
				}
				else
				{
					printf("Encoding: ./a.out -e <.bmp file> <.txt file> [output file]\n");
					return 0;
				}
			}
			else if(strcmp(argv[1], "-d") == 0)
			{
				if(argc >=3)
				{
					decInfo.src_image_fname = argv[2];
					if(argc == 3)
						decInfo.secret_fname = "decoded.txt";
					else
						decInfo.secret_fname = argv[3];

					if(do_decoding(&decInfo) == e_success)
					printf("***Decoding done successfully***\n");
					else
					return 0;
				}
				else
				{
					printf("Unsupported files or invalid entries\n");
					return 0;
				}
  		}
    }
    else
    {
			printf("Encoding: ./a.out -e <.bmp file> <.txt file> [output file]\n");
    	printf("decoding: ./a.out -d <.bmp file> [output file]\n");
			return 0;
    }
}

