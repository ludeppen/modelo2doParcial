#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

typedef struct {
 int idPelicula;
 char nombre[50];
 int anio;
 char genero[10];
 char actores[3][50];
 int calificacion;
 int estado;
} stPelicula;
///---------------------Protitipados---------------------///
int pasarArchiAarray(char archivo[],stPelicula array[], int dim);
void mostrarArray(stPelicula array[], int dim);

///---------------------Protitipados---------------------///

int main()
{
    char rutaDeArchivo[] = "datosPeliculas.bin";
    stPelicula *array;
    int totalRegistros = cantDeRegistros(rutaDeArchivo);
    array = (stPelicula*)malloc(sizeof(stPelicula) *totalRegistros);
    char control = 's';
    while(control == 's')
    {
        int ejercicio;
        system("cls");
        printf("1. Cargar peliculas.\n");
        printf("2. Ver peliculas.\n");
        printf("3. Dar de baja una pelicula.\n");
        printf("4. Modificar archivo.\n");
        printf("5. Ver peliculas por genero.\n");
        printf("6. Ver arreglo.\n");
        printf("7. Ver por titulo(ordenamiento por seleccion.\n");
        printf("8. ver por genero(ordenamiento por inserccion)\n");
        printf("Ingrese un numero:\t");
        scanf("%d",&ejercicio);
        switch(ejercicio)
        {
        case 1:
             system("cls");
             cargarArchivoPeliculas(rutaDeArchivo);
             break;
        case 2:
             system("cls");
             mostrarArchivoPeliculas(rutaDeArchivo);
             break;
        case 3:
             system("cls");
             char pelicula[50];
             printf("Ingrese el nombre de la pelicula a dar de baja:\n");
             fflush(stdin);
             gets(pelicula);
             darDeBajaPelicula(rutaDeArchivo,pelicula);
             break;
        case 4:
             system("cls");
             MostrarIdYpelicula(rutaDeArchivo);
             int id;
             printf("Ingrese el id de la pelicula a modificar:\t");
             scanf("%d",&id);
             modificarPelicula(rutaDeArchivo,id);
             break;
        case 5:
             system("cls");
             char genero[15];
             printf("Ingrese el genero:\t");
             fflush(stdin);
             gets(genero);
             verPorGenero(rutaDeArchivo,genero);
             break;
        case 6:
             system("cls");
             printf("%d",totalRegistros);
             totalRegistros =  pasarArchiAarray(rutaDeArchivo,array,totalRegistros);
             mostrarArray(array,totalRegistros);
             break;
        case 7:
             system("cls");
             ordenarPorSeleccion(array,totalRegistros);
             mostrarArray(array,totalRegistros);
        case 8:
             system("cls");
             ordenarPorInserccion(array,totalRegistros);
             mostrarArray(array,totalRegistros);
             break;
        }
        printf("\nDesea ver otro ejercicio? s / n:\t");
        fflush(stdin);
        scanf("%c",&control);
    }
    return 0;
}
///---------------------funciones---------------------///

int ultimoID(char archivo[])
{
    stPelicula p;
    int id =  -1;
    FILE*buffer = fopen(archivo,"rb");
    if(buffer)
    {
        while(fread(&p,sizeof(stPelicula),1,buffer) > 0)
        {
            if(p.idPelicula > id)
            {
              id = p.idPelicula;
            }
        }
        fclose(buffer);
    }
return id;
}
int cargarUnaPelicula(char archivo[],stPelicula *p)
{
    printf("Ingrese el nombre de la pelicula:\n");
    fflush(stdin);
    gets(p->nombre);

    int res = verificarNombre(archivo,p->nombre);
    if(res == 0)
    {
      printf("Ingrese el anio:\t");
      scanf("%d",&p->anio);

      printf("Ingrese la calificacion:\t");
      scanf("%d",&p->calificacion);

      printf("Ingrese el genero:\t");
      fflush(stdin);
      gets(p->genero);

      for(int f = 0; f < 3; f++)
      {
        printf("Ingrese el nombre del actor %d:\t",f + 1);
        fflush(stdin);
        gets(p->actores[f]);
      }
      p->estado = 1;
    }
    else
    {
      printf("Error, nombre repetido.\n");
      return 0;
    }
return 1;
}

void cargarArchivoPeliculas(char archivo[])
{
    stPelicula p;
    FILE*buffer = fopen(archivo,"ab");
    if(buffer)
    {
     int ultId = ultimoID(archivo);
     char control = 's';
     while(control == 's')
     {
        int res = cargarUnaPelicula(archivo,&p);
        if(res != 0)
        {
          ultId++;
          p.idPelicula = ultId;
          fwrite(&p,sizeof(stPelicula),1,buffer);
        }
        printf("\nDesea cargar otra pelicula? s / n:\t");
        fflush(stdin);
        scanf("%c",&control);
     }
        fclose(buffer);
    }
    else
    {
        perror("Error.\n");
    }
}

int verificarNombre(char archivo[], char nombrePelicula[])
{
    stPelicula p;
    FILE* buffer = fopen(archivo,"rb");
    if(buffer)
    {
        while(fread(&p,sizeof(stPelicula),1,buffer) > 0)
        {
            if(strcmp(p.nombre,nombrePelicula) == 0)
            {
                return 1;
            }
        }
        fclose(buffer);
    }
    else
    {
        perror("Error.\n");
    }
return 0;
}
void mostrarUnaPelicula(stPelicula p)
{
    printf("ID: %d\n",p.idPelicula + 1);
    printf("Nombre: %s\n",p.nombre);
    printf("Anio:%d\n",p.anio);
    printf("Genero: %s\n",p.genero);
    printf("Calificacion: %d\n",p.calificacion);
    for(int f =  0; f < 3; f++)
    {
        printf("Actor %d: %s\n",f + 1,p.actores[f]);
    }
    printf("Estado: %d\n",p.estado);
    puts("---------------------------------");

}
void mostrarArchivoPeliculas(char archivo[])
{
    stPelicula p;
    FILE*buffer = fopen(archivo,"rb");
    if(buffer)
    {
        while(fread(&p,sizeof(stPelicula),1,buffer) > 0)
        {
            mostrarUnaPelicula(p);
        }
        fclose(buffer);
    }
    else
    {
        perror("Error.\n");
    }
}

void darDeBajaPelicula(char archivo[],char pelicula[])
{
    stPelicula p;
    int encontrado = 0;
    FILE*buffer = fopen(archivo,"r + b");
    if(buffer)
    {
        while(fread(&p,sizeof(stPelicula),1,buffer) > 0)
        {
            if(strcmpi(p.nombre,pelicula) == 0 && p.estado == 1)
            {
                p.estado = 0;
                encontrado = 1;

                fseek(buffer,-sizeof(stPelicula), SEEK_CUR);
                fwrite(&p,sizeof(stPelicula),1,buffer);
                printf("Pelicula eliminada con exito.\n");
                break;
            }
        }
        if(encontrado == 0)
        {
            printf("Pelicula no encontrada o ya eliminada.\n");
        }
        fclose(buffer);
    }
    else
    {
        perror("Error.\n");
    }
}

void modificarPelicula(char archivo[], int id)
{
    stPelicula p;
    FILE* buffer = fopen(archivo,"r + b");
    if(buffer)
    {
      fseek(buffer,sizeof(stPelicula) * id ,SEEK_SET);
      fread(&p,sizeof(stPelicula),1,buffer);
        char control = 's';
        while(control == 's')
        {
            int campoAmodificar;
            printf("1. Nombre.\n");
            printf("2. anio.\n");
            printf("3. genero.\n");
            printf("4. actores.\n");
            printf("5. calificacion.\n");
            fflush(stdin);
            scanf("%d",&campoAmodificar);
            switch(campoAmodificar)
            {
            case 1:
                 system("cls");
                 printf("Ingrese el nuevo nombre:\n");
                 fflush(stdin);
                 gets(p.nombre);
                 break;
            case 2:
                 system("cls");
                 printf("Ingrese el nuevo anio:\t");
                 scanf("%d",&p.anio);
                 break;
            case 3:
                 system("cls");
                 printf("Ingrese el nuevo genero:\n");
                 fflush(stdin);
                 gets(p.genero);
                 break;
            case 4:
                 system("cls");
                 for(int f = 0; f < 3; f++)
                 {
                    printf("Ingrese el nuevo nombre del actor %d:\t",f + 1);
                    fflush(stdin);
                    gets(p.actores[f]);
                 }
                 break;
            case 5:
                 system("cls");
                 printf("Ingrese el nuevo anio:\t");
                 scanf("%d",&p.anio);
                 break;
            }

        printf("\nDesea modificar otro campo? s / n:\t");
        fflush(stdin);
        scanf("%c",&control);
        }

        fseek(buffer,-sizeof(stPelicula),SEEK_CUR);
        fwrite(&p,sizeof(stPelicula),1,buffer);
        fclose(buffer);
    }
    else
    {
        perror("Error.\n");
    }
}

void MostrarIdYpelicula(char archivo[])
{
    stPelicula p;
    FILE* buffer = fopen(archivo,"rb");
    if(buffer)
    {
         while(fread(&p,sizeof(stPelicula),1,buffer) > 0)
         {
             if(p.estado == 1)
             {
               printf("ID: %d\n",p.idPelicula);
               printf("Nombre: %s\n",p.nombre);
               puts("---------------------");
             }
         }
        fclose(buffer);
    }
    else
    {
        perror("Error.\n");
    }
}

void verPorGenero(char archivo[], char genero[])
{
    stPelicula p;
    FILE*buffer = fopen(archivo,"rb");
    if(buffer)
    {
      fseek(buffer,0,SEEK_SET);
      system("cls");
      while(fread(&p,sizeof(stPelicula),1,buffer) > 0)
      {
        if(p.estado == 1)
        {
            if(strcmp(p.genero,genero) == 0)
            {
                mostrarUnaPelicula(p);
            }
        }
      }
        fclose(buffer);
    }
    else
    {
        perror("Error.\n");
    }
}

int pasarArchiAarray(char archivo[],stPelicula array[], int dim)
{
  stPelicula p;
  int i = 0;
  FILE*buffer = fopen(archivo,"rb");
  if(buffer)
  {
      while(fread(&p,sizeof(stPelicula),1,buffer) > 0)
      {
        if(p.estado == 1)
        {
          array[i] = p;
          i++;
        }
      }
      fclose(buffer);
  }
  else
  {
      perror("Erro.\n");
  }
return i;
}

void mostrarArray(stPelicula array[], int dim)
{
  for(int i = 0; i < dim; i++)
  {
    printf("ID: %d\n",array[i].idPelicula);
    printf("Nombre: %s\n",array[i].nombre);
    printf("Anio:%d\n",array[i].anio);
    printf("Genero: %s\n",array[i].genero);
    printf("Calificacion: %d\n",array[i].calificacion);
    for(int f =  0; f < 3; f++)
    {
        printf("Actor %d: %s\n",f + 1,array[i].actores[f]);
    }
    printf("Estado: %d\n",array[i].estado);
    puts("---------------------------------");
  }

}

int cantDeRegistros(char archivo[])
{
    stPelicula p;
    int totalRegistros = 0 ;
    FILE *buffer = fopen(archivo,"rb");
    if(buffer)
    {
        fseek(buffer,0,SEEK_END);
        int cant = ftell(buffer);
        totalRegistros = cant / sizeof(stPelicula);
        fclose(buffer);
    }
    else
    {
        perror("Error.\n");
    }
return totalRegistros;
}


void ordenarPorSeleccion(stPelicula array[], int dim)
{
    stPelicula temp;
    int i = 0, j = 0, subMenor;
    for(i = 0; i < dim - 1; i++)
    {
        subMenor = i;
        for(j = i + 1; j < dim ; j++)
        {
          if(strcmpi(array[j].nombre, array[subMenor].nombre) < 0)
            subMenor = j;
        }
    temp = array[subMenor];
    array[subMenor] = array[i];
    array[i] = temp;
    }
}

void ordenarPorInserccion(stPelicula array[],int dim)
{
    int i = 0, j = 0;
    stPelicula temp;
    for(i = 0; i < dim; i++)
    {
        temp = array[i];
        j = i - 1;

        while(j >= 0 && (strcmp(array[j].genero,temp.genero) > 0))
        {
            array[j + 1] = array[j];
            j--;
        }
        array[j + 1] = temp;
    }
}
