#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <queue>


// Creamos una estructura con el mensaje que se va a enviar a la cola de procesos
struct msg{
    int proceso;
    int time;
    int iteracion;
};

//Creamos la cola principal del programa
std::queue<msg> cola;

// Envia el mensaje de termino del lector de la cola
bool terminarReader = false;

/**
 * Proceso principal que accede a la cola 
 */
void queueReader( )
{

    std::cout << "Inicializando reader " << std::endl;
    // Vamos a estar elementos hasta que se envie el mensaje de termino. 
    while(  !terminarReader )
    {
        // Verificamos si la cola tiene un elemento.
        if( !cola.empty() )
        {
            // Obtenemos el elemento del frente y lo eliminamos de la cola. 
            auto element = cola.front();
            cola.pop();

            // Imprimimos por consola el resultado. 
            std::cout << "Hilo : " << ( element.proceso +1 ) << " en ejecución ( i = " << (element.iteracion + 1) << ") Tiempo ejecucion " <<  element.time << std::endl;            

            //Ponemos un retraso de procesamiento 
            std::this_thread::sleep_for( std::chrono::milliseconds ( 500  ) );
        }
    }
    //Finalizado el reader, terminamos y liberamos la memoria
    std::cout << "Finalizando reader " << std::endl;
}

/**
 * Tarea 
 * @param int id Identificador de la tarea
 * @param int time Tiempo en milisegundos que debe esperar la tarea para ejecutar el siguiente loop
 */
void tarea(int id , int time ) 
{
    // Tomamos el tiempo de inicio de la tarea
    auto inicio = std::chrono::high_resolution_clock::now(); 
    
    // Asumimos que la tarea se ejecutara 3 veces y tomara un tiempo time en cada ciclo.
    for(int i = 0 ; i < 3 ; i++)
    {
        // Calculamos la duracion que lleva la tarea
        auto fin = std::chrono::high_resolution_clock::now(); 
        auto duracion =  std::chrono::duration_cast<std::chrono::milliseconds> ( fin - inicio );

        // Creamos el mensaje para la cola
        struct msg element;

        element.proceso = id;
        element.iteracion = i ;
        element.time = duracion.count(); 
        
        // Agregamos el mensaje a la cola para su procesamiento.
        cola.push( element );

        // Esperamos time milisegundos para que no se termine tan rapido
        std::this_thread::sleep_for( std::chrono::milliseconds ( time  ) );
    }
}

int main() 
{   
    //Numero total de hilos a ejecutar
    const int num_hilos = 3;

    std::cout << "Inicializando reader." << std::endl;
    std::thread queueExecutor( queueReader ); 

    //Vector que mantiene los distintos procesos paralelos
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

    //Finalizamos la cola de sincronizacion
    terminarReader = true;
    queueExecutor.join();
    
    std::cout << "Reader finalizado." << std::endl;

    return 0;
}