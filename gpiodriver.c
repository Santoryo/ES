#define GPIOA (*(volatile unsigned int*) 0x48000000)
#define GPIOB (*(volatile unsigned int*) 0x48000400)
#define GPIOC (*(volatile unsigned int*) 0x48000800)
#define GPIOD (*(volatile unsigned int*) 0x48000C00)
#define GPIOE (*(volatile unsigned int*) 0x48001000)
#define GPIOF (*(volatile unsigned int*) 0x48001400)
#define GPIOG (*(volatile unsigned int*) 0x48001800)
#define GPIOH (*(volatile unsigned int*) 0x48001C00)


// MODE
#define GPIOx_MODER (*(volatile unsigned int*)) 0x00

#define MODE_INPUT     00
#define MODE_OUTPUT    01
#define MODE_ALTERNATE 10
#define MODE_ANALOG    11
