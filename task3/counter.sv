//Counter increments a count everytime positive edge of clk is seen, en must also be true
//counter resets if rst is true
module counter#(
    parameter WIDTH = 8
)(

 // interface signals
 input logic clk, //input into counter block: clock
 input logic rst, //input into counter block: reset
 input logic en, //input into counter block: counter enable
 output logic [WIDTH-1:0] count //count output
);

always_ff @ (posedge clk) //This is dependent on clk edge, so conditions only check every positive clk edge, so as we can control
//clk edge impulse by enabling flag and as flag is only enabled when clicked then we can do 1 clock pulses
//Thus count iterates only when clk cycle happens and that is when flag is enabled

    if (rst) count <= {WIDTH{1'b0}}; //so if rst is true (1) then count = 0
    else count<= count + {{WIDTH-1{1'b0}}, en};
    /*else begin
        if (en) count<= count + {{WIDTH-1{1'b0}}, en};
        else count<= count - {{WIDTH-1{1'b0}}, !en}; //count<= count; is if we want to just increment 
    end*/
    //count<= count + {{WIDTH-1{1'b0}}, en}; //count increments by 1 as long as en is also true

endmodule
