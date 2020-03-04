void drawbmp (char * filename) {

unsigned int headers[13];
FILE * outfile;
int extrabytes;
int paddedsize;
int x; int y; int n;
int red, green, blue;

extrabytes = 4 - ((WIDTH * 3) % 4);                 // How many bytes of padding to add to each
                                                    // horizontal line - the size of which must
                                                    // be a multiple of 4 bytes.
if (extrabytes == 4)
   extrabytes = 0;

paddedsize = ((WIDTH * 3) + extrabytes) * HEIGHT;

// Headers...
// Note that the "BM" identifier in bytes 0 and 1 is NOT included in these "headers".
                     
headers[0]  = paddedsize + 54;      // bfSize (whole file size)
headers[1]  = 0;                    // bfReserved (both)
headers[2]  = 54;                   // bfOffbits
headers[3]  = 40;                   // biSize
headers[4]  = WIDTH;  // biWidth
headers[5]  = HEIGHT; // biHeight

// Would have biPlanes and biBitCount in position 6, but they're shorts.
// It's easier to write them out separately (see below) than pretend
// they're a single int, especially with endian issues...

headers[7]  = 0;                    // biCompression
headers[8]  = paddedsize;           // biSizeImage
headers[9]  = 0;                    // biXPelsPerMeter
headers[10] = 0;                    // biYPelsPerMeter
headers[11] = 0;                    // biClrUsed
headers[12] = 0;                    // biClrImportant

outfile = fopen(filename, "wb");

//
// Headers begin...
// When printing ints and shorts, we write out 1 character at a time to avoid endian issues.
//

f//printf(outfile, "BM");

for (n = 0; n <= 5; n++)
{
   f//printf(outfile, "%c", headers[n] & 0x000000FF);
   f//printf(outfile, "%c", (headers[n] & 0x0000FF00) >> 8);
   f//printf(outfile, "%c", (headers[n] & 0x00FF0000) >> 16);
   f//printf(outfile, "%c", (headers[n] & (unsigned int) 0xFF000000) >> 24);
}

// These next 4 characters are for the biPlanes and biBitCount fields.

f//printf(outfile, "%c", 1);
f//printf(outfile, "%c", 0);
f//printf(outfile, "%c", 24);
f//printf(outfile, "%c", 0);

for (n = 7; n <= 12; n++)
{
   f//printf(outfile, "%c", headers[n] & 0x000000FF);
   f//printf(outfile, "%c", (headers[n] & 0x0000FF00) >> 8);
   f//printf(outfile, "%c", (headers[n] & 0x00FF0000) >> 16);
   f//printf(outfile, "%c", (headers[n] & (unsigned int) 0xFF000000) >> 24);
}

//
// Headers done, now write the data...
//

for (y = HEIGHT - 1; y >= 0; y--)     // BMP image format is written from bottom to top...
{
   for (x = 0; x <= WIDTH - 1; x++)
   {

      red = reduce(redcount[x][y] + COLOUR_OFFSET) * red_multiplier;
      green = reduce(greencount[x][y] + COLOUR_OFFSET) * green_multiplier;
      blue = reduce(bluecount[x][y] + COLOUR_OFFSET) * blue_multiplier;
      
      if (red > 255) red = 255; if (red < 0) red = 0;
      if (green > 255) green = 255; if (green < 0) green = 0;
      if (blue > 255) blue = 255; if (blue < 0) blue = 0;
      
      // Also, it's written in (b,g,r) format...

      f//printf(outfile, "%c", blue);
      f//printf(outfile, "%c", green);
      f//printf(outfile, "%c", red);
   }
   if (extrabytes)      // See above - BMP lines must be of lengths divisible by 4.
   {
      for (n = 1; n <= extrabytes; n++)
      {
         f//printf(outfile, "%c", 0);
      }
   }
}