#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <stdlib.h> // Para size_t y malloc/free

void read_values_from_file(const char* file, float* data, size_t size) {
    FILE* values = fopen(file, "rb"); // "rb" para lectura binaria.

    if (values == NULL) {
        perror("Error opening file for reading");
        return;
    }

    fread(data, sizeof(float), size / sizeof(float), values); // size / sizeof(float) para obtener el n�mero de elementos.

    fclose(values);
}


void write_values_to_file(const char* file, float* data, size_t size) {
    FILE* values = fopen(file, "w"); // "w" para escritura de texto.

    if (values == NULL) { // Problemas al abrir.
        perror("Error opening file for writing");
        return;
    }

    size_t num_elements = size / sizeof(float); // Obtener el n�mero de elementos.
    int cont = 0;

    for (size_t i = 0; i < num_elements; i++) {
        fprintf(values, "%10.2f ", data[i]);
        cont++;

        if (cont == 6) {
            fprintf(values, "\n");
            cont = 0;
        }
    }
    if (cont != 0) {
        fprintf(values, "\n");
    }

    fclose(values);
}
//                                                  ----------------------------ESCRITURA SI SE QUIERE BINARIO-------------------------------------------------


/*void write_values_to_file(const char* file, float* data, size_t size) {
    FILE* values = fopen(file, "wb"); // "wb" para escritura binaria

    if (values == NULL) {
        perror("Error opening file for writing");
        return;
    }

    fwrite(data, sizeof(float), size / sizeof(float), values); // size / sizeof(float) para obtener el n�mero de elementos

    fclose(values);
}*/