# Nginx Module Template

This example reads the `X-Api-Key` and outputs its value in a JSON response.

## Configuration

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

To test, copy the resulting library from `objs/ngx_http_hello_world_module.so`, to the modules folder in nginx (the location mighy vary between installation configuration).

Also, on the `nginx.conf` file, on root, add the following directive:

```nginx
load_module modules/ngx_http_hello_world_module.so;
```

> Note: By running `nginx -t`, you'll find out where the library should be located. Normally, the folder `modules` doesn't exist, so you might have to run `mkdir`.

You'll need to restart `nginx` every time you rebuild the module.

## FAQ

### What version do I have to set in Makefile

Nginx locks their modules to run in the same version it was compiled with. In this case, you have to modify the variable `NGX_VERSION` on [`Makefile`](Makefile) to match the installed version of `nginx` you have installed.

### What if I get an error telling me the library is not binary compatible

That's probably because some distributions of nginx (Homebrew for macOS, for instance) don't build their nginx using the `--with-compat` option, which removes the enforcement to have a match between the module and nginx binary.

In macOS, there's already a workaround: modify the Homebrew formulae for nginx (usually located on [`/usr/local/Homebrew/Library/Taps/homebrew/homebrew-core`](/usr/local/Homebrew/Library/Taps/homebrew/homebrew-core)), using this [patch](https://github.com/pandres95/homebrew-core/blob/master/Formula/nginx.rb), and reinstalling via:

```bash
brew reinstall --build-from-source nginx
```