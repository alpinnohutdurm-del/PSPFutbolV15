#include <pspkernel.h>
#include <pspdebug.h>
#include <pspctrl.h>
#include <pspdisplay.h>

PSP_MODULE_INFO("PSP Futbol V15", 0, 1, 0);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER);

int main(void)
{
    SceCtrlData pad;
    int menu = 0;
    int score1 = 0;
    int score2 = 0;
    int playing = 0;
    unsigned int old = 0;

    sceCtrlSetSamplingCycle(0);
    sceCtrlSetSamplingMode(PSP_CTRL_MODE_DIGITAL);
    pspDebugScreenInit();

    while (1) {
        unsigned int pressed;

        sceCtrlReadBufferPositive(&pad, 1);
        pressed = pad.Buttons & ~old;
        old = pad.Buttons;

        pspDebugScreenClear();

        if (!playing) {
            pspDebugScreenPrintf("PSP FUTBOL V15\n");
            pspDebugScreenPrintf("====================\n\n");

            pspDebugScreenPrintf("%s Gosterisi Maci\n",
                menu == 0 ? ">" : " ");
            pspDebugScreenPrintf("%s Turnuva\n",
                menu == 1 ? ">" : " ");
            pspDebugScreenPrintf("%s Cikis\n\n",
                menu == 2 ? ">" : " ");

            pspDebugScreenPrintf("YUKARI/ASAGI: Sec\n");
            pspDebugScreenPrintf("X: Onayla\n");

            if (pressed & PSP_CTRL_UP)
                menu = (menu + 2) % 3;

            if (pressed & PSP_CTRL_DOWN)
                menu = (menu + 1) % 3;

            if (pressed & PSP_CTRL_CROSS) {
                if (menu == 2)
                    break;

                score1 = 0;
                score2 = 0;
                playing = 1;
            }
        } else {
            pspDebugScreenPrintf("PSP FUTBOL - MAC\n\n");
            pspDebugScreenPrintf("Galatasaray  -  Fenerbahce\n\n");
            pspDebugScreenPrintf("Skor: %d - %d\n\n",
                score1, score2);

            pspDebugScreenPrintf("X: Ev sahibi golu\n");
            pspDebugScreenPrintf("O: Deplasman golu\n");
            pspDebugScreenPrintf("START: Menuye don\n");

            if (pressed & PSP_CTRL_CROSS)
                score1++;

            if (pressed & PSP_CTRL_CIRCLE)
                score2++;

            if (pressed & PSP_CTRL_START)
                playing = 0;
        }

        sceDisplayWaitVblankStart();
    }

    sceKernelExitGame();
    return 0;
}
