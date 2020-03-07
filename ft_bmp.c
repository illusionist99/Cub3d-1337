#include "libcub3d.h"

void ft_handle_bmp()
{
    int fd = open("file.bmp", O_CREAT | O_RDWR , 0644);
    int filesize = 54 + 3*data.Width*data.Height;

    unsigned char bmpfileheader[14] = {'B','M', 0,0,0,0, 0,0, 0,0, 54,0,0,0};
    unsigned char bmpinfoheader[40] = {40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0, 24,0};
    unsigned char bmppad[3] = {0,0,0};

    bmpfileheader[ 2] = (unsigned char)(filesize    );
    bmpfileheader[ 3] = (unsigned char)(filesize>> 8);
    bmpfileheader[ 4] = (unsigned char)(filesize>>16);
    bmpfileheader[ 5] = (unsigned char)(filesize>>24);

    bmpinfoheader[ 4] = (unsigned char)(       data.Width    );
    bmpinfoheader[ 5] = (unsigned char)(       data.Width>> 8);
    bmpinfoheader[ 6] = (unsigned char)(       data.Width>>16);
    bmpinfoheader[ 7] = (unsigned char)(       data.Width>>24);
    bmpinfoheader[ 8] = (unsigned char)(       data.Height    );
    bmpinfoheader[ 9] = (unsigned char)(       data.Height >> 8);
    bmpinfoheader[10] = (unsigned char)(       data.Height >>16);
    bmpinfoheader[11] = (unsigned char)(       data.Height >>24);

    write(fd, bmpfileheader, 14);
    write(fd, bmpinfoheader, 40);

    int i;
    int j;
    int num;

    i = 0;
    j = 0;
    while (i < data.Height)
    {
        num = (data.Height - i - 1) * data.Width;
        j = 0;
        while (j < data.Width)
        {
            write(fd, &image.data[num + j], 3);
            j++;
        }
        i++;
    }
    close(fd);
    system(ft_strjoin("kill " , ft_itoa(x)));
    exit(1);
}
