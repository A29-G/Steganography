# Steganography
**LSB Image Steganography**

This C program implements LSB (Least Significant Bit) steganography for hiding and retrieving secret messages within BMP image files. The program comprises two main components: encoding and decoding.

Encoding Process: The program reads a source BMP image and a secret file, validates their formats and sizes, checks the image’s capacity to embed the secret file, and embeds the secret data into the least significant bits of the image’s pixels. The modified image, now containing the hidden message, is saved as a new BMP file.

Decoding Process: The program reads the stego image, validates its format, and decodes the hidden data by extracting it from the least significant bits of the image’s pixels. The decoded data includes a magic string, file extension, file size, and the secret file content, which is reconstructed and saved as an output file.

Overall, this program effectively demonstrates the use of LSB steganography to securely hide and retrieve secret data within BMP images, maintaining the integrity of the original image.



### Encoding Functions Description:

1. **get_image_size_for_bmp(FILE *fptr_image)**:
    - **Purpose**: This function reads the width and height of a BMP image to calculate its size.
    - **Process**: It extracts the image dimensions from the BMP file header and returns the size.

2. **validations(EncodeInfo *encInfo)**:
    - **Purpose**: Validates the file extensions and sizes of the source image, secret file, and stego image.
    - **Process**: Ensures the input files have the correct formats and are not empty, preventing invalid data from being processed.

3. **check_capacity(EncodeInfo *encInfo)**:
    - **Purpose**: Checks if the source BMP image can accommodate the secret file.
    - **Process**: Compares the size of the secret file with the capacity of the BMP image to determine if embedding is feasible.

4. **open_files(EncodeInfo *encInfo)**:
    - **Purpose**: Opens the required files (source image, secret file, and stego image) and verifies their validity.
    - **Process**: Opens the files in appropriate modes and checks for errors, ensuring all files are ready for read/write operations.

5. **copy_bmp_header(FILE *fptr_src_image, FILE *fptr_dest_image)**:
    - **Purpose**: Copies the BMP header from the source image to the stego image.
    - **Process**: Reads the header information from the source image and writes it to the stego image, maintaining the format.

6. **encode_magic_string(char *magic_string, EncodeInfo *encInfo)**:
    - **Purpose**: Encodes a magic string into the BMP image.
    - **Process**: Embeds a predefined string into the least significant bits of the image pixels, serving as an identifier for the stego image.

7. **encode_secret_file_extn(char *file_extn, EncodeInfo *encInfo)**:
    - **Purpose**: Encodes the extension of the secret file into the BMP image.
    - **Process**: Hides the file extension (e.g., .txt, .jpg) within the image, enabling the identification of the secret file type during extraction.

8. **encode_secret_file_size(long int file_size, EncodeInfo *encInfo)**:
    - **Purpose**: Encodes the size of the secret file into the BMP image.
    - **Process**: Stores the file size within the image, ensuring accurate extraction of the complete secret file.

9. **encode_secret_file_data(EncodeInfo *encInfo)**:
    - **Purpose**: Encodes the actual secret file data into the BMP image.
    - **Process**: Embeds the binary data of the secret file into the least significant bits of the image pixels, hiding the message within the image.

10. **copy_remaining_img_data(FILE *fptr_src, FILE *fptr_dest)**:
    - **Purpose**: Copies the remaining data from the source image to the stego image after encoding is done.
    - **Process**: Ensures that the rest of the image data is copied intact, maintaining the overall image structure and appearance.



### Decoding Functions Description:

1. **de_validations(DecodeInfo *decInfo)**:
    - **Purpose**: Validates the BMP image by checking the file extension.
    - **Process**: Ensures the input BMP file has the correct format, preventing invalid data from being processed.

2. **OPEN_files(DecodeInfo *decInfo)**:
    - **Purpose**: Opens the BMP image file for reading and handles errors if the file can't be opened.
    - **Process**: Opens the file in read mode and checks for errors, ensuring the file is ready for read operations.

3. **decode_byte_to_int(char *buff, int *len)**:
    - **Purpose**: Decodes a 32-bit integer from the LSB of 32 bytes.
    - **Process**: Extracts a 32-bit integer by decoding the least significant bits of 32 consecutive bytes.

4. **decode_byte_to_lsb(char *buff, char *str)**:
    - **Purpose**: Decodes a single byte from the LSB of 8 bytes.
    - **Process**: Extracts a single byte by decoding the least significant bits of 8 consecutive bytes.

5. **decode_magic_string(DecodeInfo *decInfo)**:
    - **Purpose**: Decodes a magic string from the BMP image to verify if the image contains a hidden message.
    - **Process**: Extracts a predefined string to confirm the presence of a hidden message in the image.

6. **decode_secret_file_ext(DecodeInfo *decInfo)**:
    - **Purpose**: Decodes the file extension of the hidden file.
    - **Process**: Extracts the file extension (e.g., .txt, .jpg) from the BMP image, identifying the type of the hidden file.

7. **decode_secret_file_data(DecodeInfo *decInfo)**:
    - **Purpose**: Decodes the hidden file size and its data from the BMP image.
    - **Process**: Extracts the size and data of the hidden file from the least significant bits of the image pixels.

8. **do_decoding(DecodeInfo *decInfo)**:
    - **Purpose**: Coordinates the entire decoding process, from validations to reading and decoding the hidden message.
    - **Process**: Ensures the source image is valid, opens the necessary files, decodes the magic string, file extension, file size, and finally the hidden file data. The decoded file is then written to an output file.

This comprehensive set of functions ensures that your hidden file is efficiently extracted from the BMP image using LSB steganography techniques while maintaining the integrity of the original image. 
