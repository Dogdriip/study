// test bench
// 2018112749 전현승
module t_sync_bcd_counter;
  reg t_TQ1, t_Clk, t_Rst_b;  // 카운터 모듈에 들어갈 input
  wire t_Q8, t_Q4, t_Q2, t_Q1;  // 카운터 모듈에서 나올 output

  // 카운터 모듈 instantiate
  sync_bcd_counter M (t_Q8, t_Q4, t_Q2, t_Q1, t_TQ1, t_Clk, t_Rst_b);

  always #10 t_Clk = ~t_Clk;  // 모듈에 들어가는 Clk을 10ns 단위로 toggle

  initial begin
    // 모든 변수 변경 내역을 dump.vcd에 저장
    $dumpfile("dump.vcd");
    $dumpvars(0, t_sync_bcd_counter);

    t_TQ1 = 1'b1;  // 모듈의 1번 flip flop (F1)의 input : 항상 1
    t_Clk = 1'b0;  // Clk 초기값 설정
    t_Rst_b = 1'b0;  
    #5 t_Rst_b = 1'b1;  // Rst 초기값 0 설정 후, Clk 사이클 시작 전에 1로 변경
  end

  initial #400 $finish;  // 실행 400ns 경과 후 종료

  initial begin
    // 모듈 output 바뀔 때마다 output 비트 4개 출력 (Q8, Q4, Q2, Q1 순서)
    $monitor ("%b %b %b %b", t_Q8, t_Q4, t_Q2, t_Q1);
  end
endmodule
