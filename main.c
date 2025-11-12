/*
 * PSP Hello World Application
 * Displays "Hello World" on the PSP screen
 */

#include <pspkernel.h>
#include <pspdebug.h>
#include <pspdisplay.h>
#include <pspctrl.h>

PSP_MODULE_INFO("HelloWorld", 0, 1, 0);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);

/* Define printf to use pspDebugScreenPrintf */
#define printf pspDebugScreenPrintf

/* Exit callback */
int exit_callback(int arg1, int arg2, void *common)
{
    sceKernelExitGame();
    return 0;
}

/* Callback thread */
int CallbackThread(SceSize args, void *argp)
{
    int cbid;

    cbid = sceKernelCreateCallback("Exit Callback", exit_callback, NULL);
    sceKernelRegisterExitCallback(cbid);

    sceKernelSleepThreadCB();

    return 0;
}

/* Sets up the callback thread and returns its thread id */
int SetupCallbacks(void)
{
    int thid = 0;

    thid = sceKernelCreateThread("update_thread", CallbackThread, 0x11, 0xFA0, 0, 0);
    if(thid >= 0)
    {
        sceKernelStartThread(thid, 0, 0);
    }

    return thid;
}

int main(void)
{
    SceCtrlData pad;
    
    /* Set up callbacks */
    SetupCallbacks();

    /* Initialize the debug screen */
    pspDebugScreenInit();

    /* Clear screen and set cursor to top-left */
    pspDebugScreenClear();
    pspDebugScreenSetXY(0, 0);

    /* Display Hello World message */
    printf("\n\n");
    printf("  =====================================\n");
    printf("       PSP HOMEBREW - HELLO WORLD     \n");
    printf("  =====================================\n\n");
    printf("  Hello World!\n\n");
    printf("  Welcome to PSP homebrew development!\n\n");
    printf("  Press X to exit.\n\n");
    printf("  =====================================\n");

    /* Main loop */
    while(1)
    {
        /* Read controller input */
        sceCtrlReadBufferPositive(&pad, 1);

        /* Check if X button is pressed */
        if(pad.Buttons & PSP_CTRL_CROSS)
        {
            break;
        }

        /* Wait a bit before next check */
        sceDisplayWaitVblankStart();
    }

    /* Exit */
    sceKernelExitGame();
    return 0;
}
