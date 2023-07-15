
#include <stdlib.h>

#include "framebuffer.h"

/*
uint8_t buffer[3*2];//[320*240];
tFrameBuffer frame_buffer =
{
        320, 240,
        buffer
};
*/

void frameBufferOpen( tFrameBuffer *pFrameBuffer, int width, int height,  uint8_t *pBuffer ){
    pFrameBuffer->width = width;
    pFrameBuffer->height = height;
    pFrameBuffer->pBuffer = pBuffer;
}

void frameBufferPutPixel( tFrameBuffer *pFrameBuffer, int x, int y, uint8_t color ){
    if( pFrameBuffer->pBuffer != NULL ){
        if( 0 <= x && x < pFrameBuffer->width ){
            if( 0 <= y && y < pFrameBuffer->height ){
                pFrameBuffer->pBuffer[y*pFrameBuffer->width+x] = color;
            }
        }
    }
}

void frameBufferPrint( tFrameBuffer *pFrameBuffer ){
    int x, y;
    for( y = 0 ; y < pFrameBuffer->height ; y++ ){
        //printf("%04d    ", y );
        for( x = 0 ; x < pFrameBuffer->width ; x++ ){
            if( pFrameBuffer->pBuffer[y*pFrameBuffer->width+x] )
            {
                //printf( "%02x ", pFrameBuffer->pBuffer[y*pFrameBuffer->width+x] );
            }
            else
            {
                //printf( ".. " );
            }
        }
        //printf( "\n" );
    }
}

void frameBufferClear( tFrameBuffer *pFrameBuffer, uint8_t color ){
    int x, y;
    for( y = 0 ; y < pFrameBuffer->height ; y++ ){
        for( x = 0 ; x < pFrameBuffer->width ; x++ ){
            pFrameBuffer->pBuffer[y*pFrameBuffer->width+x] = color;
        }
    }
}
