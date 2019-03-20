
/*
 * Copyright (C) Bliss.ai, Inc. 2019
 */

#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_http.h>

static ngx_table_elt_t*
    search_headers_in(ngx_http_request_t* r, u_char* name, size_t len);
static ngx_int_t
    ngx_http_hello_world_handler(ngx_http_request_t *r);
static char *
    ngx_http_hello_world(ngx_conf_t *cf, ngx_command_t *cmd, void *conf);

static ngx_command_t ngx_http_hello_world_commands[] = {
    {
        ngx_string("hello_world"),
        NGX_HTTP_LOC_CONF | NGX_CONF_NOARGS,
        ngx_http_hello_world,
        0,
        0,
        NULL
    },
    ngx_null_command
};

static ngx_http_module_t ngx_http_hello_world_module_ctx = {
    NULL, /* preconfiguration */
    NULL, /* postconfiguration */

    NULL, /* create main configuration */
    NULL, /* init main configuration */

    NULL, /* create server configuration */
    NULL, /* merge server configuration */

    NULL, /* create location configuration */
    NULL  /* merge location configuration */
};

ngx_module_t ngx_http_hello_world_module = {
    NGX_MODULE_V1,
    &ngx_http_hello_world_module_ctx, /* module context */
    ngx_http_hello_world_commands,    /* module directives */
    NGX_HTTP_MODULE,                  /* module type */
    NULL,                             /* init master */
    NULL,                             /* init module */
    NULL,                             /* init process */
    NULL,                             /* init thread */
    NULL,                             /* exit thread */
    NULL,                             /* exit process */
    NULL,                             /* exit master */
    NGX_MODULE_V1_PADDING
};


static char *
ngx_http_hello_world(ngx_conf_t *cf, ngx_command_t *cmd, void *conf) {
    ngx_http_core_loc_conf_t *clcf;

    clcf = ngx_http_conf_get_module_loc_conf(cf, ngx_http_core_module);
    clcf->handler = ngx_http_hello_world_handler;

    return NGX_CONF_OK;
}

static ngx_int_t
ngx_http_hello_world_handler(ngx_http_request_t *r) {
    ngx_buf_t *b;
    ngx_chain_t out;

    // Write output Content-Type header: text/html
    r->headers_out.content_type.len = sizeof("application/json") - 1;
    r->headers_out.content_type.data = (u_char*) "application/json";

    // Find the X-Api-Key header, using a string comparison function.
    // TODO: Use a hash-based search.
    ngx_table_elt_t *ngx_header_x_api_key = search_headers_in(r, (u_char *)"x-api-key", sizeof("x-api-key") - 1);

    // TODO: Add logic here

    // Allocate memory for a buffer.
    b = ngx_pcalloc(r->pool, sizeof(ngx_buf_t));

    // Said buffer will overwrite the output body.
    out.buf = b;
    out.next = NULL;

    // Write output body, if needed
    u_char json_template[] = "{\"apiKey\":\"\"}";
    char* json_response = ngx_pcalloc(r->pool, sizeof(json_template) + ngx_header_x_api_key->value.len - 1);
    
    sprintf(json_response, "{\"apiKey\":\"%s\"}", ngx_header_x_api_key->value.data);

    ngx_log_debug(NGX_LOG_DEBUG_HTTP, r->connection->log, 0, "JSON RESPONSE IS: ", 0);
    ngx_log_debug(NGX_LOG_DEBUG_HTTP, r->connection->log, 0, json_response, 0);
    
    b->pos = (u_char *) json_response;
    b->last = (u_char *) json_response + strlen(json_response);
    b->memory = 1;
    b->last_buf = 1;

    // Write Content-Lenght header.
    r->headers_out.content_length_n = strlen(json_response);
    r->headers_out.status = NGX_HTTP_OK;

    // Write response.
    ngx_http_send_header(r);
    return ngx_http_output_filter(r, &out);
}

/**
 * Searches a header by its name
 */
static ngx_table_elt_t*
search_headers_in(ngx_http_request_t* r, u_char* name, size_t len) {
    ngx_list_part_t* part;
    ngx_table_elt_t* h;

    // Get the first part of the list. There is usual only one part.
    part = &r->headers_in.headers.part;
    h = part->elts;

    /* Headers list array may consist of more than one part,
      so loop through all of it */
    ngx_uint_t i;
    for (i = 0;; i++) {
        if (i >= part->nelts) {
            if (part->next == NULL) {
                // The last part, search is done.
                break;
            }

            part = part->next;
            h = part->elts;
            i = 0;
        }

        // Just compare the lengths and then the names case insensitively.
        if (len != h[i].key.len || ngx_strcasecmp(name, h[i].key.data) != 0) {
            // This header doesn't match.
            continue;
        }

        /* Ta-da, we got one!
          Note, we'v stop the search at the first matched header
          while more then one header may fit. */
        return &h[i];
    }

    // No headers were found
    return NULL;
}