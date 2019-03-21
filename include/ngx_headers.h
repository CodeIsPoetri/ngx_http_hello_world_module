
/*
 * Copyright (C) Bliss.ai, Inc. 2019
 */

#ifndef _NGX_HTTP_HEADERS_H_
#define _NGX_HTTP_HEADERS_H_

static ngx_table_elt_t*
    search_headers_in(ngx_http_request_t* r, ngx_str_t name);

#endif