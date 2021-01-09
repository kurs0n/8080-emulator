#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

typedef struct ConditionCodes {    
    uint8_t    z:1;    
    uint8_t    s:1;    
    uint8_t    p:1;    
    uint8_t    cy:1;    
    uint8_t    ac:1;    
    uint8_t    pad:3;    
   } ConditionCodes;    

typedef struct State8080 {    
    uint8_t    a;    
    uint8_t    b;    
    uint8_t    c;    
    uint8_t    d;    
    uint8_t    e;    
    uint8_t    h;    
    uint8_t    l;    
    uint16_t    sp;    
    uint16_t    pc;    
    uint8_t     *memory;    
    struct      ConditionCodes      cc;    
    uint8_t     int_enable;    
   } State8080;    

int parity(int x, int size)
{
	int i;
	int p = 0;
	x = (x & ((1<<size)-1));
	for (i=0; i<size; i++)
	{
		if (x & 0x1) p++;
		x = x >> 1;
	}
	return (0 == (p & 0x1));
} //https://pl.wikipedia.org/wiki/Flaga_parzysto%C5%9Bci 


void UnimplementedInstruction(State8080* state)    
{    
    //pc will have advanced one, so undo that    
    printf ("Error: Unimplemented instruction\n");    
    exit(1);    
}    


int Emulate8080(State8080* state){
    unsigned char *opcode = &state->memory[state->pc];    
    switch(*opcode)    
    {    
        case 0x00: {
            break;
        }
        case 0x01: {
            state->b = opcode[2];
            state->c = opcode[1];
            state->pc += 2;
            break;
        }
        case 0xc3:{

        }
        case 0x80:{
            uint16_t answer = (uint16_t) state->a + (uint16_t) state->b;

            // Zero flag: if the result is zero,    
            // set the flag to zero    
            // else clear the flag  
            if((answer & 0xff) == 0){ // make 8 bit answer
                state->cc.z = 1;
            }
            else {
                state->cc.z = 0;
            }

            // Sign flag: if bit 7 is set,    
            // set the sign flag    
            // else clear the sign flag  
            if(answer & 0x80){
                state->cc.s = 1;
            }
            else {
                state->cc.s = 0;
            }

            // Carry flag    
            if (answer > 0xff)    
                state->cc.cy = 1;    
            else    
                state->cc.cy = 0;  

            state->cc.p = parity((answer & 0xff),8);

            state->a = (answer & 0xff);
            
            break;
        }
        case 0x81:{
             uint16_t answer = (uint16_t) state->a + (uint16_t) state->c;

            // Zero flag: if the result is zero,    
            // set the flag to zero    
            // else clear the flag  
            if((answer & 0xff) == 0){ // make 8 bit answer
                state->cc.z = 1;
            }
            else {
                state->cc.z = 0;
            }

            // Sign flag: if bit 7 is set,    
            // set the sign flag    
            // else clear the sign flag  
            if(answer & 0x80){
                state->cc.s = 1;
            }
            else {
                state->cc.s = 0;
            }

            // Carry flag    
            if (answer > 0xff)    
                state->cc.cy = 1;    
            else    
                state->cc.cy = 0;  

            state->cc.p = parity((answer & 0xff),8);

            state->a = (answer & 0xff);
            
            break;
        }
        case 0x82:{
            uint16_t answer = (uint16_t) state->a + (uint16_t) state->d;

            // Zero flag: if the result is zero,    
            // set the flag to zero    
            // else clear the flag  
            if((answer & 0xff) == 0){ // make 8 bit answer
                state->cc.z = 1;
            }
            else {
                state->cc.z = 0;
            }

            // Sign flag: if bit 7 is set,    
            // set the sign flag    
            // else clear the sign flag  
            if(answer & 0x80){
                state->cc.s = 1;
            }
            else {
                state->cc.s = 0;
            }

            // Carry flag    
            if (answer > 0xff)    
                state->cc.cy = 1;    
            else    
                state->cc.cy = 0;  

            state->cc.p = parity((answer & 0xff),8);

            state->a = (answer & 0xff);
            
            break;
        }
        case 0x83:{
            uint16_t answer = (uint16_t) state->a + (uint16_t) state->e;

            // Zero flag: if the result is zero,    
            // set the flag to zero    
            // else clear the flag  
            if((answer & 0xff) == 0){ // make 8 bit answer
                state->cc.z = 1;
            }
            else {
                state->cc.z = 0;
            }

            // Sign flag: if bit 7 is set,    
            // set the sign flag    
            // else clear the sign flag  
            if(answer & 0x80){
                state->cc.s = 1;
            }
            else {
                state->cc.s = 0;
            }

            // Carry flag    
            if (answer > 0xff)    
                state->cc.cy = 1;    
            else    
                state->cc.cy = 0;  

            state->cc.p = parity((answer & 0xff),8);

            state->a = (answer & 0xff);
            
            break;
        }
        case 0x84:{
            uint16_t answer = (uint16_t) state->a + (uint16_t) state->h;

            // Zero flag: if the result is zero,    
            // set the flag to zero    
            // else clear the flag  
            if((answer & 0xff) == 0){ // make 8 bit answer
                state->cc.z = 1;
            }
            else {
                state->cc.z = 0;
            }

            // Sign flag: if bit 7 is set,    
            // set the sign flag    
            // else clear the sign flag  
            if(answer & 0x80){
                state->cc.s = 1;
            }
            else {
                state->cc.s = 0;
            }

            // Carry flag    
            if (answer > 0xff)    
                state->cc.cy = 1;    
            else    
                state->cc.cy = 0;  

            state->cc.p = parity((answer & 0xff),8);

            state->a = (answer & 0xff); // conversion to 8 bit
            
            break;
        }
        case 0x85:{
            uint16_t answer = (uint16_t) state->a + (uint16_t) state->l;

            // Zero flag: if the result is zero,    
            // set the flag to zero    
            // else clear the flag  
            if((answer & 0xff) == 0){ // make 8 bit answer
                state->cc.z = 1;
            }
            else {
                state->cc.z = 0;
            }

            // Sign flag: if bit 7 is set,    
            // set the sign flag    
            // else clear the sign flag  
            if(answer & 0x80){
                state->cc.s = 1;
            }
            else {
                state->cc.s = 0;
            }

            // Carry flag    
            if (answer > 0xff)    
                state->cc.cy = 1;    
            else    
                state->cc.cy = 0;  

            state->cc.p = parity((answer & 0xff),8);

            state->a = (answer & 0xff);
            
            break;
        }
        case 0x86:{
            uint16_t offset = ((state->h<<8)|(state->l)); // most significant byte we push to the left and connect via |
            uint16_t answer = (uint16_t) state->a + state->memory[offset];

            // Zero flag: if the result is zero,    
            // set the flag to zero    
            // else clear the flag  
            if((answer & 0xff) == 0){ // make 8 bit answer
                state->cc.z = 1;
            }
            else {
                state->cc.z = 0;
            }

            // Sign flag: if bit 7 is set,    
            // set the sign flag    
            // else clear the sign flag  
            if(answer & 0x80){
                state->cc.s = 1;
            }
            else {
                state->cc.s = 0;
            }

            // Carry flag    
            if (answer > 0xff)    
                state->cc.cy = 1;    
            else    
                state->cc.cy = 0;  

            state->cc.p = parity((answer & 0xff),8);

            state->a = (answer & 0xff);
            
            break;
        }
        case 0x87:{
            uint16_t answer = (uint16_t) state->a + (uint16_t) state->a;

            // Zero flag: if the result is zero,    
            // set the flag to zero    
            // else clear the flag  
            if((answer & 0xff) == 0){ // make 8 bit answer
                state->cc.z = 1;
            }
            else {
                state->cc.z = 0;
            }

            // Sign flag: if bit 7 is set,    
            // set the sign flag    
            // else clear the sign flag  
            if(answer & 0x80){
                state->cc.s = 1;
            }
            else {
                state->cc.s = 0;
            }

            // Carry flag    
            if (answer > 0xff)    
                state->cc.cy = 1;    
            else    
                state->cc.cy = 0;  

            state->cc.p = parity((answer & 0xff),8);

            state->a = (answer & 0xff);
            
            break;
        }
        case 0xc6:{
            uint16_t answer = (uint16_t) state->a + (uint16_t)opcode[1];

            // Zero flag: if the result is zero,    
            // set the flag to zero    
            // else clear the flag  
            if((answer & 0xff) == 0){ // make 8 bit answer
                state->cc.z = 1;
            }
            else {
                state->cc.z = 0;
            }

            // Sign flag: if bit 7 is set,    
            // set the sign flag    
            // else clear the sign flag  
            if(answer & 0x80){
                state->cc.s = 1;
            }
            else {
                state->cc.s = 0;
            }

            // Carry flag    
            if (answer > 0xff)    
                state->cc.cy = 1;    
            else    
                state->cc.cy = 0;  

            state->cc.p = parity((answer & 0xff),8);

            state->a = (answer & 0xff);
            
            state->pc+=1;

            break;
        }
        case 0xce:{
            uint16_t answer = (uint16_t) state->a + (uint16_t) opcode[1] + (uint16_t) state->cc.cy;

            // Zero flag: if the result is zero,    
            // set the flag to zero    
            // else clear the flag  
            if((answer & 0xff) == 0){ // make 8 bit answer
                state->cc.z = 1;
            }
            else {
                state->cc.z = 0;
            }

            // Sign flag: if bit 7 is set,    
            // set the sign flag    
            // else clear the sign flag  
            if(answer & 0x80){
                state->cc.s = 1;
            }
            else {
                state->cc.s = 0;
            }

            // Carry flag    
            if (answer > 0xff)    
                state->cc.cy = 1;    
            else    
                state->cc.cy = 0;  

            state->cc.p = parity((answer & 0xff),8);

            state->a = (answer & 0xff);
            
            state->pc+=1;   

            break;
        }
        case 0x88:{
             uint16_t answer = (uint16_t) state->a + (uint16_t) state->b + (uint16_t) state->cc.cy; 

            // Zero flag: if the result is zero,    
            // set the flag to zero    
            // else clear the flag  
            if((answer & 0xff) == 0){ // make 8 bit answer
                state->cc.z = 1;
            }
            else {
                state->cc.z = 0;
            }

            // Sign flag: if bit 7 is set,    
            // set the sign flag    
            // else clear the sign flag  
            if(answer & 0x80){
                state->cc.s = 1;
            }
            else {
                state->cc.s = 0;
            }

            // Carry flag    
            if (answer > 0xff)    
                state->cc.cy = 1;    
            else    
                state->cc.cy = 0;  

            state->cc.p = parity((answer & 0xff),8);

            state->a = (answer & 0xff);
            
            break;
        }
        case 0x89:{
             uint16_t answer = (uint16_t) state->a + (uint16_t) state->c + (uint16_t) state->cc.cy;

            // Zero flag: if the result is zero,    
            // set the flag to zero    
            // else clear the flag  
            if((answer & 0xff) == 0){ // make 8 bit answer
                state->cc.z = 1;
            }
            else {
                state->cc.z = 0;
            }

            // Sign flag: if bit 7 is set,    
            // set the sign flag    
            // else clear the sign flag  
            if(answer & 0x80){
                state->cc.s = 1;
            }
            else {
                state->cc.s = 0;
            }

            // Carry flag    
            if (answer > 0xff)    
                state->cc.cy = 1;    
            else    
                state->cc.cy = 0;  

            state->cc.p = parity((answer & 0xff),8);

            state->a = (answer & 0xff);
            
            break;
        }
        case 0x8a:{
            uint16_t answer = (uint16_t) state->a + (uint16_t) state->d + (uint16_t) state->cc.cy;

            // Zero flag: if the result is zero,    
            // set the flag to zero    
            // else clear the flag  
            if((answer & 0xff) == 0){ // make 8 bit answer
                state->cc.z = 1;
            }
            else {
                state->cc.z = 0;
            }

            // Sign flag: if bit 7 is set,    
            // set the sign flag    
            // else clear the sign flag  
            if(answer & 0x80){
                state->cc.s = 1;
            }
            else {
                state->cc.s = 0;
            }

            // Carry flag    
            if (answer > 0xff)    
                state->cc.cy = 1;    
            else    
                state->cc.cy = 0;  

            state->cc.p = parity((answer & 0xff),8);

            state->a = (answer & 0xff);
            
            break;
        }
        case 0x8b:{
            uint16_t answer = (uint16_t) state->a + (uint16_t) state->e + (uint16_t) state->cc.cy;

            // Zero flag: if the result is zero,    
            // set the flag to zero    
            // else clear the flag  
            if((answer & 0xff) == 0){ // make 8 bit answer
                state->cc.z = 1;
            }
            else {
                state->cc.z = 0;
            }

            // Sign flag: if bit 7 is set,    
            // set the sign flag    
            // else clear the sign flag  
            if(answer & 0x80){
                state->cc.s = 1;
            }
            else {
                state->cc.s = 0;
            }

            // Carry flag    
            if (answer > 0xff)    
                state->cc.cy = 1;    
            else    
                state->cc.cy = 0;  

            state->cc.p = parity((answer & 0xff),8);

            state->a = (answer & 0xff);
            
            break;
        }
        case 0x8c:{
            uint16_t answer = (uint16_t) state->a + (uint16_t) state->h + (uint16_t) state->cc.cy;

            // Zero flag: if the result is zero,    
            // set the flag to zero    
            // else clear the flag  
            if((answer & 0xff) == 0){ // make 8 bit answer
                state->cc.z = 1;
            }
            else {
                state->cc.z = 0;
            }

            // Sign flag: if bit 7 is set,    
            // set the sign flag    
            // else clear the sign flag  
            if(answer & 0x80){
                state->cc.s = 1;
            }
            else {
                state->cc.s = 0;
            }

            // Carry flag    
            if (answer > 0xff)    
                state->cc.cy = 1;    
            else    
                state->cc.cy = 0;  

            state->cc.p = parity((answer & 0xff),8);

            state->a = (answer & 0xff);
            
            break;
        }
        case 0x8d:{
            uint16_t answer = (uint16_t) state->a + (uint16_t) state->l + (uint16_t) state->cc.cy;

            // Zero flag: if the result is zero,    
            // set the flag to zero    
            // else clear the flag  
            if((answer & 0xff) == 0){ // make 8 bit answer
                state->cc.z = 1;
            }
            else {
                state->cc.z = 0;
            }

            // Sign flag: if bit 7 is set,    
            // set the sign flag    
            // else clear the sign flag  
            if(answer & 0x80){
                state->cc.s = 1;
            }
            else {
                state->cc.s = 0;
            }

            // Carry flag    
            if (answer > 0xff)    
                state->cc.cy = 1;    
            else    
                state->cc.cy = 0;  

            state->cc.p = parity((answer & 0xff),8);

            state->a = (answer & 0xff);
            
            break;
        }
        case 0x8e:{
            uint16_t offset = ((state->h<<8)|(state->l));
            uint16_t answer = (uint16_t) state->a + state->memory[offset] + (uint16_t) state->cc.cy;

            // Zero flag: if the result is zero,    
            // set the flag to zero    
            // else clear the flag  
            if((answer & 0xff) == 0){ // make 8 bit answer
                state->cc.z = 1;
            }
            else {
                state->cc.z = 0;
            }

            // Sign flag: if bit 7 is set,    
            // set the sign flag    
            // else clear the sign flag  
            if(answer & 0x80){
                state->cc.s = 1;
            }
            else {
                state->cc.s = 0;
            }

            // Carry flag    
            if (answer > 0xff)    
                state->cc.cy = 1;    
            else    
                state->cc.cy = 0;  

            state->cc.p = parity((answer & 0xff),8);

            state->a = (answer & 0xff);
            
            break;
        }
        case 0x8f:{
            uint16_t answer = (uint16_t) state->a + (uint16_t) state->a + (uint16_t) state->cc.cy;

            // Zero flag: if the result is zero,    
            // set the flag to zero    
            // else clear the flag  
            if((answer & 0xff) == 0){ // make 8 bit answer
                state->cc.z = 1;
            }
            else {
                state->cc.z = 0;
            }

            // Sign flag: if bit 7 is set,    
            // set the sign flag    
            // else clear the sign flag  
            if(answer & 0x80){
                state->cc.s = 1;
            }
            else {
                state->cc.s = 0;
            }

            // Carry flag    
            if (answer > 0xff)    
                state->cc.cy = 1;    
            else    
                state->cc.cy = 0;  

            state->cc.p = parity((answer & 0xff),8);

            state->a = (answer & 0xff);
            
            break;
        }
        case 0x90:{
            uint16_t answer = (uint16_t) state->a - (uint16_t) state->b;

            // Zero flag: if the result is zero,    
            // set the flag to zero    
            // else clear the flag  
            if((answer & 0xff) == 0){ // make 8 bit answer
                state->cc.z = 1;
            }
            else {
                state->cc.z = 0;
            }

            // Sign flag: if bit 7 is set,    
            // set the sign flag    
            // else clear the sign flag  
            if(answer & 0x80){
                state->cc.s = 1;
            }
            else {
                state->cc.s = 0;
            }

            // Carry flag    
            if (answer > 0xff)    
                state->cc.cy = 1;    
            else    
                state->cc.cy = 0;  

            state->cc.p = parity((answer & 0xff),8);

            state->a = (answer & 0xff);
            
            break;        
        }
    }    
    state->pc+=1;  //for the opcode    
}


int main(){
    FILE*  f= fopen("./rom/invaders.h","r");
    
    //Get the file size and read it into a memory buffer    
    fseek(f, 0L, SEEK_END);    
    int fsize = ftell(f);    
    fseek(f, 0L, SEEK_SET);   

    unsigned char *buffer = malloc(fsize);
    fread(buffer,fsize,1,f);
    fclose(f);
    struct State8080 state;
    state.memory = buffer;
    state.pc = 0;
    while(state.pc < fsize){
        Emulate8080(&state);
    }
    return 0;
}