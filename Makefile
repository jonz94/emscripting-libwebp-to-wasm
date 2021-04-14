all:
	$(MAKE) build

build:
	docker run --rm -v $(CURDIR):/src emscripten/emsdk bash -c "mkdir -p dist && emcc -O3 -s WASM=1 -s EXTRA_EXPORTED_RUNTIME_METHODS='[\"cwrap\", \"getValue\"]' -I libwebp src/webp.c libwebp/src/**/*.c -o dist/webp.js"
