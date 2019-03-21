
/*
 * Copyright (C) Bliss.ai, Inc. 2019
 */

#include <ngx_headers.h>


/**
 * Searches a header by its name
 */
static ngx_table_elt_t*
search_headers_in(ngx_http_request_t* r, ngx_str_t name) {
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
        if (name.len != h[i].key.len || ngx_strcasecmp(name.data, h[i].key.data) != 0) {
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