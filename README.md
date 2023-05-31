# STP(Simple Transfer Protocol)
 World Stupid Prtocol
 This is basic protocol for multiple devices.Supporting Master slave operation.
 Basicly protocol frame have 40 byte. Protocol transfering 32 byte one time on default.STP_config exist maimum data length.
 This protocol write,read,response frame fixed 40 byte.Because more easy to implemnt any system.
 The example Master is STM32411 nucelo borad and the slave is stm32f4 discovery board.Examples using UART in interrupt mode.
 The library default have 9 register.Every register is fixed 32 byte length.
 Library have some issues,check the issues section.
 Master and slave functions are in differen source files.
 I hope,adding  clear documentation.
 
![STP](https://github.com/eyumurta/STP-Simple-Transfer-Protocol-/assets/57114692/188b5087-8e47-4cc9-aa6e-f33cabad94e1)
