#include <libssh/libssh.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

char* ssh_host = "111.111.111.111";
int ssh_port = 22;
char* ssh_username = "foo";
char* ssh_password = "bar";
char* ssh_command = "pwd && ls -al";

int is_insecure = 1;

int verify_knownhost(ssh_session session);
int execute_remotessh_command(ssh_session session, int out_buf_maxlen, char* out_buf, int* out_buf_nbytes);

int main()
{
    ssh_session my_ssh_session;
    int verbosity = SSH_LOG_PROTOCOL;
    int port = ssh_port;
    int rc;

    #define MAX_OUTPUT_LEN 4096
    char strout[MAX_OUTPUT_LEN];
    int strout_len;

    // Creating the session and setting options
    my_ssh_session = ssh_new();
    if (my_ssh_session == NULL)
    exit(-1);

    ssh_options_set(my_ssh_session, SSH_OPTIONS_HOST, ssh_host);
    ssh_options_set(my_ssh_session, SSH_OPTIONS_LOG_VERBOSITY, &verbosity);
    ssh_options_set(my_ssh_session, SSH_OPTIONS_PORT, &port);
    ssh_options_set(my_ssh_session, SSH_OPTIONS_USER, ssh_username);

    // Connecting to the server
    rc = ssh_connect(my_ssh_session);
    if (rc != SSH_OK)
    {
        fprintf(stderr, "Error connecting to localhost: %s\n", ssh_get_error(my_ssh_session));
        exit(-1);
    }

    // Authenticating the server
    if(is_insecure != 1) {
        if (verify_knownhost(my_ssh_session) < 0)
        {
            ssh_disconnect(my_ssh_session);
            ssh_free(my_ssh_session);
            exit(-1);
        }
    }


    // Authenticating the user password
    rc = ssh_userauth_password(my_ssh_session, NULL, ssh_password);
    if (rc != SSH_AUTH_SUCCESS)
    {
        fprintf(stderr, "Error authenticating with password: %s\n", ssh_get_error(my_ssh_session));
        ssh_disconnect(my_ssh_session);
        ssh_free(my_ssh_session);
        exit(-1);
    }

    // Execute command
    rc = execute_remotessh_command(my_ssh_session, MAX_OUTPUT_LEN, strout, &strout_len);
    if (rc != SSH_OK)
    {
        fprintf(stderr, "Error execute remote ssh: %s\n", ssh_get_error(my_ssh_session));
        ssh_disconnect(my_ssh_session);
        ssh_free(my_ssh_session);
        exit(-1);
    }

    // Display output from buffer
    printf("==================================\n");
    printf("\n%s\n", strout);
    printf("==================================\n"); 

    // End session
    ssh_disconnect(my_ssh_session);
    ssh_free(my_ssh_session);
}

int execute_remotessh_command(ssh_session session, int out_buf_maxlen, char* out_buf, int* out_buf_nbytes)
{
    ssh_channel channel;
    int rc;
    char buffer[256];
    int nbytes;
    int out_buf_cnt = 0;
    int is_full = 0;

    channel = ssh_channel_new(session);
    if (channel == NULL)
    return SSH_ERROR;

    rc = ssh_channel_open_session(channel);
    if (rc != SSH_OK)
    {
        ssh_channel_free(channel);
        return rc;
    }

    rc = ssh_channel_request_exec(channel, ssh_command);
    if (rc != SSH_OK)
    {
        ssh_channel_close(channel);
        ssh_channel_free(channel);
        return rc;
    }

    nbytes = ssh_channel_read(channel, buffer, sizeof(buffer), 0);
    while ((nbytes > 0) && (is_full == 0))
    {        
        if( (out_buf_cnt + nbytes) > out_buf_maxlen) {
            nbytes = out_buf_maxlen - out_buf_cnt;
            is_full = 1;
        }
        
        memcpy(&out_buf[out_buf_cnt], buffer, nbytes);
        out_buf_cnt = out_buf_cnt + nbytes;
        nbytes = ssh_channel_read(channel, buffer, sizeof(buffer), 0);
    }

    if (nbytes < 0)
    {
        ssh_channel_close(channel);
        ssh_channel_free(channel);
        return SSH_ERROR;
    }

    ssh_channel_send_eof(channel);
    ssh_channel_close(channel);
    ssh_channel_free(channel);

    *out_buf_nbytes = out_buf_cnt;
    
    return SSH_OK;
}

int verify_knownhost(ssh_session session)
{
    enum ssh_known_hosts_e state;
    unsigned char *hash = NULL;
    ssh_key srv_pubkey = NULL;
    size_t hlen;
    char buf[10];
    char *hexa;
    char *p;
    int cmp;
    int rc;
    
    rc = ssh_get_server_publickey(session, &srv_pubkey);
    if (rc < 0) {
        return -1;
    }
    
    rc = ssh_get_publickey_hash(srv_pubkey,
                                SSH_PUBLICKEY_HASH_SHA1,
                                &hash,
                                &hlen);
    ssh_key_free(srv_pubkey);
    if (rc < 0) {
        return -1;
    }
    
    state = ssh_session_is_known_server(session);
    switch (state) {
        case SSH_KNOWN_HOSTS_OK:
            /* OK */
            
            break;
        case SSH_KNOWN_HOSTS_CHANGED:
            fprintf(stderr, "Host key for server changed: it is now:\n");
            ssh_print_hash(SSH_PUBLICKEY_HASH_SHA1, hash, hlen); // ssh_print_hexa("Public key hash", hash, hlen);            
            fprintf(stderr, "For security reasons, connection will be stopped\n");
            ssh_clean_pubkey_hash(&hash);
            
            return -1;
        case SSH_KNOWN_HOSTS_OTHER:
            fprintf(stderr, "The host key for this server was not found but an other"
                    "type of key exists.\n");
            fprintf(stderr, "An attacker might change the default server key to"
                    "confuse your client into thinking the key does not exist\n");
            ssh_clean_pubkey_hash(&hash);

            return -1;
        case SSH_KNOWN_HOSTS_NOT_FOUND:
            fprintf(stderr, "Could not find known host file.\n");
            fprintf(stderr, "If you accept the host key here, the file will be"
                    "automatically created.\n");

            /* FALL THROUGH to SSH_SERVER_NOT_KNOWN behavior */

        case SSH_KNOWN_HOSTS_UNKNOWN:
            hexa = ssh_get_hexa(hash, hlen);
            fprintf(stderr,"The server is unknown. Do you trust the host key?\n");
            fprintf(stderr, "Public key hash: %s\n", hexa);
            ssh_string_free_char(hexa);
            ssh_clean_pubkey_hash(&hash);
            p = fgets(buf, sizeof(buf), stdin);
            if (p == NULL) {
                return -1;
            }

            cmp = strncasecmp(buf, "yes", 3);
            if (cmp != 0) {
                return -1;
            }

            rc = ssh_session_update_known_hosts(session);
            if (rc < 0) {
                fprintf(stderr, "Error %s\n", strerror(errno));
                return -1;
            }

            break;
        case SSH_KNOWN_HOSTS_ERROR:
            fprintf(stderr, "Error %s", ssh_get_error(session));
            ssh_clean_pubkey_hash(&hash);
            return -1;
    }

    ssh_clean_pubkey_hash(&hash);
    return 0;
}
