#ifndef FTP_CLIENT_H
#define FTP_CLIENT_H
#define _GNU_SOURCE

#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
#include <ctype.h>
#include <time.h>


#define INVALID_SOCKET -1
#define INVALID_IP -1
#define MAX_SIZE 1024
#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50
#define MAX_FILENAME_LEN 256
#define MAX_FILES 10

#define PORT 9000
#define DEFAULT_PORT 5500
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct addrinfo ADDRINFO;

struct command
{
	char arg[MAX_SIZE];
	char code[5];
};

typedef struct
{
	char username[MAX_SIZE];
	char password[MAX_SIZE];
} Account;



/*Validating IP Address*/
int validate_ip(const char *ip);

/*
 * Get file name from string of files
 */
void separate_filenames(const char *input, char output[][MAX_FILENAME_LEN], int *count);

/**
 * Print response message
 */
void print_reply(int rc);

/**
 * Receive a response from server
 * Returns -1 on error, return code on success
 */
int read_reply(int sock_control);

/**
 * Input: cmd struct with an a code and an arg
 * Concats code + arg into a string and sends to server
 */
int ftclient_send_cmd(struct command *cmd, int sock_control);

/**
 * Read input from command line
 */
void read_input(char *user_input, int size);

/**
 * Get login details from user and
 * send to server for authentication
 */
void ftclient_login(int sock_control);

/**
 * Parse command in cstruct
 */
int ftclient_read_command(char *user_input, int size, struct command *cstruct);

/**
 * Create listening socket on remote host
 * Returns -1 on error, socket fd on success
 */
int socket_create(int port);

/**
 * Create new socket for incoming client connection request
 * Returns -1 on error, or fd of newly created socket
 */
int socket_accept(int sock_listen);

/**
 * Open data connection
 */
int ftclient_open_conn(int sock_con);

/**
 * Do list commmand
 */
int ftclient_list(int sock_data, int sock_ctrl);

/*
 * Send folder command
 */
int ftclient_zip(int sock_data, int sock_ctrl);

/**
 * Do get <filename> command
 */
int ftclient_get(int data_sock, int sock_control, char *arg);

int ftclient_private_get(int data_sock, int sock_control, char *arg);

void upload(int data_sock, char *filename, int sock_control);

/*
 * Send multiple files command
 */
int ftclient_send_multiple(int data_sock, char *filename, int sock_control);

/*
 * Private send command
 */
void private_upload(int data_sock, char *filename, int sock_control);

/*
 * Helper function
 */
void ftclient_help(int sock_data, int sock_control);

int login_menu();
int signup();
void runProgressBar(int status);

#endif // FTP_CLIENT_H
