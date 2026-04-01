#include "client.h"
#include <readline/readline.h>

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

	logger = iniciar_logger();

	// Usando el logger creado previamente
	// Escribi: "Hola! Soy un log"
	log_info(logger,"Hola! Soy un log");
	

	/* ---------------- ARCHIVOS DE CONFIGURACION ---------------- */

	config = iniciar_config();

	//char *clave = config_get_string_value(config,"CLAVE");
	//config_save_in_file(,"");
	//log_info(logger, clave);
	
	valor = config_get_string_value(config,"CLAVE");
	log_info(logger, "El valor de la clave es: %s", valor);

	ip = config_get_string_value(config,"IP");
	log_info(logger, "El valor de la IP es :%s", ip);
	
	puerto= config_get_string_value(config,"PUERTO");
	log_info(logger, "El valor del PUERTO es:%s",puerto);
	// Usando el config creado previamente, leemos los valores del config y los 
	// dejamos en las variables 'ip', 'puerto' y 'valor'

	// Loggeamos el valor de config


	/* ---------------- LEER DE CONSOLA ---------------- */

	leer_consola(logger);

	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	// ADVERTENCIA: Antes de continuar, tenemos que asegurarnos que el servidor esté corriendo para poder conectarnos a él

	// Creamos una conexión hacia el servidor
	conexion = crear_conexion(ip, puerto);

	// Enviamos al servidor el valor de CLAVE como mensaje

	// Armamos y enviamos el paquete
	paquete(conexion);

	terminar_programa(conexion, logger, config);

	/*---------------------------------------------------PARTE 5-------------------------------------------------------------*/
	// Proximamente
}

t_log* iniciar_logger(void)
{
	t_log* nuevo_logger = log_create("/home/utnso/tp0/tp0.log","Primer Log de Axel" ,true, LOG_LEVEL_INFO );
	//log_create("",)--- esto lo hice yo
	return nuevo_logger;
}

t_config* iniciar_config(void)
{
	
	t_config* nuevo_config = config_create("cliente.config");
	
	if (nuevo_config == NULL)
	{
		abort();
	}

	//char *clave = config_get_string_value(nuevo_config,"Hola soy la clave");
	

	return nuevo_config;
}

void leer_consola(t_log* logger)
{
	char* leido;

	// La primera te la dejo de yapa
	leido = readline("> ");

	
	// El resto, las vamos leyendo y logueando hasta recibir un string vacío

	log_info(logger, leido);

	while (strcmp(leido,"")!= 0)
	{
		log_info(logger, leido);

		leido = readline("> ");
		//log_info(logger, leido);
		
		//abort();
	}
	free(leido);
	abort();
	// ¡No te olvides de liberar las lineas antes de regresar!
	//free(leido);
}

void paquete(int conexion)
{
	// Ahora toca lo divertido!
	char* leido;
	t_paquete* paquete;

	// Leemos y esta vez agregamos las lineas al paquete


	// ¡No te olvides de liberar las líneas y el paquete antes de regresar!
	
}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	/* Y por ultimo, hay que liberar lo que utilizamos (conexion, log y config) 
	  con las funciones de las commons y del TP mencionadas en el enunciado */
	log_destroy(logger);
	
	config_destroy(config);
}
