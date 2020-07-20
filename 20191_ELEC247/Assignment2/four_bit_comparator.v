module four_bit_comparator(A_lt_B, A_gt_B, A_eq_B, A, B);
  output A_lt_B, A_gt_B, A_eq_B;
  input [3:0] A, B;
  wire A3n, B3n, A2n, B2n, A1n, B1n, A0n, B0n, x01, x02, x11, x12, x21, x22, x31, x32, x0, x1, x2, x3, w1, w2, w3, w4, w5, w6;

  not 
    G1(A3n, A[3]),
    G2(B3n, B[3]),
    G3(A2n, A[2]),
    G4(B2n, B[2]),
    G5(A1n, A[1]),
    G6(B1n, B[1]),
    G7(A0n, A[0]),
    G8(B0n, B[0]);
  and
    G9(x01, A[0], B0n),
    G10(x02, A0n, B[0]),
    G11(x11, A[1], B1n),
    G12(x12, A1n, B[1]),
    G13(x21, A[2], B2n),
    G14(x22, A2n, B[2]),
    G15(x31, A[3], B3n),
    G16(x32, A3n, B[3]);
  nor
    G17(x0, x01, x02),
    G18(x1, x11, x12),
    G19(x2, x21, x22),
    G20(x3, x31, x32);
  and
    G21(A_eq_B, x0, x1, x2, x3),
    G22(w1, x01, x1, x2, x3),
    G23(w2, x02, x1, x2, x3),
    G24(w3, x11, x2, x3),
    G25(w4, x12, x2, x3),
    G26(w5, x21, x3),
    G27(w6, x22, x3);
  or
    G28(A_gt_B, w1, w3, w5, x31),
    G29(A_lt_B, w2, w4, w6, x32);

endmodule
