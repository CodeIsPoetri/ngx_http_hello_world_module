## Nginx Module Template

## Configuration

First, you have to successfully install the dependencies. To do so, run

```bash
make install
```

Then, you'll be able to run configuration.

```bash
make configure
```

## Development

The [`ngx_http_hello_world_module.c`](ngx_http_hello_world_module.c) is the main module file.

## Building

To build the project, run

```bash
make
```

## Testing

To test, run

```bash
sudo make deploy
sudo /usr/local/nginx/sbin/nginx
```

You'll need to restart `nginx` every time you rebuild the module.