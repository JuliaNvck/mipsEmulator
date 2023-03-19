#include <iostream>
#include <string>
using namespace std;

__uint32_t PC = 0;
__uint32_t REGS[32];
__uint32_t IMEM[16384];
__uint32_t DMEM[16384];

int opcode;
int rs;
int rt;
int immediate;
int rd;
int shamt;
int funct;
int address;

//funcs
void add(int rd, int rs, int rt){
    REGS[rd] = REGS[rs] + REGS[rt];
}

void or1(int rd, int rs, int rt){
    REGS[rd] = REGS[rs] | REGS[rt];

}

void nor(int rd, int rs, int rt){
    REGS[rd] = !(REGS[rs] | REGS[rt]);

     
}

void and1(int rd, int rs, int rt){
    REGS[rd] = REGS[rs] & REGS[rt];

     
}

void sll(int rd, int rs, int shamt){
    REGS[rd] = REGS[rs] << shamt;

     
}

void addi(int rt, int rs, int immediate){
    REGS[rt] = REGS[rs] + immediate;
    
     
}

void andi(int rt, int rs, int immediate){
    REGS[rt] = REGS[rs] & immediate;
    
     
}

void ori(int rt, int rs, int immediate){
    REGS[rt] = REGS[rs] | immediate;
    
     
}

void beq(int rt, int rs, int branchAddr){
    if(REGS[rt] == REGS[rs]){
        PC = PC + 4 + branchAddr;
    }
    
     
}

void lw(int rt, int rs, int immediate){
    REGS[rt] = DMEM[REGS[rs] + immediate];
    
     
}

void sw(int rt, int rs, int immediate){
    DMEM[REGS[rs] + immediate] = REGS[rt];
    
     
}

void j(int address){
    PC = address;
}


//turn instruction into an integer, store instructions in imem, decode and execute instructions until exit syscall

//parseint: converts input string into uint32 put into imem
__uint32_t parseInstruction(string input){
    __uint32_t instruction = stoi(input);
    return instruction;
}

//execute function: 
//decode: first 6 bits, find opcode, 

void execute(uint32_t instruction){
    //update decode values
    opcode = (instruction & 0xFC000000) >> 26;
    
    
    if(opcode != 0){
        //not R type
        if(opcode == 0x2){
            //j
            address = (instruction & 0x03FFFFFF);
        }
        else{
            immediate = (instruction & 0x0000FFFF);
            rs = (instruction & 0x03E00000) >> 21;
            rt = (instruction & 0x001F0000) >> 16;
        }
        
    }
    
    
    
    else{
        rs = (instruction & 0x03E00000) >> 21;
        rt = (instruction & 0x001F0000) >> 16;
        rd = (instruction & 0x0000F800) >> 11;
        shamt = (instruction & 0x00007C00) >> 6;
        funct = (instruction & 0x0000003F);
    }

    //what to do
    if(opcode == 0){
        //R type
        if(funct == 0x20){
            cout << "add" << endl;
            add(rd, rs, rt);
        }
        else if (funct == 0x25){
            or1(rd, rs, rt);
        }
        else if (funct == 0x27){
            nor(rd, rs, rt);
        }
        else if(funct == 0x24){
            and1(rd, rs, rt);
        }
        else if(funct == 0x00){
            sll(rd, rs, shamt);
        }

    }
    else{
        if(opcode == 0x8){
            addi(rt, rs, immediate);
        }
        else if(opcode == 0xC){
            andi(rt, rs, immediate);
        }
        else if(opcode == 0xD){
            ori(rt, rs, immediate);
        }
        else if(opcode == 0x4){
            beq(rt, rs, immediate);
        }
        else if(opcode == 0x23){
            lw(rt, rs, immediate);
        }
        else if(opcode == 0x2B){
            sw(rt, rs, immediate);
        }
        else if(opcode == 0x2){
            j(address);
        }

    }

}

int main(){

    //while loop: check if imem[pc]
    //get user input w cin
    //imem[pc] = parseinstruction(input);

    //call execute and increment pc
        

    while(PC < 16384){
        cout << "enter input" << endl;
        string userInput;
        cin >> userInput;
        IMEM[PC] = parseInstruction(userInput);

        execute(IMEM[PC]);
        PC++;
        cout << REGS[11] << endl;
    }

    
    
    return 0;
}


