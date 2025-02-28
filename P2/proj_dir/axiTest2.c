/******************************************************************************
* Copyright (C) 2023 Advanced Micro Devices, Inc. All Rights Reserved.
* SPDX-License-Identifier: MIT
******************************************************************************/
/*
 * helloworld.c: simple test application
 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 */

#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"

#include "xparameters.h"
#include "xil_io.h"

#include "xgpio.h"
#include "sleep.h"

/************************** Constant Definitions *****************************/
#define GPIO_ONE  XPAR_XGPIO_0_BASEADDR 

/************************** Function Prototypes ******************************/

int SystemInit(void);

/************************** Variable Definitions *****************************/
XGpio Gpio1; /* The Instance of the GPIO Driver */


int main()
{
    init_platform();

    int Status = XST_SUCCESS;

    Status = SystemInit();

    //XGpio_DiscreteWrite(&Gpio1, LED_CHANNEL, 8);

    if(Status == XST_FAILURE)
    {
        print("System init failed\r\n");
        while(1);
    }

    ////print("Hello World\n\r");
    //print("Testing adder axi ip\r\n");
    //u32 val = Xil_In32(XPAR_MYIP_PONG_0_BASEADDR + (4 * 3));
    //xil_printf("Reading output: %d\r\n", val);

    //print("Performing addition Axi test\r\n");

    //Status = Xil_SecureOut32(XPAR_MYIP_PONG_0_BASEADDR + (4 * 0), 5);

    //if(Status == XST_FAILURE)
    //{
        //print("Address adder Write failed\r\n");
        //while(1);
    //}

    //Xil_Out32(XPAR_MYIP_PONG_0_BASEADDR + (4 * 1), 5);


    //val = Xil_In32(XPAR_MYIP_PONG_0_BASEADDR + (4 * 2));
    //xil_printf("Reading adder output: %d\r\n", val);



    //print("Starting G\r\n");

    //XGpio_SetDataDirection(&Gpio1, 0,1);
    print("Starting Game\r\n");
    sleep(1);

    const u8 GAME_START = 0b10000;

    Status = Xil_SecureOut32(XPAR_MYIP_PONG2_0_BASEADDR + (4 * 0), GAME_START);

    if(Status == XST_FAILURE)
    {
        print("Address pong Write failed\r\n");
        while(1);
    }

    //u32 paddle_data = XGpio_DiscreteRead(&Gpio1, 1);

    //xil_printf("Reading paddle data: %d\r\n", paddle_data);

    //while(1);

    while (1) {
        // read from gpio
        u32 paddle_data = XGpio_DiscreteRead(&Gpio1, 1);

        // write value to paddle register
        Xil_Out32(XPAR_MYIP_PONG2_0_BASEADDR + (4 * 0), GAME_START & paddle_data);

        //xil_printf("Reading paddle data: %d\r\n", paddle_data);

        //msleep(100);

        //while(1);


        //calculate where ball will be and place paddle at that location
        //...
        //Example links at bottom of code

    }

    print("Exited Error\r\n");
    cleanup_platform();
    return 0;
}





//////////////////////f(x)///////////
int SystemInit(void)
{
    int Status = XST_SUCCESS;

	Status = XGpio_Initialize(&Gpio1, GPIO_ONE);
	if (Status != XST_SUCCESS) {
		xil_printf("Gpio Initialization Failed\r\n");
		return XST_FAILURE;
	}
    
    Status = XGpio_SelfTest(&Gpio1);
	if (Status != XST_SUCCESS) {
		xil_printf("Gpio self-test Failed\r\n");
		return XST_FAILURE;
	}

    return Status;
}


//prediction links used for last semester
//https://stackoverflow.com/questions/55976268/how-can-you-pre-calculate-the-balls-trajectory-and-therefore-its-endpoint-in-the

//https://stackoverflow.com/questions/61139016/how-to-predict-trajectory-of-ball-in-a-ping-pong-game-for-ai-paddle-prediction
        //^The above is not AI, AI/ML is a big buzz word these days. 
        //^This is an algorithm with exact solution, not a probability.

//https://www.reddit.com/r/learnprogramming/comments/1ct96r/as3_predict_where_pong_ball_will_go/
