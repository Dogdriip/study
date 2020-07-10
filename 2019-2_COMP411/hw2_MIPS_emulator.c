// mips_sim.c

#include <stdio.h>
#include <stdlib.h>

////////////////////// some definitions
#define FALSE 0
#define TRUE 1
// opcode
#define RTYPE 0x00  // add, jr - distinguished by funct
#define ADDI 0x08
#define JAL 0x03
#define J 0x02
#define LW 0x23
#define SW 0x2b
#define SLTI 0x0a
#define BEQ 0x04
// funct
#define ADD_FUNCT 0x20
#define JR_FUNCT 0x08
////////////////////// some definitions

//clock cycles
long long cycles = 0;

// registers
int regs[32];

// program counter
unsigned long pc = 0;

// memory
#define INST_MEM_SIZE 32*1024
#define DATA_MEM_SIZE 32*1024
unsigned long inst_mem[INST_MEM_SIZE]; //instruction memory
unsigned long data_mem[DATA_MEM_SIZE]; //data memory

////////////////////// custom variables
// IF
unsigned int curr_inst;  // current instruction
// ID

// int opcode, rs, rt, rd, imm, funct, j_address;
int opcode, rs, rt, rd, funct, j_address;
short int imm;  // 16bit

int rs_data, rt_data;  // Read data 1, 2
// EX
int res;  // ALU result
// MEM
int wb_data;  // data to write-back

////////////////////// custom variables

//misc. function
int init(char* filename);
void print_cycles();
void print_reg();
void print_pc();

// implement funcs
void fetch();
void decode();
void exe();
void mem();
void wb();
void update_pc();

int main(int ac, char *av[]) {
	if (ac != 2) {
		printf("./mips_sim filename\n");
        return -1;
	}
	
	char done = FALSE;
	if (init(av[1]) != 0)
        return -1;
	
	////////////////////// main loop
	while (!done) {
		curr_inst = 0;
		opcode = rs = rt = rd = imm = funct = j_address = 0;
		rs_data = rt_data = 0;
		res = 0;
		wb_data = 0;

		fetch();     //fetch an instruction from the instruction memory
		decode();    //decode the instruction and read data from register file
		exe();       //perform an appropriate operation 
		mem();       //access the data memory
		wb();        //write result of arithmetic operation or data read from the data memory to register file
		update_pc(); //update the pc to the address of the next instruction

		cycles++;    //increase clock cycle

		print_cycles();  //print clock cycles
		print_pc();		 //print pc
		print_reg();	 //print registers

        // check the exit condition 
		if (regs[9] == 10)  //if value in $t1 is 10, finish the simulation
			done = TRUE;
	}
	////////////////////// main loop

	return 0;
}

/* initialize all datapat elements
//fill the instruction and data memory
//reset the registers
*/
int init(char* filename) {
	FILE* fp = fopen(filename, "r");
	int i;
	long inst;

	if (fp == NULL) {
		fprintf(stderr, "Error opening file.\n");
		return -1;
	}

	/* fill instruction memory */
	i = 0;
	while (fscanf(fp, "%lx", &inst) == 1) {
		// printf("%lx\n", inst);
		inst_mem[i++] = inst;
	}
	/*reset the registers*/
	for (i = 0; i < 32; i++) {
		regs[i] = 0;
	}

	/*reset pc*/
	pc = 0;
    /*reset clock cycles*/
    cycles = 0;
    return 0;
}

void print_cycles(){
	printf("Clock cycle: %lld\n", cycles);
}

void print_pc() {
	printf("Program counter: %ld\n", pc);
}

void print_reg() {
	int i, j;
	for (i = 0; i < 4; i++) {
		printf("R%02d-R%02d:", i * 8, (i + 1) * 8 - 1);
		for (j = 0; j < 8; j++) {
			printf(" %08X", regs[i * 8 + j]);
		}
		printf("\n");
	}
	printf("\n");
}

////////////////////// implementations
void fetch() {
	curr_inst = inst_mem[pc / 4];
}

void decode() {
	opcode = ((curr_inst >> 26) & 0x3f);  // [31 - 26] 6
	rs = ((curr_inst >> 21) & 0x1f);  // [25 - 21] 5
	rt = ((curr_inst >> 16) & 0x1f);  // [20 - 16] 5
	rd = ((curr_inst >> 11) & 0x1f);  // [15 - 11] 5
	imm = ((curr_inst) & 0xffff);  // [15 - 0] 16
	funct = ((curr_inst) & 0x3f);  // [5 - 0] 6
	j_address = ((curr_inst) & 0x3ffffff);  // [25 - 0] 26

	rs_data = regs[rs];
	rt_data = regs[rt];
}

void exe() {  // ALU?
	if (opcode == RTYPE) {
		if (funct == ADD_FUNCT) {
			res = rs_data + rt_data;
		} else if (funct == JR_FUNCT) {
			res = rs_data;
		}
	} else if (opcode == ADDI || opcode == LW || opcode == SW) {
		res = rs_data + imm;
	} else if (opcode == JAL || opcode == J) {
		res = j_address;
	} else if (opcode == SLTI) {
		res = (rs_data < imm ? 1 : 0);
	} else if (opcode == BEQ) {
		res = rs_data - rt_data;
	}
}

void mem() {  // dm is only triggered at lw, sw
	if (opcode == LW) {
		wb_data = data_mem[res];
	} else if (opcode == SW) {
		data_mem[res] = rt_data;
	} else {
		wb_data = res;
	}
}

void wb() {
	if (opcode == RTYPE && funct == ADD_FUNCT) {  // add writes to rd
		regs[rd] = wb_data;
	} else if (opcode == ADDI || opcode == LW || opcode == SLTI) {  // others writes to rt
		regs[rt] = wb_data;
	} else if (opcode == JAL) {
		regs[31] = pc + 4;  // $ra:31
	}
}

void update_pc() {
	if (opcode == RTYPE && funct == JR_FUNCT) {
		pc = rs_data;
	} else if (opcode == J || opcode == JAL) {
		pc = (pc & 0xf0000000) + (j_address << 2);
	} else if (opcode == BEQ) {
		pc += 4;
		if (res == 0) {  // branch jump
			pc += (imm << 2);
		}
	} else {
		pc += 4;
	}
}
////////////////////// implementations
