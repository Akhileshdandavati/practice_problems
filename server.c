#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define MAX_CLIENTS 10
#define BUFFER_SIZE 1024

typedef struct
{
	char username[50];
	char password[50];
} User;

typedef struct
{
	char topic[50];
	int clients[MAX_CLIENTS];
	int client_count;
} Topic;

User users[MAX_CLIENTS];
int user_count = 0;

Topic topics[MAX_CLIENTS];
int topic_count = 0;

void handle_client(int client_socket);
void send_message(int client_socket, const char *message);
void register_user(int client_socket, const char *message);
void authenticate_user(int client_socket, const char *message);
void create_topic(int client_socket, const char *message);
void join_topic(int client_socket, const char *message);
void send_to_topic(int client_socket, const char *message);
void list_topics(int client_socket);

int main()
{
	int server_socket, client_socket;
	struct sockaddr_in server_addr, client_addr;
	socklen_t client_len;
	char *ip = "127.0.0.1";

	server_socket = socket(AF_LOCAL, SOCK_STREAM, 0);
	if (server_socket < 0)
	{
		perror("Error creating server socket");
		exit(1);
	}

	server_addr.sin_family = AF_LOCAL;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = inet_addr(ip);

	if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
	{
		perror("Error binding server socket");
		exit(1);
	}

	if (listen(server_socket, MAX_CLIENTS) < 0)
	{
		perror("Error listening for connections");
		exit(1);
	}

	printf("Server started. Waiting for connections...\n");

	while (1)
	{
		client_len = sizeof(client_addr);

		client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_len);
		if (client_socket < 0)
		{
			perror("Error accepting connection");
			exit(1);
		}

		printf("New connection established. Client socket: %d\n", client_socket);

		handle_client(client_socket);
	}

	close(server_socket);

	return 0;
}

void handle_client(int client_socket)
{
	char buffer[BUFFER_SIZE];
	ssize_t bytes_received;

	send_message(client_socket, "Welcome to the chat system!");

	while (1)
	{

		bytes_received = recv(client_socket, buffer, BUFFER_SIZE, 0);
		if (bytes_received < 0)
		{
			perror("Error receiving data from client");
			break;
		}
		else if (bytes_received == 0)
		{
			printf("Client disconnected. Client socket: %d\n", client_socket);
			break;
		}

		buffer[bytes_received] = '\0';
		char *action = strtok(buffer, ":");
		char *parameter = strtok(NULL, "/");

		if (strcmp(action, "register") == 0)
		{
			register_user(client_socket, parameter);
		}
		else if (strcmp(action, "authenticate") == 0)
		{
			authenticate_user(client_socket, parameter);
		}
		else if (strcmp(action, "create_topic") == 0)
		{
			create_topic(client_socket, parameter);
		}
		else if (strcmp(action, "join_topic") == 0)
		{
			join_topic(client_socket, parameter);
		}
		else if (strcmp(action, "send_to_topic") == 0)
		{
			send_to_topic(client_socket, parameter);
		}
		else if (strcmp(action, "list_topics") == 0)
		{
			list_topics(client_socket);
		}
		else
		{
			send_message(client_socket, "Invalid action");
		}
	}
	close(client_socket);
}

void send_message(int client_socket, const char *message)
{
	ssize_t bytes_sent;

	bytes_sent = send(client_socket, message, strlen(message), 0);
	if (bytes_sent < 0)
	{
		perror("Error sending data to client");
		exit(1);
	}
}

void register_user(int client_socket, const char *message)
{
	char username[50];
	char password[50];

	sscanf(message, "%s %s", username, password);

	for (int i = 0; i < user_count; i++)
	{
		if (strcmp(users[i].username, username) == 0)
		{
			send_message(client_socket, "Username already exists. Please choose a different username.");
			return;
		}
	}

	if (user_count < MAX_CLIENTS)
	{
		strcpy(users[user_count].username, username);
		strcpy(users[user_count].password, password);
		user_count++;
		send_message(client_socket, "Registration successful. You can now authenticate with your credentials.");
	}
	else
	{
		send_message(client_socket, "Maximum user limit reached. Registration failed.");
	}
}

void authenticate_user(int client_socket, const char *message)
{
	char username[50];
	char password[50];

	sscanf(message, "%s %s", username, password);

	for (int i = 0; i < user_count; i++)
	{
		if (strcmp(users[i].username, username) == 0)
		{
			if (strcmp(users[i].password, password) == 0)
			{
				send_message(client_socket, "Authentication successful. You are now logged in.");
				return;
			}
			else
			{
				send_message(client_socket, "Incorrect password. Please try again.");
				return;
			}
		}
	}

	send_message(client_socket, "User not found. Please register an account.");
}

void create_topic(int client_socket, const char *message)
{
	char topic_name[50];

	sscanf(message, "%s", topic_name);

	for (int i = 0; i < topic_count; i++)
	{
		if (strcmp(topics[i].topic, topic_name) == 0)
		{
			send_message(client_socket, "Topic already exists. Please choose a different topic name.");
			return;
		}
	}

	if (topic_count < MAX_CLIENTS)
	{
		strcpy(topics[topic_count].topic, topic_name);
		topics[topic_count].client_count = 0;
		topic_count++;
		send_message(client_socket, "Topic created successfully.");
	}
	else
	{
		send_message(client_socket, "Maximum topic limit reached. Topic creation failed.");
	}
}

void join_topic(int client_socket, const char *message)
{
	char topic_name[50];

	sscanf(message, "%s", topic_name);

	int topic_index = -1;
	for (int i = 0; i < topic_count; i++)
	{
		if (strcmp(topics[i].topic, topic_name) == 0)
		{
			topic_index = i;
			break;
		}
	}

	if (topic_index != -1)
	{
		for (int i = 0; i < topics[topic_index].client_count; i++)
		{
			if (topics[topic_index].clients[i] == client_socket)
			{
				send_message(client_socket, "You are already a member of this topic.");
				return;
			}
		}

		if (topics[topic_index].client_count < MAX_CLIENTS)
		{
			topics[topic_index].clients[topics[topic_index].client_count] = client_socket;
			topics[topic_index].client_count++;
			send_message(client_socket, "You have joined the topic successfully.");
		}
		else
		{
			send_message(client_socket, "Maximum topic capacity reached. Joining the topic failed.");
		}
	}
	else
	{
		send_message(client_socket, "Topic not found. Please enter a valid topic name.");
	}
}

void send_to_topic(int client_socket, const char *message)
{
	char topic_name[50];
	char topic_message[BUFFER_SIZE];

	sscanf(message, "%s %[^\n]", topic_name, topic_message);

	int topic_index = -1;
	for (int i = 0; i < topic_count; i++)
	{
		if (strcmp(topics[i].topic, topic_name) == 0)
		{
			topic_index = i;
			break;
		}
	}

	if (topic_index != -1)
	{
		int is_member = 0;
		for (int i = 0; i < topics[topic_index].client_count; i++)
		{
			if (topics[topic_index].clients[i] == client_socket)
			{
				is_member = 1;
				break;
			}
		}

		if (is_member)
		{
			for (int i = 0; i < topics[topic_index].client_count; i++)
			{
				int recipient_socket = topics[topic_index].clients[i];
				if (recipient_socket != client_socket)
				{
					send_message(recipient_socket, topic_message);
				}
			}
		}
		else
		{
			send_message(client_socket, "You are not a member of this topic. Join the topic first.");
		}
	}
	else
	{
		send_message(client_socket, "Topic not found. Please enter a valid topic name.");
	}
}

void list_topics(int client_socket)
{
	if (topic_count == 0)
	{
		send_message(client_socket, "No topics available.");
	}
	else
	{
		char topic_list[BUFFER_SIZE];
		strcpy(topic_list, "Available topics:\n");

		for (int i = 0; i < topic_count; i++)
		{
			char topic_info[BUFFER_SIZE];
			snprintf(topic_info, sizeof(topic_info), "- %s (%d members)\n", topics[i].topic, topics[i].client_count);
			strcat(topic_list, topic_info);
		}

		send_message(client_socket, topic_list);
	}
}