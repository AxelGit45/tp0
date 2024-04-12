#include "client.h"
#include "readline/readline.h"


int main(void)
{
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/

	int conexion;
	char* ip;
	char* puerto;
	char* valor;

	t_log* logger;
	t_config* config;

	/* ---------------- LOGGING ---------------- */
	
	log_create("/home/utnso/tp0/tp0.log", "tp0.log", true, LOG_LEVEL_INFO);
	logger = iniciar_logger();

	// Usando el logger creado previamente
	// Escribi: "Hola! Soy un log"
	log_info(logger, "Soy un log");


	/* ---------------- ARCHIVOS DE CONFIGURACION ---------------- */
	
	//---------------------- IMPORTANTE!!!!!!!!!!!!!!!
	config = iniciar_config();
	config = config_create("cliente.config");
	//------------------------
	// Usando el config creado previamente, leemos los valores del config y los 
	// dejamos en las variables 'ip', 'puerto' y 'valor'

	 
	ip = config_get_string_value(config, "IP");
	puerto = config_get_string_value(config,"PUERTO");
	valor = config_get_string_value(config,"CLAVE");
	// Loggeamos el valor de config
	log_info(logger, ip);
	log_info(logger, puerto);
	log_info(logger, valor);


	/* ---------------- LEER DE CONSOLA ---------------- */

	leer_consola(logger);

	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	// ADVERTENCIA: Antes de continuar, tenemos que asegurarnos que el servidor esté corriendo para poder conectarnos a él

	// Creamos una conexión hacia el servidor
	conexion = crear_conexion(ip, puerto);

	// Enviamos al servidor el valor de CLAVE como mensaje
	enviar_mensaje(valor, conexion);
	// Armamos y enviamos el paquete
	paquete(conexion);

	terminar_programa(conexion, logger, config);

	/*---------------------------------------------------PARTE 5-------------------------------------------------------------*/
	// Proximamente

	
}

t_log* iniciar_logger(void)
{
	t_log* nuevo_logger;

	return nuevo_logger;
}

t_config* iniciar_config(void)
{
	t_config* nuevo_config;

	return nuevo_config;
}

void leer_consola(t_log* logger)
{
	char* leido;

	// La primera te la dejo de yapa
	leido = readline("> ");

	// El resto, las vamos leyendo y logueando hasta recibir un string vacío
	
	while (1)
	{
		leido = readline("> ");
		if (!leido) {
            break;
        }
		printf("%s\n", leido);
	}
	
	free(leido);
	// ¡No te olvides de liberar las lineas antes de regresar!

}

void paquete(int conexion)
{
	// Ahora toca lo divertido!
	char* leido;
	t_paquete* paquete = crear_paquete();
	
	// Leemos y esta vez agregamos las lineas al paquete
	while (1)
	{
		leido = readline("> ");
		if (!leido) {
            break;
        }
		agregar_a_paquete(paquete,leido,strlen(leido)+1);
	}
	
	free(leido);
	//agregar_a_paquete(paquete,leido,strlen(leido)+1);
	enviar_paquete(paquete,conexion);
	
	// ¡No te olvides de liberar las líneas y el paquete antes de regresar!
	eliminar_paquete(paquete);
	free(leido);
}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	/* Y por ultimo, hay que liberar lo que utilizamos (conexion, log y config) 
	  con las funciones de las commons y del TP mencionadas en el enunciado */

	config_destroy(config);
	log_destroy(logger);
	liberar_conexion(conexion);
	

}
