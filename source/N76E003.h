#ifndef N76E003_H
#define N76E003_H

/* Port Registers */
__sfr __at(0x80) P0;
__sfr __at(0x90) P1;
__sfr __at(0xA0) P2;
__sfr __at(0xB0) P3;

/* Port 0 Output Mode Control */
__sfr __at(0xB1) P0M1;
__sfr __at(0xB2) P0M2;

/* Port 1 Output Mode Control */
__sfr __at(0xB3) P1M1;
__sfr __at(0xB4) P1M2;

/* P1 Bits */
__sbit __at(0x90) P10;
__sbit __at(0x91) P11;
__sbit __at(0x92) P12;
__sbit __at(0x93) P13;
__sbit __at(0x94) P14;
__sbit __at(0x95) P15;
__sbit __at(0x96) P16;
__sbit __at(0x97) P17;

/* Timer Control */
__sfr __at(0x88) TCON;

/* Timer Mode */
__sfr __at(0x89) TMOD;

/* Timer 0 */
__sfr __at(0x8A) TL0;
__sfr __at(0x8C) TH0;

/* Timer 1 */
__sfr __at(0x8B) TL1;
__sfr __at(0x8D) TH1;

/* Clock Control */
__sfr __at(0x8E) CKCON;

/* TCON Bits */
__sbit __at(0x8C) TR0;
__sbit __at(0x8D) TF0;
__sbit __at(0x8E) TR1;
__sbit __at(0x8F) TF1;

/* Interrupt Enable */
__sfr __at(0xA8) IE;

/* IE bits */
__sbit __at(0xA8) EX0;
__sbit __at(0xA9) ET0;
__sbit __at(0xAA) EX1;
__sbit __at(0xAB) ET1;
__sbit __at(0xAC) ES;
__sbit __at(0xAD) EBOD;
__sbit __at(0xAE) EADC;
__sbit __at(0xAF) EA;

#endif
