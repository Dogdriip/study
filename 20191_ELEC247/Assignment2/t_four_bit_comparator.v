module t_four_bit_comparator;
  reg [3:0] t_A, t_B;
  wire t_A_lt_B, t_A_gt_B, t_A_eq_B;

  four_bit_comparator M(t_A_lt_B, t_A_gt_B, t_A_eq_B, t_A, t_B);
  
  initial begin
    t_A = 4'b1010;
    t_B = 4'b0111;
    #10
    t_A = 4'b0001;
    t_B = 4'b0100;
    #10
    t_A = 4'b0000;
    t_B = 4'b0000;
  end

  initial begin
    $monitor ("A = %b, B = %b --> A_lt_B = %b, A_gt_B = %b, A_eq_B = %b", t_A, t_B, t_A_lt_B, t_A_gt_B, t_A_eq_B);
  end


endmodule

