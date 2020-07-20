// BCD counter module
// 2018112749 전현승
module sync_bcd_counter(Q8, Q4, Q2, Q1, TQ1, Clk, Rst_b);
  output Q8, Q4, Q2, Q1;  // 카운터 모듈의 output (각 flip flop의 output)
  input TQ1, Clk, Rst_b;  // 카운터 모듈의 input (Clk : Clock, Rst_b : Reset)
  wire TQ2, TQ4, TQ8;  // 각 flip flop의 input (TQ1 : test bench에서 초기값 지정. TQ2, TQ4, TQ8 : 변수)
  wire Q8Q1, Q4Q2Q1;  // 게이트 정의에서 임시로 쓰일 변수

  // 임시변수 정의
  and
    G1(Q8Q1, Q8, Q1),
    G2(Q4Q2Q1, Q4, Q2, Q1);

  // 각 flip flop의 input 정의
  and
    G3(TQ2, ~Q8, Q1),  // TQ2 = Q8'Q1
    G4(TQ4, Q2, Q1);  // TQ4 = Q2Q1
  or G5(TQ8, Q8Q1, Q4Q2Q1);  // TQ8 = Q8Q1 + Q4Q2Q1

  // 회로에 사용되는 T flip flop 4개 (동기식 : 같은 Clk 공유)
  Toggle_flip_flop F1 (Q1, TQ1, Clk, Rst_b);
  Toggle_flip_flop F2 (Q2, TQ2, Clk, Rst_b);
  Toggle_flip_flop F3 (Q4, TQ4, Clk, Rst_b);
  Toggle_flip_flop F4 (Q8, TQ8, Clk, Rst_b);
endmodule


// flip flop module
module Toggle_flip_flop (Q, T, Clk, Rst_b);
	output Q;  // flip flop의 output
	input T, Clk, Rst_b;  // flip flop의 input
	reg Q;
	always @ (posedge Clk, negedge Rst_b)  // Clk이 0->1이거나 Rst_b가 1->0인 경우
	  if (Rst_b == 0) Q <= 1'b0;  // Rst_b가 0이 된 경우라면 flip flop의 output = 0
	  else if (T) Q <= ~Q;  // Clk이 0->1이면서 flip flop의 입력이 1이라면 output을 toggle
endmodule
