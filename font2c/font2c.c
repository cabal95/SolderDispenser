#include <stdio.h>

#include <ft2build.h>
#include FT_FREETYPE_H
#include <ftbitmap.h>

static FT_Library library;
static FT_Face face;
static FT_Error err;
static FT_Bitmap tempbitmap;

int bitmap_width = 0;
int bitmap_height = 0;

static void to_xbm( FT_Bitmap*  bitmap, unsigned char ch)
{
    if (bitmap_width == 0) {
	bitmap_width = bitmap->width;
	bitmap_height = bitmap->rows;

	printf("const unsigned char PROGMEM font%dx%d[] = {\r\n", bitmap_width, bitmap_height);
    }

    if (bitmap_width != bitmap->width) {
        printf("Glyph '%c' does not match expected size.\r\n", ch);
        exit(1);
    }

    printf("    ");
    for (int y = 0; y < bitmap->rows; y++ )
    {
        int b = 0;
        int bx = 0;
        for (int x = 0; x < bitmap->width; x++, bx++ )
        {
            int pixel = bitmap->buffer[(y * bitmap->width) + x] != 0 ? 1 : 0;
            b |= pixel << bx;

            if (bx == 8)
            {
                printf("0x%02x, ", b);
                b = 0;
                bx = 0;
            }
        }

        if (bx > 0) {
            printf("0x%02x, ", b);
        }
    }

    printf("// '%c'\r\n", ch);
}

static void draw_glyph(unsigned char glyph) {
	FT_UInt  glyph_index;
	FT_GlyphSlot  slot = face->glyph;

	glyph_index = FT_Get_Char_Index( face, glyph );

	if ((err = FT_Load_Glyph( face, glyph_index, FT_LOAD_DEFAULT ))) {
		fprintf( stderr, "warning: failed FT_Load_Glyph 0x%x %d\n", glyph, err);
		return;
	}

    if ((err = FT_Render_Glyph( face->glyph, FT_RENDER_MODE_MONO ))) {
    	fprintf( stderr, "warning: failed FT_Render_Glyph 0x%x %d\n", glyph, err);
    	return;
    }

	FT_Bitmap_New(&tempbitmap);
	FT_Bitmap_Convert( library, &slot->bitmap, &tempbitmap, 1);

    //to_bitmap( &slot->bitmap, *x + slot->bitmap_left, *y - slot->bitmap_top );
    to_xbm( &tempbitmap, glyph );

	FT_Bitmap_Done( library, &tempbitmap );
}

int main(int argc, char **argv) {
	char *filename;
	int x = 0, y = 0;
	int g;

	if (argc < 2) {
		fprintf( stderr, "usage: font2c [font]\n");
		exit(1);
	}
	filename = argv[1];

	if ((err = FT_Init_FreeType( &library ))) {
		fprintf( stderr, "error: Init_Freetype failed %d\n", err);
		exit(1);
	}
	if ((err = FT_New_Face( library, filename, 0, &face ))) {
		fprintf( stderr, "error: FT_New_Face failed %d\n", err);
		exit(1);
	}

	for (g = ' '; g <= 126; g++) {
		draw_glyph(g);
	}

	printf("};\r\n");

	FT_Done_Face( face );
	FT_Done_FreeType( library );

	return 0;
}
