#include <iostream>
#include <thread>
#include <vector>
#include <mutex>


// Semaforo que va a poermitir acceder a un recurso a la zona critica
std::mutex mtx; 


/**
 * Tarea 
 * @param int id Identificador de la tarea
 * @param int time Tiempo en milisegundos que debe esperar la tarea para ejecutar el siguiente loop
 */
void tarea(int id , int time ) 
{
    // Tomamos el tiempo de inicio de la tarea
    auto inicio = std::chrono::high_resolution_clock::now(); 
    
    // Debe ejecutarse solamente 3 veces pero debe bloquear la seccion critica
    int i = 0; 
    // Asumimos que la tarea se ejecutara 4 veces y tomara un tiempo time en cada ciclo.
    while( i < 3)
    {
        // Calculamos la duracion que lleva la tarea
        auto fin = std::chrono::high_resolution_clock::now(); 
        auto duracion =  std::chrono::duration_cast<std::chrono::milliseconds> ( fin - inicio );

        //Tomamos el semaforo 
        if ( mtx.try_lock()) 
        {
            // Imprimimos por consola el resultado. 
            std::cout << "Hilo : " << (id+1) << " en ejecución ( i = " << (i + 1) << ") Tiempo ejecucion " <<  duracion.count()  << std::endl;
            
            // Esperamos time milisegundos para que no se termine tan rapido
            std::this_thread::sleep_for( std::chrono::milliseconds ( time  ) );
            i++;
            mtx.unlock(); // Liberar el mutex
        }
        else 
        {
            std::cout << "Hilo : " << (id+1) << " en espera por semaforo ( i = " << (i + 1) << ") Tiempo ejecucion " <<  duracion.count()  << std::endl;
            // Esperamos 1200 milisegundos para que no se termine tan rapido
            std::this_thread::sleep_for( std::chrono::milliseconds ( 1200  ) );
        }
    }
}

int main() 
{   
    //Numero total de hilos
    const int num_hilos = 3;

    //Vector que mantiene 
    std::vector<std::thread> hilos;

    std::cout << "Iniciando hilos. " << std::endl;
    for (int i = 0; i < num_hilos; ++i) 
    {
        //Creamos la tarea y la agregamos a vector.
        hilos.push_back( std::thread( tarea, i , ( (i+1) * 2000 / 3  )) );

        // Pequeno sleep para que la salida por consola no se vea mezclada
        std::this_thread::sleep_for( std::chrono::milliseconds ( 50   ) );
    }

    // Recorre los threads que tengo y va esperando a que todos terminen. s
    for (auto& hilo : hilos) {
        hilo.join();
    }

    // Hilos finalizados. 
    std::cout << "Todos los hilos han terminado." << std::endl;

    return 0;
}