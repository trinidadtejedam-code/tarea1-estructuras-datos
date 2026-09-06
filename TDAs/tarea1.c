#include "tdas/list.h"
#include "tdas/extra.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
  int id;
  char descripcion[100];
  int prioridad;
  time_t horaRegistro;
} Ticket;

const char *nombre_prioridad(int prioridad) {
  if (prioridad == 1)
    return "Alto";

  if (prioridad == 2)
    return "Medio";

  return "Bajo";
}

int comparar_tickets(void *dato1, void *dato2) {
  Ticket *ticket1 = (Ticket *)dato1;
  Ticket *ticket2 = (Ticket *)dato2;

  if (ticket1->prioridad < ticket2->prioridad)
    return 1;

  return 0;
}

Ticket *buscar_ticket(List *tickets, int id) {
  Ticket *ticket = list_first(tickets);

  while (ticket != NULL) {
    if (ticket->id == id)
      return ticket;

    ticket = list_next(tickets);
  }

  return NULL;
}

Ticket *extraer_ticket(List *tickets, int id) {
  int cantidad = list_size(tickets);
  Ticket *encontrado = NULL;

  for (int i = 0; i < cantidad; i++) {
    Ticket *ticket = list_popFront(tickets);

    if (ticket->id == id && encontrado == NULL) {
      encontrado = ticket;
    } else {
      list_pushBack(tickets, ticket);
    }
  }

  return encontrado;
}

void liberar_tickets(List *tickets) {
  Ticket *ticket;

  while ((ticket = list_popFront(tickets)) != NULL) {
    free(ticket);
  }

  list_clean(tickets);
}

// Menú principal
void mostrarMenuPrincipal() {
  limpiarPantalla();
  puts("========================================");
  puts("     Sistema de Gestión de Tickets");
  puts("========================================");

  puts("1) Registrar ticket");
  puts("2) Asignar prioridad a ticket");
  puts("3) Mostrar tickets pendientes");
  puts("4) Procesar siguiente ticket");
  puts("5) Buscar ticket por ID");
  puts("6) Salir");
}

void registrar_ticket(List *tickets) {
  printf("Registrar nuevo ticket\n");
  // Aquí implementarías la lógica para registrar un nuevo ticket

  Ticket *nuevo = malloc(sizeof(Ticket));

  if (nuevo == NULL) {
    printf("Error al registrar el ticket.\n");
    return;
  }

  printf("Ingrese el ID del ticket: ");
  scanf("%d", &nuevo->id);

  if (buscar_ticket(tickets, nuevo->id) != NULL) {
    printf("Ya existe un ticket con ese ID.\n");
    free(nuevo);
    return;
  }

  printf("Ingrese la descripcion del problema: ");
  scanf(" %99[^\n]", nuevo->descripcion);

  nuevo->prioridad = 3;
  nuevo->horaRegistro = time(NULL);

  list_sortedInsert(tickets, nuevo, comparar_tickets);

  printf("Ticket registrado correctamente con prioridad Bajo.\n");
}

void asignar_prioridad(List *tickets) {
  int id;
  char prioridad[10];
  int nuevaPrioridad;

  printf("Ingrese el ID del ticket: ");
  scanf("%d", &id);

  if (buscar_ticket(tickets, id) == NULL) {
    printf("No existe un ticket con ese ID.\n");
    return;
  }

  printf("Ingrese la nueva prioridad (Alto, Medio, Bajo): ");
  scanf(" %9s", prioridad);

  if (strcmp(prioridad, "Alto") == 0 ||
      strcmp(prioridad, "alto") == 0) {
    nuevaPrioridad = 1;
  } else if (strcmp(prioridad, "Medio") == 0 ||
             strcmp(prioridad, "medio") == 0) {
    nuevaPrioridad = 2;
  } else if (strcmp(prioridad, "Bajo") == 0 ||
             strcmp(prioridad, "bajo") == 0) {
    nuevaPrioridad = 3;
  } else {
    printf("Prioridad no valida.\n");
    return;
  }

  Ticket *ticket = extraer_ticket(tickets, id);

  ticket->prioridad = nuevaPrioridad;

  list_sortedInsert(tickets, ticket, comparar_tickets);

  printf("Prioridad actualizada correctamente.\n");
}

void mostrar_lista_tickets(List *tickets) {
  // Mostrar tickets pendientes

  Ticket *ticket = list_first(tickets);

  printf("Tickets pendientes: \n");

  // recorrer y mostrar los tickets

  if (ticket == NULL) {
    printf("No hay tickets pendientes.\n");
    return;
  }

  while (ticket != NULL) {
    printf("----------------------------------------\n");
    printf("ID: %d\n", ticket->id);
    printf("Descripcion: %s\n", ticket->descripcion);
    printf("Prioridad: %s\n", nombre_prioridad(ticket->prioridad));
    printf("Hora de registro: %s", ctime(&ticket->horaRegistro));

    ticket = list_next(tickets);
  }

  printf("----------------------------------------\n");
}

void procesar_siguiente_ticket(List *tickets) {
  Ticket *ticket = list_popFront(tickets);

  if (ticket == NULL) {
    printf("No hay tickets pendientes.\n");
    return;
  }

  printf("Procesando siguiente ticket:\n");
  printf("ID: %d\n", ticket->id);
  printf("Descripcion: %s\n", ticket->descripcion);
  printf("Prioridad: %s\n", nombre_prioridad(ticket->prioridad));
  printf("Hora de registro: %s", ctime(&ticket->horaRegistro));

  free(ticket);
}

void buscar_ticket_por_id(List *tickets) {
  int id;

  printf("Ingrese el ID del ticket: ");
  scanf("%d", &id);

  Ticket *ticket = buscar_ticket(tickets, id);

  if (ticket == NULL) {
    printf("No existe un ticket con ese ID.\n");
    return;
  }

  printf("Ticket encontrado:\n");
  printf("ID: %d\n", ticket->id);
  printf("Descripcion: %s\n", ticket->descripcion);
  printf("Prioridad: %s\n", nombre_prioridad(ticket->prioridad));
  printf("Hora de registro: %s", ctime(&ticket->horaRegistro));
}

int main() {
  char opcion;
  List *tickets = list_create(); // lista para gestionar los tickets

  do {
    mostrarMenuPrincipal();
    printf("Ingrese su opción: ");
    scanf(" %c", &opcion); 

    switch (opcion) {
    case '1':
      registrar_ticket(tickets);
      break;
    case '2':
      // Lógica para asignar prioridad
      asignar_prioridad(tickets);
      break;
    case '3':
      mostrar_lista_tickets(tickets);
      break;
    case '4':
      // Lógica para procesar el siguiente ticket
      procesar_siguiente_ticket(tickets);
      break;
    case '5':
      // Lógica para buscar ticket por ID
      buscar_ticket_por_id(tickets);
      break;
    case '6':
      puts("Saliendo del sistema de gestión de tickets...");
      break;
    default:
      puts("Opción no válida. Por favor, intente de nuevo.");
    }

    if (opcion != '6') {
      presioneTeclaParaContinuar();
    }

  } while (opcion != '6');

  // Liberar recursos
  liberar_tickets(tickets);
  free(tickets);

  return 0;
}