NGX_VERSION=1.15.9
OSSL_VERSION=1.0.2r

NGX_SLUG=nginx-$(NGX_VERSION)
OSSL_SLUG=openssl-$(OSSL_VERSION)

OSSL_FOLDER=$(VENDOR_FOLDER)$(OSSL_SLUG)
NGX_FOLDER=$(VENDOR_FOLDER)$(NGX_SLUG)
VENDOR_FOLDER=vendor/

default: build

clean:
	$(MAKE) -C $(NGX_FOLDER) -f Makefile clean

$(NGX_FOLDER)/Makefile:
	$(MAKE) configure

configure: $(VENDOR_FOLDER)
	cd $(NGX_FOLDER); ./configure --with-compat --with-debug \
			--add-module=../..

build: $(NGX_FOLDER) $(OSSL_FOLDER) $(NGX_FOLDER)/Makefile
	$(MAKE) -C $(NGX_FOLDER) -f Makefile modules
	if [ ! -d objs ]; then mkdir objs; fi
	cp $(NGX_FOLDER)/objs/*.so objs

install: $(VENDOR_FOLDER)
	curl http://nginx.org/download/$(NGX_SLUG).tar.gz -o $(NGX_SLUG).tar.gz
	tar -zxf $(NGX_SLUG).tar.gz -C $(VENDOR_FOLDER)
	rm -rf $(NGX_SLUG).tar.gz
	curl https://www.openssl.org/source/$(OSSL_SLUG).tar.gz -o $(OSSL_SLUG).tar.gz
	tar -zxf $(OSSL_SLUG).tar.gz -C $(VENDOR_FOLDER)
	rm -rf $(OSSL_SLUG).tar.gz
	

$(VENDOR_FOLDER):
	if [ ! -d vendor ]; then mkdir vendor; fi

deploy:
	$(MAKE) -C $(NGX_FOLDER) -f Makefile install
