//
// Created by Shreejit Murthy on 18/9/2024.
//

#include "utils.h"
#include <log/log.h>
#include <stdlib.h>

char* readFile(const char* filePath) {
    if (filePath != NULL) {
        // Open the file
        SDL_IOStream* io = SDL_IOFromFile(filePath, "rb");
        if (io == NULL) {
            log_error("SNP::File unsuccessfully read: %s", filePath);
            return NULL;
        }

        // Get the length of the file
        Sint64 length = SDL_GetIOSize(io);
        if (length < 0) {
            log_error("SNP::SDL_IOStream file size error");
            SDL_CloseIO(io);
            return NULL;
        }

        // Allocate memory to read the file content
        char* content = (char*)malloc(length + 1);
        if (content == NULL) {
            log_error("SNP::File memory allocation failed");
            SDL_CloseIO(io);
            return NULL;
        }

        // Read the file content
        Sint64 bytesRead = SDL_ReadIO(io, content, length);
        if (bytesRead != length) {
            log_error("SNP::SDL_IOStream file read error");
            free(content);
            SDL_CloseIO(io);
            return NULL;
        }

        // Null-terminate the content
        content[length] = '\0';

        SDL_CloseIO(io);
        return content;
    } else {
        return NULL;
    }
}