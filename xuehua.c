作者：Milo Yip
链接：https://zhuanlan.zhihu.com/p/24688522
来源：知乎
著作权归作者所有，转载请联系作者获得授权。

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char* image;
static int x, y, w, h;

static void Put(int i, int j, char c) {
    char *p = image + j * w + i;
    if (*p == ' ' || *p == '_') // _ can be overridden by / or \.
        *p = c;
}

static void KochCurve(int n, int dir) {
    if (n == 0)
        switch (dir % 6) {
            case 0: Put(x++, y  , '_' );
                    Put(x++, y,   '_' ); break;
            case 1: Put(x++, y--, '/' ); break;
            case 2: Put(--x, y--, '\\'); break;
            case 3: Put(--x,   y, '_' );
                    Put(--x,   y, '_' ); break;
            case 4: Put(--x, ++y, '/' ); break;
            case 5: Put(x++, ++y, '\\'); break;
        }
    else {
        KochCurve(n - 1, dir    );
        KochCurve(n - 1, dir + 1);
        KochCurve(n - 1, dir + 5);
        KochCurve(n - 1, dir    );
    }
}

int main() {
    w = 2;
    h = 1;
    for (int n = 0; n < 4; n++) {
        image = (char*)malloc(w * h);
        memset(image, ' ', w * h);

        x = 0;
        y = h - 1;
        KochCurve(n, 0);

        printf("\nn=%d\n\n", n);
        for (int j = 0; j < h; j++) {
            for (int i = 0; i < w; i++)
                putchar(image[j * w + i]);
            putchar('\n');
        }

        w *= 3;
        h = n == 0 ? 1 : h * 3;
        free(image);
    }
}
