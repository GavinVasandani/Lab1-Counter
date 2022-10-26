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

always_ff @ (posedge clk)
    if (rst) count <= {WIDTH{1'b0}}; //so if rst is true (1) then count = 0
    else count<= count + {{WIDTH-1{1'b0}}, en}; //count increments by 1 as long as en is also true

endmodule
