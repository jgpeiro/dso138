
#ifndef _FRAMEBUFFER_H_
#define _FRAMEBUFFER_H_

#include <stdint.h>

struct sFrameBuffer
{
    int width, height;
    uint8_t *pBuffer;
};
typedef struct sFrameBuffer tFrameBuffer;

void frameBufferOpen( tFrameBuffer *pFrameBuffer, int width, int height,  uint8_t *pBuffer );
void frameBufferPutPixel( tFrameBuffer *pFrameBuffer, int x, int y, uint8_t color );
void frameBufferPrint( tFrameBuffer *pFrameBuffer );
void frameBufferClear( tFrameBuffer *pFrameBuffer, uint8_t color );

#endif /* _FRAMEBUFFER_H_ */
