//Hecho por bryan Quevedo y Jimmy Zambrano
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INGREDIENTES 10
#define MAX_ORDENES 100

typedef struct {
    int id;
    char nombre[50];
    int stock; 
} Ingrediente;

typedef struct {
    int idOrden;
    int idProducto;
    int cantidad; 
    int tiempoTotal; 
} OrdenTrabajo;

typedef struct {
    int id;
    char nombre[50];
    int tiempoPreparacion;
    int ingredientes[MAX_INGREDIENTES]; 
} ProductoFijo;

ProductoFijo productosFijos[] = {
    {1, "Pan Enrollado", 140, {500, 250, 50, 7, 50, 1, 10}},
    {2, "Pan de Chocolate", 140, {500, 250, 50, 7, 50, 1, 10, 200}},
    {3, "Pan Integral", 145, {500, 0, 0, 7, 40, 40, 10}},
    {4, "Orejas de Hojaldre", 25, {0, 0, 0, 0, 100, 0, 20, 0}},
    {5, "Suspiros", 70, {0, 0, 0, 0, 250, 4, 15, 0}}
};

Ingrediente inventario[MAX_INGREDIENTES] = {
    {1, "Harina de Trigo", 5000},
    {2, "Leche", 2500},
    {3, "Mantequilla", 1000},
    {4, "Levadura", 500},
    {5, "Azucar", 2000},
    {6, "Huevos", 100},
    {7, "Sal", 1000},
    {8, "Chocolate", 500},
    {9, "Hojaldre", 50},
    {10, "Vainilla", 100}
};

OrdenTrabajo ordenes[MAX_ORDENES];
int totalOrdenes = 0;
int archivoGuardado = 1;

void guardarInventario();
void cargarInventario();
void guardarOrdenes();
void cargarOrdenes();
void mostrarInventario();
void mostrarProductosOfertados();
void modificarStock();
void ingresarOrden();
void mostrarOrdenes();
void buscarOrden();
void menu();

void guardarInventario() {
    FILE *archivo = fopen("inventario.txt", "w");
    if (!archivo) {
        printf("Error al guardar el inventario.\n");
        return;
    }

    for (int i = 0; i < MAX_INGREDIENTES; i++) {
        fprintf(archivo, "%d %s %d\n", inventario[i].id, inventario[i].nombre, inventario[i].stock);
    }
    fclose(archivo);
    archivoGuardado = 1;
    printf("Inventario guardado correctamente.\n");
}

void cargarInventario() {
    FILE *archivo = fopen("inventario.txt", "r");
    if (!archivo) return;

    for (int i = 0; i < MAX_INGREDIENTES; i++) {
        fscanf(archivo, "%d %s %d\n", &inventario[i].id, inventario[i].nombre, &inventario[i].stock);
    }
    fclose(archivo);
    printf("Inventario cargado correctamente.\n");
}

void guardarOrdenes() {
    FILE *archivo = fopen("ordenes.txt", "w");
    if (!archivo) {
        printf("Error al guardar las ordenes.\n");
        return;
    }

    for (int i = 0; i < totalOrdenes; i++) {
        fprintf(archivo, "%d %d %d %d\n",
                ordenes[i].idOrden,
                ordenes[i].idProducto,
                ordenes[i].cantidad,
                ordenes[i].tiempoTotal);
    }
    fclose(archivo);
    printf("Ordenes guardadas correctamente.\n");
}

void cargarOrdenes() {
    FILE *archivo = fopen("ordenes.txt", "r");
    if (!archivo) return;

    totalOrdenes = 0;
    while (fscanf(archivo, "%d %d %d %d\n",
                &ordenes[totalOrdenes].idOrden,
                &ordenes[totalOrdenes].idProducto,
                &ordenes[totalOrdenes].cantidad,
                &ordenes[totalOrdenes].tiempoTotal) != EOF) {
        totalOrdenes++;
    }
    fclose(archivo);
    printf("Ordenes cargadas correctamente.\n");
}

void mostrarInventario() {
    printf("\n--- Inventario ---\n");
    for (int i = 0; i < MAX_INGREDIENTES; i++) {
        printf("ID: %d, Ingrediente: %s, Stock: %d\n", inventario[i].id, inventario[i].nombre, inventario[i].stock);
    }
}

void mostrarProductosOfertados() {
    printf("\n--- Productos Ofertados ---\n");
    for (int i = 0; i < 5; i++) {
        printf("ID: %d, Producto: %s\n", productosFijos[i].id, productosFijos[i].nombre);
        printf("Tiempo de preparacion: %d minutos\n", productosFijos[i].tiempoPreparacion);
        printf("Ingredientes necesarios:\n");
        for (int j = 0; j < MAX_INGREDIENTES; j++) {
            if (productosFijos[i].ingredientes[j] > 0) {
                printf("- %s: %d\n", inventario[j].nombre, productosFijos[i].ingredientes[j]);
            }
        }
        printf("\n");
    }
}

void modificarStock() {
    int id, nuevoStock;
    printf("Ingrese el ID del ingrediente a modificar: ");
    scanf("%d", &id);

    if (id < 1 || id > MAX_INGREDIENTES) {
        printf("ID invalido.\n");
        return;
    }

    printf("Ingrediente seleccionado: %s\n", inventario[id - 1].nombre);
    printf("Ingrese la nueva cantidad en stock: ");
    scanf("%d", &nuevoStock);

    inventario[id - 1].stock = nuevoStock;
    archivoGuardado = 0;
    printf("Stock actualizado correctamente.\n");
}

void ingresarOrden() {
    int idProducto, cantidad;
    printf("Ingrese el ID del producto (1-5): ");
    scanf("%d", &idProducto);

    if (idProducto < 1 || idProducto > 5) {
        printf("ID de producto invalido.\n");
        return;
    }

    printf("Producto seleccionado: %s\n", productosFijos[idProducto - 1].nombre);
    printf("Ingrese la cantidad deseada: ");
    scanf("%d", &cantidad);

    for (int i = 0; i < MAX_INGREDIENTES; i++) {
        if (productosFijos[idProducto - 1].ingredientes[i] * cantidad > inventario[i].stock) {
            printf("Orden no procede. Ingrediente insuficiente: %s\n", inventario[i].nombre);
            return;
        }
    }

    for (int i = 0; i < MAX_INGREDIENTES; i++) {
        inventario[i].stock -= productosFijos[idProducto - 1].ingredientes[i] * cantidad;
    }

    OrdenTrabajo nuevaOrden = {
        .idOrden = totalOrdenes + 1,
        .idProducto = idProducto,
        .cantidad = cantidad,
        .tiempoTotal = productosFijos[idProducto - 1].tiempoPreparacion * cantidad
    };
    ordenes[totalOrdenes++] = nuevaOrden;

    archivoGuardado = 0;
    printf("Orden ingresada correctamente. Tiempo total de preparacion: %d minutos\n", nuevaOrden.tiempoTotal);
}

void mostrarOrdenes() {
    printf("\n--- Ordenes de Trabajo ---\n");
    for (int i = 0; i < totalOrdenes; i++) {
        printf("ID Orden: %d, Producto: %s, Cantidad: %d, Tiempo Total: %d minutos\n",
            ordenes[i].idOrden,
            productosFijos[ordenes[i].idProducto - 1].nombre,
            ordenes[i].cantidad,
            ordenes[i].tiempoTotal);
    }
}

void buscarOrden() {
    int idOrden;
    printf("Ingrese el ID de la orden a buscar: ");
    scanf("%d", &idOrden);

    for (int i = 0; i < totalOrdenes; i++) {
        if (ordenes[i].idOrden == idOrden) {
            printf("Orden encontrada: Producto: %s, Cantidad: %d, Tiempo Total: %d minutos\n",
                productosFijos[ordenes[i].idProducto - 1].nombre,
                ordenes[i].cantidad,
                ordenes[i].tiempoTotal);
            return;
        }
    }

    printf("Orden no encontrada.\n");
}

void menu() {
    int opcion;

    cargarInventario();
    cargarOrdenes();

    do {
        printf("\n--- Menu ---\n");
        printf("1. Mostrar productos ofertados\n");
        printf("2. Mostrar inventario\n");
        printf("3. Modificar stock\n");
        printf("4. Ingresar orden de trabajo\n");
        printf("5. Mostrar ordenes de trabajo\n");
        printf("6. Buscar orden\n");
        printf("7. Guardar inventario y ordenes\n");
        printf("8. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1: mostrarProductosOfertados(); break;
            case 2: mostrarInventario(); break;
            case 3: modificarStock(); break;
            case 4: ingresarOrden(); break;
            case 5: mostrarOrdenes(); break;
            case 6: buscarOrden(); break;
            case 7: guardarInventario(); guardarOrdenes(); break;
            case 8:
                if (!archivoGuardado) {
                    printf("No ha guardado los cambios. Desea salir sin guardar? (s/n): ");
                    char respuesta;
                    scanf(" %c", &respuesta);
                    if (respuesta == 'n' || respuesta == 'N') {
                        opcion = 0;
                    }
                }
                break;
            default: printf("Opcion invalida.\n");
        }
    } while (opcion != 8);
}

int main() {
    menu();
    return 0;
}
