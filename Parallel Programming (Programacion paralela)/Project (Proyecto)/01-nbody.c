/*
* Universidad Central de Venezuela
* Facultad de Ciencias
* Licenciatura en Ciencias de la Computacion
* Fundamentos de la Programacion Paralela
* Tarea 2
* Alumno:
*   Anthony Alvarado
* C.I:
*   27.321.522
*/
//---------------------------------------------------------------LIBRERIAS---------------------------------------------
#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "timer.h"
#include "files2.h"
#include <mpi.h> //para hacer uso de mpi.
#include <omp.h> // para trabajar openmp.
//-------------------------------------------------------------------------------VARIABLES GLOBALES-------------------------------------------
#define SOFTENING 1e-9f

//--------------------------------------------------------------------------------ESTRUCTURAS---------------------------------------------------------------------
typedef struct { float x, y, z, vx, vy, vz; } Body;


//--------------------------------------------------------------------FUNCIONES.-----------------------------------------------------------------------------


void bodyForce(Body* p, float dt, int n, int ind_init,int ind_final) {
	int i =0;
#pragma omp parallel for
    for (i = ind_init; i < ind_final; ++i) {
        // Obtener el número de hilo actual
        //int thread_id = omp_get_thread_num();
        // Obtener el número total de hilos
        //int num_threads = omp_get_num_threads();

        // Imprimir el número de hilo y el número total de hilos.
        //printf("Hilo %d de %d, i = %d\n", omp_get_thread_num(), omp_get_num_threads(), i);
        float Fx = 0.0f; float Fy = 0.0f; float Fz = 0.0f;
        
        for (int j = 0; j < n; j++) {
            float dx = p[j].x - p[i].x;
            float dy = p[j].y - p[i].y;
            float dz = p[j].z - p[i].z;
            float distSqr = dx * dx + dy * dy + dz * dz + SOFTENING;
            float invDist = 1.0f / sqrtf(distSqr);
            float invDist3 = invDist * invDist * invDist;

            Fx += dx * invDist3; 
            Fy += dy * invDist3; 
            Fz += dz * invDist3;
        }

        p[i].vx += dt * Fx;
        p[i].vy += dt * Fy;
        p[i].vz += dt * Fz;
    }
};
void integratePosition(Body*p,float dt,int n,int ind_ini,int ind_final)
{
    int i = 0;
#pragma omp parallel for
    for (i = ind_ini; i < ind_final; i++) { // integrate position
        p[i].x += p[i].vx * dt;
        p[i].y += p[i].vy * dt;
        p[i].z += p[i].vz * dt;
    }
};

//------------------------------------------------------------------------------------- ACCION PRINCIPAL---------------------------------------------------------------------------


int main(const int argc, const char** argv) {
    //Variables.
    int ind_ini = 0, ind_final = 0;
    int i = 0;
    int tag = 99;
   int MyId, Num;
   const char* initialized_values;
   const char* solution_values;
   //Inicializar mpi.
   MPI_Init(&argc, &argv);
   MPI_Status status;
   MPI_Comm_rank(MPI_COMM_WORLD, &MyId); // id del proceso.
   MPI_Comm_size(MPI_COMM_WORLD, &Num); // numero de procesos.
  // The assessment will test against both 2<11 and 2<15.
  // Feel free to pass the command line argument 15 when you generate ./nbody report files
  int nBodies = 2<<11;

  if (MyId == 0) 
  {
      /*
      * Si soy el maestro realizo la verificacion del tamaño
      * para asignar el nombre de los archivos.
      */
      if (argc > 1) nBodies = 2 << atoi(argv[1]);

      // The assessment will pass hidden initialized values to check for correctness.
      // You should not make changes to these files, or else the assessment will not work.
     // const char* initialized_values;
     // const char* solution_values;

      if (nBodies == 2 << 11) {
          initialized_values = "files/initialized_4096";
          solution_values = "files/solution_4096.txt";
      }
      else { // nBodies == 2<<15
          initialized_values = "files/initialized_65536";
          solution_values = "files/solution_65536.txt";
      }


      if (argc > 2) initialized_values = argv[2];
      if (argc > 3) solution_values = argv[3];

  }
  /*
  * El maestro envia el tamaño de nBodies en dado caso que se ha modificado
  * con los parametros de entrada.
  */
  MPI_Bcast(&nBodies,1,MPI_INT,0, MPI_COMM_WORLD);
  
  // Todos crean los nBodies va a crear los nBodies.

  const float dt = 0.01f; // Time step
  const int nIters = 10;  // Simulation iterations

  int bytes = nBodies * sizeof(Body);
  float *buf;

  buf = (float *)malloc(bytes);

  Body *p = (Body*)buf;
  float* recv_buf = (float*)malloc(bytes);
  Body* recv_p = (Body*)recv_buf;
  
   //El maestro realiza la lectura.
  if (MyId == 0)
  {
      read_values_from_file(initialized_values, buf, bytes);
  }
  /*
  * Creacion de MPI_Type_create_struct
  */
  MPI_Datatype mpi_nBodies;
  int longitud[6] = { 1,1,1,1,1,1};
  MPI_Datatype tipo[6] = {MPI_FLOAT, MPI_FLOAT ,MPI_FLOAT ,MPI_FLOAT ,MPI_FLOAT ,MPI_FLOAT };
  MPI_Aint offsets[6] ;
  offsets[0] = offsetof(Body, x);
  offsets[1] = offsetof(Body, y);
  offsets[2] = offsetof(Body, z);
  offsets[3] = offsetof(Body, vx);
  offsets[4] = offsetof(Body, vy);
  offsets[5] = offsetof(Body, vz);

  MPI_Type_create_struct(6,longitud,offsets, tipo, &mpi_nBodies);
  MPI_Type_commit(&mpi_nBodies);
 

  /*
  * Bcast de los datos a los hijos.
  */
  MPI_Bcast(p, nBodies, mpi_nBodies, 0, MPI_COMM_WORLD);


  int* sendcounts = NULL;//Creacion de arreglo donde se guardan las posiciones para el MPI_Gatherv.
  int* displs = NULL;
  /*
   * Envio de los indices con los cuales va a trabajar cada proceso.
   */

  if (MyId == 0)
  {
      sendcounts = (int*)malloc(Num * sizeof(int));
      displs = (int*)malloc(Num * sizeof(int));
      int ind_ini_temp = 0, ind_final_temp = 0;
      ind_ini = 0;
      ind_final = nBodies / Num;
      sendcounts[0] = ind_final - ind_ini;
      displs[0] = 0;
      ind_ini_temp = ind_final;
      for (i = 1; i < Num; i++)
      {
          ind_ini_temp = ind_ini_temp + 1;
          MPI_Send(&ind_ini_temp,1,MPI_INT,i,0, MPI_COMM_WORLD);// envio del indice inicial donde van a trabajar cada hijo.
          ind_final_temp = ind_ini_temp + (nBodies / Num);
          if (ind_final_temp > nBodies) 
          {
              ind_final_temp = nBodies;
          }
          MPI_Send(&ind_final_temp, 1, MPI_INT, i, 0, MPI_COMM_WORLD); // envio del indice final hasta donde trabaja cada hijo.
          sendcounts[i] = ind_final_temp - ind_ini_temp;
          displs[i] = ind_ini_temp;
          ind_ini_temp = ind_final_temp;
      }


  }
  else
  {
      /*
      *     Recibe los hijos cada indice, tanto inferior como superior.
      */
      MPI_Recv(&ind_ini, 1, MPI_INT, 0, 0,MPI_COMM_WORLD, &status);
      MPI_Recv(&ind_final, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
      
  }
  /*
  *...................................... EJECUCION................................
  */
  double totalTime = 0.0;
  

  /*
   * Inicio del ciclo de iteraciones
   */

  for (int iter = 0; iter < nIters; iter++) {
      //Inicio del tiempo por el maestro.
      if (MyId == 0)
      {
          StartTimer();
      }
      //printf("Soy el proceso %d de %d\n", MyId,Num);
      bodyForce(p, dt, nBodies, ind_ini,ind_final); // llamada a la funcion Bodyforce
      /*
      * He decidido sacar la Integracio de posicion a una funcion para mayor legibilidad.
      * Aqui tambien cada nodo va a trabajar con el subconjunto que le toco.
      */
      integratePosition(p,dt,nBodies,ind_ini,ind_final);
    
      MPI_Barrier(MPI_COMM_WORLD); // Se espera a que todos terminen sus resultados.


      /*
      * Recoleccion de datos.
      */
      MPI_Gatherv(&p[ind_ini], ind_final - ind_ini, mpi_nBodies, recv_p, sendcounts, displs, mpi_nBodies, 0, MPI_COMM_WORLD);
      /*
      * Movimiento de datos de el buffer recv_p a p por parte del maestro.
      */
      if (MyId == 0)
      {
		  
          const double tElapsed = GetTimer() / 1000.0;
          totalTime += tElapsed;
          memcpy(p, recv_p, nBodies * sizeof(Body)); // Realiza la copia		  de manera mas rapida.
	  }
      /*
      * Vuelve a enviar los datos actualizados a esclavos para la siguiente iteracion en caso de que exista.
      */
      MPI_Bcast(p, nBodies, mpi_nBodies, 0, MPI_COMM_WORLD);

  }
  /*
  * Fin del ciclo de iteraciones
  */

  /*
  * Realiza la escritura en los archivos correspondientes y hace el calculo del tiempo
  */
  if (MyId == 0)
  {
      double avgTime = totalTime / (double)(nIters);
      float billionsOfOpsPerSecond = 1e-9 * nBodies * nBodies / avgTime;
      write_values_to_file(solution_values, buf, bytes);
      printf("%0.3f Billion Interactions / second\n", billionsOfOpsPerSecond);
  }
  MPI_Finalize();
}
