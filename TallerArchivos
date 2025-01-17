//hecho por Bryan Quevedo y Jimmy Zambrano
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INGREDIENTES 10
#define MAX_ORDENES 100
#define MAX_PRODUCTOS 5

char *productosFijos[] = {
    "Pan Enrollado",
    "Pan de Chocolate",
    "Pan Integral",
    "Orejas de Hojaldre",
    "Suspiros"
};

char *ingredientes[] = {
    "Harina de Trigo",
    "Leche",
    "Mantequilla",
    "Levadura",
    "Azucar",
    "Huevos",
    "Sal",
    "Chocolate",
    "Hojaldre",
    "Vainilla"
};

int inventario[MAX_INGREDIENTES] = {5000, 2500, 1000, 500, 2000, 100, 1000, 500, 50, 100};

int productosIngredientes[MAX_PRODUCTOS][MAX_INGREDIENTES] = {
    {500, 250, 50, 7, 50, 1, 10, 0, 0, 0},    // Pan Enrollado
    {500, 250, 50, 7, 50, 1, 10, 200, 0, 0},  // Pan de Chocolate
    {500, 0, 40, 7, 40, 0, 10, 0, 0, 0},      // Pan Integral
    {0, 0, 0, 0, 100, 0, 20, 0, 0, 0},        // Orejas de Hojaldre
    {0, 0, 0, 0, 250, 4, 15, 0, 0, 0}         // Suspiros
};

int idOrden[MAX_ORDENES];
int idProducto[MAX_ORDENES];
int cantidad[MAX_ORDENES];
int tiempoTotal[MAX_ORDENES];
int totalOrdenes = 0;

void guardarInventario() {
    FILE *archivo = fopen("inventario.txt", "w");
    if (!archivo) {
        printf("No se pudo abrir el archivo de inventario.\n");
        return;
    }

    for (int i = 0; i < MAX_INGREDIENTES; i++) {
        fprintf(archivo, "%d\n", inventario[i]);
    }

    fclose(archivo);
}

void cargarInventario() {
    FILE *archivo = fopen("inventario.txt", "r");
    if (!archivo) {
        printf("No se pudo abrir el archivo de inventario.\n");
        return;
    }

    for (int i = 0; i < MAX_INGREDIENTES; i++) {
        fscanf(archivo, "%d", &inventario[i]);
    }

    fclose(archivo);
}

void guardarOrdenes() {
    FILE *archivo = fopen("ordenes.txt", "w");
    if (!archivo) {
        printf("No se pudo abrir el archivo de ordenes.\n");
        return;
    }

    for (int i = 0; i < totalOrdenes; i++) {
        fprintf(archivo, "%d %d %d %d\n", idOrden[i], idProducto[i], cantidad[i], tiempoTotal[i]);
    }

    fclose(archivo);
}

void cargarOrdenes() {
    FILE *archivo = fopen("ordenes.txt", "r");
    if (!archivo) {
        printf("No se pudo abrir el archivo de ordenes.\n");
        return;
    }

    while (fscanf(archivo, "%d %d %d %d", &idOrden[totalOrdenes], &idProducto[totalOrdenes], &cantidad[totalOrdenes], &tiempoTotal[totalOrdenes]) != EOF) {
        totalOrdenes++;
    }

    fclose(archivo);
}

void mostrarInventario() {
    printf("\n--- Inventario ---\n");
    for (int i = 0; i < MAX_INGREDIENTES; i++) {
        printf("Ingrediente: %s, Stock: %d\n", ingredientes[i], inventario[i]);
    }
}

void mostrarProductosOfertados() {
    printf("\n--- Productos Ofertados ---\n");
    for (int i = 0; i < MAX_PRODUCTOS; i++) {
        printf("Producto: %s\n", productosFijos[i]);
        printf("Ingredientes necesarios:\n");
        for (int j = 0; j < MAX_INGREDIENTES; j++) {
            if (productosIngredientes[i][j] > 0) {
                printf("- %s: %d\n", ingredientes[j], productosIngredientes[i][j]);
            }
        }
        printf("\n");
    }
}

void modificarStock() {
    int id, nuevoStock;
    printf("Ingrese el ID del ingrediente a modificar (1-10): ");
    scanf("%d", &id);
    if (id < 1 || id > MAX_INGREDIENTES) {
        printf("ID invalido.\n");
        return;
    }

    printf("Ingrediente seleccionado: %s\n", ingredientes[id - 1]);
    printf("Ingrese la nueva cantidad en stock: ");
    scanf("%d", &nuevoStock);
    
    inventario[id - 1] = nuevoStock;
    printf("Stock actualizado correctamente.\n");
}

void ingresarOrden() {
    int idProductoSeleccionado, cantidadSeleccionada;
    printf("Ingrese el ID del producto a pedir (1-5): ");
    scanf("%d", &idProductoSeleccionado);

    if (idProductoSeleccionado < 1 || idProductoSeleccionado > MAX_PRODUCTOS) {
        printf("ID de producto invalido.\n");
        return;
    }

    printf("Producto seleccionado: %s\n", productosFijos[idProductoSeleccionado - 1]);
    printf("Ingrese la cantidad deseada: ");
    scanf("%d", &cantidadSeleccionada);

    for (int i = 0; i < MAX_INGREDIENTES; i++) {
        if (productosIngredientes[idProductoSeleccionado - 1][i] * cantidadSeleccionada > inventario[i]) {
            printf("Orden no procede. Ingrediente insuficiente: %s\n", ingredientes[i]);
            return;
        }
    }

    for (int i = 0; i < MAX_INGREDIENTES; i++) {
        inventario[i] -= productosIngredientes[idProductoSeleccionado - 1][i] * cantidadSeleccionada;
    }

    idOrden[totalOrdenes] = totalOrdenes + 1;
    idProducto[totalOrdenes] = idProductoSeleccionado;
    cantidad[totalOrdenes] = cantidadSeleccionada;
    tiempoTotal[totalOrdenes] = cantidadSeleccionada * 120;  // Tiempo promedio de preparación

    totalOrdenes++;
    printf("Orden ingresada correctamente. Tiempo total de preparacion: %d minutos\n", tiempoTotal[totalOrdenes - 1]);
}

void mostrarOrdenes() {
    printf("\n--- Ordenes de Trabajo ---\n");
    for (int i = 0; i < totalOrdenes; i++) {
        printf("ID Orden: %d, Producto: %s, Cantidad: %d, Tiempo Total: %d minutos\n",
            idOrden[i],
            productosFijos[idProducto[i] - 1],
            cantidad[i],
            tiempoTotal[i]);
    }
}

void buscarOrden() {
    int id;
    printf("Ingrese el ID de la orden a buscar: ");
    scanf("%d", &id);

    for (int i = 0; i < totalOrdenes; i++) {
        if (idOrden[i] == id) {
            printf("Orden encontrada: Producto: %s, Cantidad: %d, Tiempo Total: %d minutos\n",
                productosFijos[idProducto[i] - 1],
                cantidad[i],
                tiempoTotal[i]);
            return;
        }
    }

    printf("Orden no encontrada.\n");
}

void menu() {
    int opcion;
    do {
        printf("\n--- Menu ---\n");
        printf("1. Mostrar productos ofertados\n");
        printf("2. Mostrar inventario\n");
        printf("3. Modificar stock\n");
        printf("4. Ingresar orden de trabajo\n");
        printf("5. Mostrar ordenes de trabajo\n");
        printf("6. Buscar orden\n");
        printf("7. Guardar y salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1: mostrarProductosOfertados(); break;
            case 2: mostrarInventario(); break;
            case 3: modificarStock(); break;
            case 4: ingresarOrden(); break;
            case 5: mostrarOrdenes(); break;
            case 6: buscarOrden(); break;
            case 7: 
                guardarInventario();
                guardarOrdenes();
                printf("Datos guardados. Saliendo...\n");
                break;
            default: printf("Opcion invalida.\n");
        }
    } while (opcion != 7);
}

int main() {
    cargarInventario();
    cargarOrdenes();
    menu();
    return 0;
}
