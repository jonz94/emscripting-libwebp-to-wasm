#include <stdlib.h>
#include "emscripten.h"
#include "../libwebp/src/webp/decode.h"
#include "../libwebp/src/webp/encode.h"

EMSCRIPTEN_KEEPALIVE
int getDecoderVersion() {
  return WebPGetDecoderVersion();
}

EMSCRIPTEN_KEEPALIVE
int* getInfo(const uint8_t* data, size_t size) {
  int* results = (int*) malloc(3 * sizeof(int));

  int width;
  int height;

  // (const uint8_t* data, size_t size, int* w, int* h) -> int;
  results[0] = WebPGetInfo(data, size, &width, &height);
  results[1] = width;
  results[2] = height;

  return results;
}

EMSCRIPTEN_KEEPALIVE
uint8_t* decode(const uint8_t* data, size_t size) {
  int width;
  int height;

  uint8_t* buffer = WebPDecodeRGBA(data, size, &width, &height);
  return buffer;
}

EMSCRIPTEN_KEEPALIVE
uint8_t* createBuffer(int size) {
  return malloc(size * sizeof(uint8_t));
}

EMSCRIPTEN_KEEPALIVE
uint8_t* createBufferViaDimension(int width, int height) {
  return malloc(width * height * 4 * sizeof(uint8_t));
}

EMSCRIPTEN_KEEPALIVE
void destroyBuffer(uint8_t* pointer) {
  free(pointer);
}

EMSCRIPTEN_KEEPALIVE
int getEncoderVersion() {
  return WebPGetEncoderVersion();
}

int encodeResult[2];
EMSCRIPTEN_KEEPALIVE
void encode(uint8_t* img_in, int width, int height, float quality) {
  uint8_t* img_out;
  size_t size;

  size = WebPEncodeRGBA(img_in, width, height, width * 4, quality, &img_out);

  encodeResult[0] = (int) img_out;
  encodeResult[1] = size;
}

EMSCRIPTEN_KEEPALIVE
void freeResult(uint8_t* result) {
  WebPFree(result);
}

EMSCRIPTEN_KEEPALIVE
int getEncodeResultPointer() {
  return encodeResult[0];
}

EMSCRIPTEN_KEEPALIVE
int getEncodeResultSize() {
  return encodeResult[1];
}
