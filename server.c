///*
// * server.cpp
// *
// *  Created on: Nov 11, 2013
// *      Author: rick
// */
//
//#include <stdio.h>
//#include <string.h>
//#include <openssl/bio.h>
//#include <openssl/ssl.h>
//#include "thread.h"
//#include <openssl/x509v3.h>
//#include <openssl/x509.h>
//#include <openssl/err.h>
//
//#define CAFILE "server.crt"
//#define CADIR NULL
//#define CERTFILE "server.crt"
//#define KEYFILE "server.key"
//
//#define CIPHER_LIST "AES:DH:RSA:SHA:!ADH:!LOW:!EXP:!MD5:@STRENGTH"
//
///**
// * tamanho dos pacotes de dados transportados do cliente para o servidor e vice-versa
// */
//#define SSL_LENGTH_DATA 2048
//
///**
// * tamanho do comando aceita na linha de comando do cliente
// */
//#define COMMAND_SIZE 150
//
//int verify_callback(int ok, X509_STORE_CTX *store){
//	return ok;
//}
//
//SSL_CTX* setup_server_ctx(void){
//	SSL_CTX *ctx;
//	ctx = SSL_CTX_new(SSLv23_method());
//	if (SSL_CTX_load_verify_locations(ctx, CAFILE, CADIR) != 1){
//		printf("Error loading CA file and/or directory");
//		return 0;
//	}
//	if (SSL_CTX_set_default_verify_paths(ctx) != 1){
//		printf("Error loading default CA file and/or directory");
//		return 0;
//	}
//	if (SSL_CTX_use_certificate_chain_file(ctx, CERTFILE) != 1){
//		printf("Error loading certificate from file");
//		return 0;
//	}
//	if (SSL_CTX_use_PrivateKey_file(ctx, KEYFILE, SSL_FILETYPE_PEM) != 1){
//		printf("Error loading private key from file");
//		return 0;
//	}
//	SSL_CTX_set_verify(ctx, SSL_VERIFY_NONE, verify_callback);
//	SSL_CTX_set_verify_depth(ctx, 4);
//	SSL_CTX_set_options(ctx, SSL_OP_ALL | SSL_OP_NO_SSLv2);
//	if (SSL_CTX_set_cipher_list(ctx, CIPHER_LIST) != 1){
//		printf("Error setting cipher list (no valid ciphers)");
//		return 0;
//	}
//	SSL_CTX_set_timeout(ctx,30);
//	return ctx;
//}
//
//char * ssl_read_data(SSL *ssl, int *bytes_readed){
//	int nread, i = 0, ntemp = 0, repeat = 0;
//	char *temp;
//	char *buf = NULL, *buf_aux = NULL;
//	*bytes_readed = 0;
//	buf = (char *)calloc(SSL_LENGTH_DATA+1, sizeof(void));
//	do{
//		if (i){
//			buf_aux = buf;
//			buf = NULL;
//			buf = (char *)calloc((SSL_LENGTH_DATA*(i+1))+1, sizeof(void));
//			strncpy((char *)buf, (char *)buf_aux, SSL_LENGTH_DATA*i);
//			free(buf_aux);
//		}
//		nread = SSL_read(ssl, buf + (i * SSL_LENGTH_DATA), SSL_LENGTH_DATA);
//		i++;
//		if (nread <= 0){
//				goto err0;
//		}
//		*bytes_readed = (*bytes_readed + nread);
//		if (nread == SSL_LENGTH_DATA){
//			temp = (char *)calloc(SSL_LENGTH_DATA+1, sizeof(char));
//			ntemp = SSL_read(ssl, temp, SSL_LENGTH_DATA);
//			if (nread <= 0){
//				free(temp);
//				goto err0;
//			}
//			if (!(strcmp(temp, "repeat"))){
//				repeat = 1;
//			}else{
//				repeat = 0;
//			}
//			free(temp);
//		}else{
//			repeat = 0;
//		}
//	}while (repeat == 1);
//	return buf;
//err0:
//	printf("Error reading data from SSL connection");
//	free(buf);
//	return NULL;
//}
//
//char *connection_read_data(SSL *conn, int *length){
//	char *data = NULL;
//
//	data = ssl_read_data(conn, length);
//
//	return data;
//}
//
//int do_server_loop(SSL *conn){
//	char *enter_buffer = NULL, *buffer_parts[COMMAND_SIZE];
//	int nread, enter_number;
//
//
//
//	for (;;){
//		if (!(enter_buffer = connection_read_data(conn, &nread))){
//			break;
//		}
//		if (!strcmp(enter_buffer, "quit") || !strcmp(enter_buffer, "exit")){
//			free(enter_buffer);
//			break;
//		}
//		//log_message(CLIENT_FUNC_MSG, enter_buffer);
//		//enter_number = umount_string_by_space(enter_buffer, buffer_parts);
//		//management_enter_datas(ctx, buffer_parts, enter_number);
//
//		free(enter_buffer);
//		while (enter_number > 0){
//			enter_number--;
//			free(buffer_parts[enter_number]);
//		}
//	}
//
//	return (SSL_get_shutdown(conn) & SSL_RECEIVED_SHUTDOWN) ? 1 : 0;
//
//}
//
//void server_thread(void *arg){
//
//	SSL *conn;
//
//	conn = (SSL*)arg;
//
//	pthread_detach(pthread_self());
//	if (SSL_accept(conn) <= 0){
//		printf("Error accepting SSL connection. Probably, connection cancelled by user");
//	}
//	else {
//		printf("SSL Connection opened ...");
//		//log_message(HSM_CONNECTIONS_MSG, "SSL connection opened");
//
//		if (do_server_loop(conn))
//			SSL_shutdown(conn);
//		else
//			SSL_clear(conn);
//		printf("SSL Connection closed.");
//		//log_message(HSM_CONNECTIONS_MSG, "SSL connection closed");
//		}
//		SSL_free(conn);
//		ERR_remove_state(0);
//		pthread_exit(NULL);
//
//}
//
//int main(int argc, char **argv){
//
//	BIO *acc, *client;
//	SSL *ssl;
//	SSL_CTX *ctx;
//	THREAD_TYPE tid, tengineid;
//
//	OpenSSL_add_all_algorithms();
//	OpenSSL_add_ssl_algorithms();
//
//	if (!argc){
//		printf("No specified port\n");
//	}
//
//
//	if ((atoi(argv[1]) < 1025) || (atoi(argv[1]) > 30000) ){ /* Flawfinder: ignore */ //Controlado através do tamanho da string
//		printf("Invalid port (range 1025:30000)\n");
//	}
//
//	ctx = setup_server_ctx();
//
//	if (!ctx){
//		return (-1);
//	}
//
//	acc = BIO_new_accept(argv[0]);
//	if (!acc)
//		printf("Error creating server socket");
//	if (BIO_do_accept(acc) <= 0)
//		printf("Error binding server socket");
//
//	for (;;) {
//		printf("Waiting Connection ... \n");
//		if (BIO_do_accept(acc) <= 0) {
//			printf("Error accepting connection");
//		} else {
//			client = BIO_pop(acc);
//			if (!(ssl = SSL_new(ctx))) {
//				printf("Error creating SSL context");
//			} else {
//				SSL_set_bio(ssl, client, client);
//				THREAD_CREATE(tid, server_thread, (void * )ssl);
//			}
//		}
//	}
//
//}
