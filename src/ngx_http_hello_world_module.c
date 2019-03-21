
/*
 * Copyright (C) Bliss.ai, Inc. 2019
 */

#include <ngx_http_hello_world_module.h>
#include <ngx_headers.h>
#include "ngx_headers.c"

static ngx_int_t
ngx_http_hello_world_module_init(ngx_conf_t *cf) {
    ngx_http_core_main_conf_t   *cmcf;
    ngx_http_handler_pt         *h;

    cmcf = ngx_http_conf_get_module_main_conf(cf, ngx_http_core_module);
    h = ngx_array_push(&cmcf->phases[NGX_HTTP_PREACCESS_PHASE].handlers);
    
    if (h == NULL) {
        return NGX_ERROR;
    }

    *h = ngx_http_hello_world_handler;

    return NGX_OK;
}

static char *
ngx_http_hello_world(ngx_conf_t *cf, ngx_command_t *cmd, void *conf) {
    return NGX_CONF_OK;
}

static ngx_int_t
ngx_http_hello_world_handler(ngx_http_request_t *r) {
    ngx_table_elt_t *header;
    
    // Find the X-Api-Key header, using a string comparison function.
    // TODO: Use a hash-based search.
    ngx_str_t name = ngx_string("x-api-key");
    header = search_headers_in(r, name);

    if (header == NULL) {
        return NGX_HTTP_UNAUTHORIZED;
    }
    
    if (ngx_strcasecmp(header->value.data, (u_char *) "lkashjdkalsjdaljhf6er65rt7ks")) {
        return NGX_HTTP_UNAUTHORIZED;
    }

    return NGX_OK;
}
