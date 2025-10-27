#include <stdio.h>
#include <openssl/evp.h>
#include <stdlib.h>
int string_len(const char* str) {
    int i = 0;
    while (str[i] != '\0') i++;
    return i;
}
int string_eq(const char* str1, const char* str2){
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0'){
        if (str1[i] != str2[i]) return 0;
        i++;
    }
    if (str1[i] != str2[i]) return 0;
    return 1;
}
// Obtenido de: https://blog.magnatox.com/posts/c_hashing_files_with_openssl/ 
char* md5_string(const char *str) {
	char            buff[128];	                /* buffer for hash */
	unsigned int    md_len;				        /* stores hash length */
	EVP_MD_CTX      *mdctx;				        /* stores hash context */
	unsigned char md_value[EVP_MAX_MD_SIZE];    /* stores hash */
	mdctx = EVP_MD_CTX_new();	/* Initialize new ctx */
	const EVP_MD *EVP_md5();    /* use EVP md5 function */
	EVP_DigestInit_ex(mdctx, EVP_md5(), NULL);	    /* Initializes digest type */
	EVP_DigestUpdate(mdctx, str, string_len(str));	/* Add input to hash context */
	EVP_DigestFinal_ex(mdctx, md_value, &md_len);	/* Finalize hash context */	
    char* out = malloc(sizeof(char)*(md_len*2+1));
    for (int i = 0; i < md_len; ++i) {
        sprintf(&out[i*2], "%02x", md_value[i]);
    }
    return out;
}
const char* hash = "d2a971dcc0b7026a5e2bc26ddcef95a2\0";
void login(const char* entry) {
    if (string_eq(entry, hash)) {
        printf("Login Accepted\n");
    } else {
        printf("Password Incorrect\n");
    }
}
int main(int argc, char* argv[]){
    if (argc != 2) {
        printf("Use: %s <password>\n", argv[0]);
        return 1;
    }
    char* entry = md5_string(argv[1]);
    login(entry);
    free(entry); entry =  NULL;
    return 0;
}
