#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <getopt.h>

#include "RGKR.h"
#include "UartSet.h"

char *RegisterName = NULL;
int i = 0;

char* device = "/dev/ttyUSB0";

static void display_help(void)
{
	printf("Usage: ./a.out [OPTION]\n"
			"\n"
			"  -h, --help\n"
			"  -p, --port        Port (Default /dev/ttyUSB0)\n"
            "  -r  --RegName     ACTE_IM_L1  (must be specified) \n" 
            "                    ACTE_IM_L2 \n"
            "                    ACTE_IM_L3 \n"
            "                    INDE_L1 \n"
            "                    INDE_L2 \n"
            "                    INDE_L3 \n"
            "                    CAPE_L1 \n"
            "                    CAPE_L2 \n"
            "                    CAPE_L3 \n"
            "                    ACTPWR_L1 \n"
            "                    ACTPWR_L2 \n"
            "                    ACTPWR_L3 \n"
            "                    INDPWR_L1 \n"
            "                    INDPWR_L2 \n"
            "                    INDPWR_L3 \n"
            "                    CAPPWR_L1 \n"
            "                    CAPPWR_L2 \n"
            "                    CAPPWR_L3 \n"
            "                    CosPhi_L1 \n"
            "                    CosPhi_L2 \n"
            "                    CosPhi_L3 \n"
            "                    REACHIND \n"
            "                    REACHCAP \n"
            "                    THDL1\n"
            "                    THDL2\n"
            "                    THDL3\n"
            "                    VOLT_L1\n"
            "                    VOLT_L2\n"
            "                    VOLT_L3\n"
            "                    CURRENT_L1\n"
            "                    CURRENT_L2\n"
            "                    CURRENT_L3\n"
            
            "\n"
	      );
}

static void process_opt(int argc, char * argv[])
{
    for (;;) {

		int option_index = 0;
		static const char *short_options = "hp:r:";

		static const struct option long_options[] = {
			{"help", no_argument, 0, 0},
			{"port", optional_argument, 0, 'p'},
            {"RegName", required_argument, 0, 'r'},
			
			{0,0,0,0},
		};

		int c = getopt_long(argc, argv, short_options,
				long_options, &option_index);

		if (c == EOF) {
			break;
		}

		switch (c) {
		case 0:
		case 'h':
			display_help();
			exit(0);
			break;
		case 'p':
			device = optarg;
			break;
		case 'r':
			RegisterName = optarg;
			break;
        }
    }
}


int main(int argc, char *argv[])
{
    process_opt(argc, argv);
    
    if(!RegisterName)
    {
        fprintf(stderr, "ERROR: RegisterName argument required\n");
        display_help();
        exit(0);
    }

    else
    {
        while(RGKR_Params_Table[i].RegName != 0)
        {
            if(strcmp(RegisterName, RGKR_Params_Table[i].RegName) == 0)
            {
                break;
            }

            i++;
        }
    }

    int fd = open_serial_port(device, baudrate);

    if (fd < 0) { return 1; }

    write_port(fd, (uint8_t *) RGKR_Params_Table[i].RequestArray, sizeof(RGKR_Params_Table[0].RequestArray));

    read_port(fd, RGKR_Uart_Params.buffer, sizeof(RGKR_Uart_Params.buffer));

    printf("Calculated Value of %s is : %f \n",RGKR_Params_Table[i].RegName,
     ParseProcess((char*)RGKR_Uart_Params.buffer, RGKR_Uart_Params.idx, i));

    close(fd);

    return 0;

}


