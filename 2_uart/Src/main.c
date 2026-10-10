// Nucleo Board has USART3 by default. It is connected to APB1 Bus.
// Table 10 of Nucleo User manual: Alternate Function AF7: Pin D8: USART3_TX and Pin D9: USART3_RX

#include "stm32h7xx.h"

#define		GPIODEN						(1U<<3)
#define		UART3_TX					(1U<<8)
#define		GPIO_ALTERNATE_MODE			 0x2   //0b 10

#define		USART3EN					(1U<<18)

#define UART_DATAWIDTH_8B                  0x00000000U             /*!< 8 bits word length : Start bit, 8 data bits, n stop bits */
#define UART_PARITY_NONE                   0x00000000U               /*!< Parity control disabled */
#define UART_STOPBITS_1                    0x00000000U                   /*!< 1 stop bit */

void set_ahb4_periph_clock(uint32_t periphs);
void set_pin_mode(GPIO_TypeDef *GPIOx, uint32_t Pin, uint32_t Mode);
void set_apb1_periph_clock(uint32_t periphs);
void config_uart_parameters(USART_TypeDef *USARTx, uint32_t DataWidth, uint32_t Parity, uint32_t StopBits);
uint16_t compute_uart_div(uint32_t PeriphClk, uint32_t BaudRate);
void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t BaudRate);
void uart_enable(USART_TypeDef *USARTx);

void uart_write(USART_TypeDef *USARTx , uint8_t value);
void uart3_tx_init(void);
void set_uart_tranfer_direction(USART_TypeDef *USARTx,uint32_t TransferDirection);

int main(void)
{
    int x;
	uart3_tx_init();

	while(1)
	{
		 uart_write(USART3 , 'A');
		 for(int i=0;i<9000;i++)
		 {
			 x++;
		 }
	}
}

void uart_write(USART_TypeDef *USARTx , uint8_t value)
{
	/*Make sure transmit FIFO is empty
	This checks the TXE_TXFNF (Transmit Data Register Empty / Transmit FIFO Not Full) flag.
	This flag indicates that the transmitter can accept another byte.*/
	while (!(USARTx->ISR & USART_ISR_TXE_TXFNF)){}

	/*Write value into transmit FIFO*/
	USARTx->TDR = value;
}


void uart3_tx_init(void)
{
	/*1. Enable clock access to GPIOD*/
	 set_ahb4_periph_clock(GPIODEN);

	/*2. Set PD8 to mode to alternate function*/
	 set_pin_mode(GPIOD,  UART3_TX,  GPIO_ALTERNATE_MODE);

	/*3. Set alternate function to USART*/
	 GPIOD->AFR[1] |= (1U<<0);
	 GPIOD->AFR[1] |= (1U<<1);
	 GPIOD->AFR[1] |= (1U<<2);
	 GPIOD->AFR[1] &= ~(1U<<3);

	/*Enable clock to the USART3 module*/
	 set_apb1_periph_clock(USART3EN);

	/*Confiugure USART parameters*/
	 config_uart_parameters(USART3,  UART_DATAWIDTH_8B,UART_PARITY_NONE,  UART_STOPBITS_1);
	 set_uart_tranfer_direction(USART3 ,USART_CR1_TE);

	/*Set baudrate*/
	 uart_set_baudrate(USART3, 64000000,115200);

	/*Enable USART*/
	uart_enable(USART3);
}

void uart_enable(USART_TypeDef *USARTx)
{
	SET_BIT(USARTx->CR1,USART_CR1_UE);
}


void set_uart_tranfer_direction(USART_TypeDef *USARTx,uint32_t TransferDirection)
{
	  MODIFY_REG(USARTx->CR1, USART_CR1_RE | USART_CR1_TE, TransferDirection);

}
void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t BaudRate)
{
	USARTx->BRR = compute_uart_div( PeriphClk,  BaudRate);
}

void config_uart_parameters(USART_TypeDef *USARTx, uint32_t DataWidth, uint32_t Parity, uint32_t StopBits)
{
  MODIFY_REG(USARTx->CR1, USART_CR1_PS | USART_CR1_PCE | USART_CR1_M, Parity | DataWidth);

  MODIFY_REG(USARTx->CR2, USART_CR2_STOP, StopBits);
}


void set_ahb4_periph_clock(uint32_t periphs)
{
	SET_BIT(RCC->AHB4ENR,periphs);
}


void set_ahb2_periph_clock(uint32_t periphs)
{
	SET_BIT(RCC->AHB2ENR,periphs);
}

void set_apb1_periph_clock(uint32_t periphs)
{
	SET_BIT(RCC->APB1LENR ,periphs);
}

void set_apb2_periph_clock(uint32_t periphs)
{
	SET_BIT(RCC->APB2ENR,periphs);
}


void set_pin_mode(GPIO_TypeDef *GPIOx, uint32_t Pin, uint32_t Mode)
{
	/* 0x3 =  0b 11
	 * POSITION_VAL(1U<<8)
	 *
	 * (1U<<8) = 0000 0000 0000 0000 0000 0001 0000 0000
	 * rbit = 0000 0000 1000 0000 0000 0000 0000 0000
	 * clz  =  8
	 * POSITION_VAL(1U<<8) *2 =  16
	 * 0x3 << 16 =  (1U<<16) | (1U<<17)
	 * CLEAR((1U<<16) | (1U<<17) )  ==>  bit16 =0, bit 17 =0
	 *
	 * Mode = 0b 10 = 0x2
	 * 2 << 16 ==>  bit16 =0, bit 17 =1
	 * */

	MODIFY_REG(GPIOx->MODER, (0x3 << (POSITION_VAL(Pin) * 2U)), (Mode << (POSITION_VAL(Pin) * 2U)));
}


uint16_t compute_uart_div(uint32_t PeriphClk, uint32_t BaudRate)
{
	return ((PeriphClk + (BaudRate/2U))/BaudRate);
}

