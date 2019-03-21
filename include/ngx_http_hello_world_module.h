
/*
 * Copyright (C) Bliss.ai, Inc. 2019
 */

#ifndef _NGX_HTTP_HELLO_WORLD_MODULE_H_
#define _NGX_HTTP_HELLO_WORLD_MODULE_H_

#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_http.h>


static ngx_int_t
    ngx_http_hello_world_handler(ngx_http_request_t *r);
static char *
    ngx_http_hello_world(ngx_conf_t *cf, ngx_command_t *cmd, void *conf);
static ngx_int_t
    ngx_http_hello_world_module_init(ngx_conf_t *cf);


static ngx_command_t ngx_http_hello_world_commands[] = {
    {
        ngx_string("hello_world"),              /* name */
        NGX_HTTP_LOC_CONF | NGX_CONF_NOARGS,    /* type */
        ngx_http_hello_world,                   /* set */
        0,                                      /* conf */
        0,                                      /* offset */
        NULL                                    /* post */
    },
    ngx_null_command
};

static ngx_http_module_t ngx_http_hello_world_module_ctx = {
    NULL,                               /* preconfiguration */
    ngx_http_hello_world_module_init,   /* postconfiguration */

    NULL,                               /* create main configuration */
    NULL,                               /* init main configuration */

    NULL,                               /* create server configuration */
    NULL,                               /* merge server configuration */

    NULL,                               /* create location configuration */
    NULL                                /* merge location configuration */
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

#endif