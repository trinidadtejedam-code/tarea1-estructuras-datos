# Sistema de Gestión de Tickets

Programa desarrollado en C para gestionar tickets de soporte técnico según su prioridad y orden de llegada.

## Compilación

Para compilar el programa desde la carpeta raíz:
```
gcc tdas/*.c tarea1.c -Wno-unused-result -o tarea1
```

## Ejecución

Para ejecutar el programa:
```
./tarea1
```

## Opciones del programa

1. Registrar ticket
2. Asignar prioridad a ticket
3. Mostrar tickets pendientes
4. Procesar siguiente ticket
5. Buscar ticket por ID
6. Salir

Todas las opciones se encuentran funcionando correctamente.

## Ejemplo de uso

Al registrar un ticket se ingresa su ID y la descripción del problema. El ticket se registra inicialmente con prioridad Bajo.

Luego se puede cambiar su prioridad a Alto, Medio o Bajo.

Los tickets pendientes se muestran ordenados por prioridad:

Alto > Medio > Bajo

Al procesar un ticket, se selecciona el de mayor prioridad y se elimina de los tickets pendientes.

También se puede buscar un ticket utilizando su ID.

## TDAs

En la carpeta `tdas` se encuentran implementados distintos TDAs que se pueden utilizar en el programa.