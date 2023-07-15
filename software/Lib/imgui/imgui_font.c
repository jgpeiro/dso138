
#include "imgui_font.h"
#include "imgui_draw_prim.h"
#include "imgui_font_kyrou8.h"

const tFont *pFont_def = &font_kyrou8;
/*
void draw_char( const tFont *pFont, int16_t x0, int16_t y0, uint8_t c, tColor color )
{
    int16_t x, y, w, bitmap, b;
    int16_t px, py;

    for( y = 0 ; y < pFont->pGlyphs[c-32]->bbxh ; y++ )
    {
        w = (pFont->pGlyphs[c-32]->bbxw-1)/8+1;

        for( x = 0 ; x < pFont->pGlyphs[c-32]->bbxw ; x+=8 )
        {
            bitmap = pFont->pGlyphs[c-32]->pBitmap[y*w+x/8];

            for( b = 0 ; b < 8 ; b++ )
            {
                if( x+b >= pFont->pGlyphs[c-32]->bbxw )
                {
                    break;
                }

                px = x0+x+b;
                py = y0+y;
                py += pFont->bbxh;
                py -= pFont->descent;
                py -= pFont->pGlyphs[c-32]->bbxh;
                py -= pFont->pGlyphs[c-32]->bbxy;

                if( bitmap & (0x80>>b) )
                {
                	draw_pixel( px, py, color );
                }
            }
        }
    }
}
*/
void draw_char( const tFont *pFont, int16_t x0, int16_t y0, uint8_t c, tColor color )
{
    int16_t x, y, w, bitmap, b;
    int16_t px, py;
    const tGlyph *pGlyph;

    pGlyph = pFont->pGlyphs[c-32];

    y0 += pFont->bbxh;
    y0 -= pFont->descent;
    y0 -= pGlyph->bbxh;
    y0 -= pGlyph->bbxy;

    for( y = 0 ; y < pGlyph->bbxh ; y++ )
    {
        py = y0+y;

        w = (pGlyph->bbxw-1)/8+1;

        int16_t yw = y*w;
        for( x = 0 ; x < pGlyph->bbxw ; x+=8 )
        {
            bitmap = pGlyph->pBitmap[yw+x/8];

            for( b = 0 ; b < 8 ; b++ )
            {
                if( x+b >= pGlyph->bbxw )
                {
                    break;
                }

                px = x0+x+b;

                if( bitmap & (0x80>>b) )
                {
                    draw_pixel( px, py, color );
                }
            }
        }
    }
}


tRectangle get_char_rect( const tFont *pFont, uint8_t c )
{
    tRectangle rect = {0};

    rect.width = pFont->pGlyphs[c-32]->dwidthx;
    rect.height = pFont->bbxh;
    return rect;
}

tRectangle get_text_rect( const tFont *pFont, char *pString )
{
	uint8_t i;
	tRectangle rect = {0};

	rect.height = pFont->bbxh;
	for( i = 0 ; pString[i] != '\0' ; i++ )
	{
		rect.width += get_char_rect( pFont, pString[i] ).width;
    }

    return rect;
}
