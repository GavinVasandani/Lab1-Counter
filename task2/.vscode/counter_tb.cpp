//Testbench for testing counter

#include "Vcounter.h"
#include "verilated.h"
#include "verilated_vcd_c.h"
#include "vbuddy.cpp"

    int main(int argc, char **argv, char**env) {
        int i;
        int clk;
        int icnt = 0;

    Verilated::commandArgs(argc, argv);
    //Initiate instance of vcounter, so a module() is a class and we're creating instance of it
    Vcounter* top = new Vcounter; //so pointer pointing to instance of Vcounter
    //init trace dump
    //code below starts signal tracing and tfp is an object of the signal tracing of the current object(vcounter)
    //and this data is dumped to file counter.vcd
    Verilated::traceEverOn(true);
    VerilatedVcdC* tfp = new VerilatedVcdC;
    top->trace (tfp,99);
    tfp->open ("counter.vcd");

    //initialize vbuddy
    if(vbdOpen()!=1) return(-1);
    vbdHeader("Lab 1: Counter");

    //intiailize initial simulation inputs
    top->clk = 1; //Vcounter input values are clk, rst, en and initialized to different values
    top->rst = 1;
    top->en = 0;

    //run simulation for certain number of clock cycles
    for (i=0; i<300; i++) {
        if(top->count==9 && icnt<=3) { //in C++ you can use ints instead of binary form N'B
            top->en = 0;
            icnt++; 
        }
        else if (icnt==4) {
            top->en = 1;
            icnt = 0;
        }
        //i is current clock cycle in overall duration of simulation (given in clock cycles)
        //but as we need clk cycle to iterate between 0,1 then:
        for (clk=0; clk<2; clk++) {
            tfp->dump (2*i+clk);
            top->clk = !top->clk;
            top->eval ();
        }

        //Send count value to be displayed on 7-seg display every cycle on vbuddy screen:
        vbdHex(4, (int(top->count) >> 16) & 0xF);
        vbdHex(3, (int(top->count) >> 8) & 0xF);
        vbdHex(2, (int(top->count) >> 4) & 0xF);
        vbdHex(1, (int(top->count) & 0xF);
        vbdCycle(i+1);

        top->rst = (i<2) | (i==15); //set rst parameter to be dependen on OR statement so if current clock cycle is <2 or ==15 then = 1 
        //so reset
        //else let rst = 0; 
        top->en = (i>4); //so doing (i>4) checks whether i>4 and outputs a bool so if >4 then en = 1 so count increment starts
        if (Verilated::gotFinish()) exit(0);
    }
    vbdClose();
    tfp->close();
    exit(0);
}