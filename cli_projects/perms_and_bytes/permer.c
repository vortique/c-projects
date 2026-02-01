#include "../argparse.h"
#include "perms.h"

#include <stdio.h>

void give_perm_ability_to_file(const char *file_path);

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Hata: Lutfen bir dosya yolu belirtin!\n");
        printf("Kullanim: ./permer <dosya_yolu> [-P]\n");
        return 1;
    }
    
    StringArray argv_string_arr = { .data=argv, .len=argc };
    Args *parsed_args = parser(&argv_string_arr);

    if (parsed_args == NULL || parsed_args->arguments.len == 0) {
        printf("Argumanlar ayristirilamadi veya dosya yolu eksik.\n");
        return 1;
    }

    if (string_array_includes(&(parsed_args->flags), "-P") != -1) {
        give_perm_ability_to_file(parsed_args->arguments.data[0]);
    }

    free(parsed_args->arguments.data);
    free(parsed_args->flags.data);
    free(parsed_args);

    return 0;
}

void give_perm_ability_to_file(const char *file_path) {
    uint8_t perm_bits = 0x01;
    unsigned char c;
    
    FILE *file = fopen(file_path, "rb");
    if (file == NULL) return;
    FILE *temp = fopen("tmp.tmp", "wb");
    if (temp == NULL) return;

    fwrite(&perm_bits, 1, 1, temp);
    
    while (fread(&c, 1, 1, file) == 1) {
        fwrite(&c, 1, 1, temp);
    }

    fclose(file);
    fclose(temp);

    remove(file_path);
    rename("tmp.tmp", file_path);
}
