\\https://unix.stackexchange.com/questions/224125/linux-performance-measurements-using-proc-vmstat

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/sysinfo.h>

int main(int argc, char **argv)
{
    struct sysinfo si;
    sysinfo (&si);
    const double xdt = 1024;
    float  pagein,pageout, oldvalin = 0, oldvalout = 0, res;
    for(;;) {
        FILE *fp=fopen("/proc/vmstat","r");
        char  tmp[256];
        char  subbuff[256];
        while(fp!=NULL && fgets(tmp, sizeof(tmp),fp)!=NULL)
        {
            if (strstr(tmp, "pgpgin")) {
                memcpy( subbuff, &tmp[7], 40);
                subbuff[40] = '\0';
                pagein = atoi(subbuff);
            }
            if (strstr(tmp, "pgpgout")) {
                printf("\n\n%s", tmp);
                memcpy( subbuff, &tmp[7], 40);
                subbuff[40] = '\0';
                pageout = atoi(subbuff);
            }
        }
        printf("Res : %.2f \t %.2f",pagein-oldvalin,pageout-oldvalout);
        oldvalin = pagein;
        oldvalout = pageout;
        if(fp!=NULL) fclose(fp);
        sleep(1);
    }
}
